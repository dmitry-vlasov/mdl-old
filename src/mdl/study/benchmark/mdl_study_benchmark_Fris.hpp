/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_benchmark_Fris.hpp                             */
/* Description:     benchmarking FRiS learning                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/study/benchmark/mdl_study_benchmark_Data_1.hpp"

namespace mdl {
namespace study {
namespace benchmark {

class Fris :
	public object :: Object,
	public Scalar<Fris> {
public :
	typedef
		Polynomial<1, allocator :: Heap>
		Polynomial_1_;
	typedef
		Polynomial<2, allocator :: Heap>
		Polynomial_2_;

	Fris (Format&);
	virtual ~ Fris();

	void benchmark (Time& timeLimit);
	bool isDone() const;

	const Polynomial_1_* getCreateTimePolynomialX() const;
	const Polynomial_1_* getTeachTimePolynomialX() const;
	const Polynomial_2_* getTeachTimePolynomialXY() const;
	const Polynomial_1_* getResultTimePolynomialX() const;
	const Polynomial_1_* getDeleteTimePolynomialX() const;

	void writeOptions (String& output) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	typedef
		mdl :: form :: evaluation :: term :: Lexp
		LexpTerm_;
	typedef
		LexpTerm_ :: Fris_
		FrisFunc_;

	enum {
		COUNT_VECTOR_SIZE = 256,
		MAX_COUNT_PER_SIZE = 16
	};

	bool benchmarkPair
	(
		const index :: Assertion index,
		const value :: Integer size
	);
	void benchmarkExperience
	(
		statement :: Experience* experience,
		const value :: Integer size
	);
	void benchmarkTeaching
	(
		lexp :: Teacher* teacher,
		const value :: Integer size
	);

	Format format_;
	Format subFormat_;

	vector :: value :: Integer countVector_;

	Data<1> createData1_;
	Data<1> teachData1_;
	Data<2> teachData2_;
	Data<1> resultData1_;
	Data<1> deleteData1_;

	Polynomial_1_* createTimePolynomialX_;
	Polynomial_1_* teachTimePolynomialX_;
	Polynomial_2_* teachTimePolynomialXY_;
	Polynomial_1_* resultTimePolynomialX_;
	Polynomial_1_* deleteTimePolynomialX_;

	static const char* optionCreateTimeX_;
	static const char* optionTeachTimeX_;
	static const char* optionTeachTimeXY_;
	static const char* optionResultTimeX_;
	static const char* optionDeleteTimeX_;
};

}
}
}


