/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_benchmark_Optimization.hpp                     */
/* Description:     time estimation polynomials evaluation                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"

namespace mdl {
namespace study {
namespace benchmark {

class Optimization :
	public object :: Object,
	public Scalar<Optimization> {
public :
	typedef
		Polynomial<1, allocator :: Heap>
		Polynomial_1_;
	typedef
		Polynomial<2, allocator :: Heap>
		Polynomial_2_;

	Optimization (Format&);
	virtual ~ Optimization();

	void benchmark (Time& timeLimit);
	bool isDone() const;

	const Polynomial_1_* getTimePolynomialX() const;
	const Polynomial_2_* getTimePolynomialXY() const;

	void writeOptions (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	enum {
		MIN_SAMPLE_STEP = 1,
		INITIAL_SAMPLE_VECTOR_CAPACITY = 32
	};

	typedef
		vector :: Vector
		<
			study :: Sample,
			storage :: ByPointer,
			allocator :: Heap
		>
		SampleVector_;

	typedef vector :: value :: Integer
		SizeVector_;

	bool benchmarkSizePrecision
	(
		const value :: Integer size,
		const value :: Integer precision,
		Time timeLimit
	);
	study :: Sample* findSample
	(
		const value :: Integer size,
		Time timeLimit
	);

	Format format_;
	Format subFormat_;

	Data<1> timeData1_;
	Data<2> timeData2_;
	Polynomial_1_* timePolynomialX_;
	Polynomial_2_* timePolynomialXY_;

	SizeVector_ sizeVector_;
	SampleVector_ sampleVector_;

	static const char* optionTimeX_;
	static const char* optionTimeXY_;
};

}
}
}


