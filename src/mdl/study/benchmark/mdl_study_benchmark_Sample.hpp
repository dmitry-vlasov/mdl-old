/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_benchmark_Sample.hpp                           */
/* Description:     time estimation for sample building                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_BENCHMARK_SAMPLE_HPP_
#define MDL_STUDY_BENCHMARK_SAMPLE_HPP_

#include "mdl/interface/mdl_interface.hpp"

namespace mdl {
namespace study {
namespace benchmark {

class Sample :
	public object :: Object,
	public Scalar<Sample> {
public :
	typedef
		Polynomial<1, allocator :: Heap>
		Polynomial_1_;
	typedef
		Polynomial<2, allocator :: Heap>
		Polynomial_2_;

	enum {
		SAMPLE_SIZE_STEP = 1
	};

	Sample (Format&);
	virtual ~ Sample();

	void benchmark (Time& timeLimit);
	bool isDone() const;

	const Polynomial_1_* getTimePolynomialX() const;

	void writeOptions (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	Format format_;
	Format subFormat_;

	Data<1> timeData1_;
	Polynomial_1_* timePolynomialX_;

	static const char* optionTimeX_;
};

}
}
}

#endif /*MDL_STUDY_BENCHMARK_SAMPLE_HPP_*/
