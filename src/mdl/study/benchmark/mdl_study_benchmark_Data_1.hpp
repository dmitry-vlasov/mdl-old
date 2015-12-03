/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_benchmark_Data_1.hpp                           */
/* Description:     1 dimensional data for interpolation                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_BENCHMARK_DATA_1_HPP_
#define MDL_STUDY_BENCHMARK_DATA_1_HPP_

#include "mdl/interface/mdl_interface.hpp"

namespace mdl {
namespace study {
namespace benchmark {

template<>
class Data<1> :
	public object :: Object,
	public Scalar<Data<1> > {
public :
	typedef
		Polynomial<1, allocator :: Heap>
		Polynomial_1_;

	Data ();
	virtual ~ Data();

	void add (const value :: Real x, const value :: Real y);
	Polynomial_1_* interpolate();
	Polynomial_1_* interpolate (const value :: Integer degree);
	void clear();

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	enum {
		MAX_COUNT_PER_SIZE = 16,
		INITIAL_VECTOR_CAPACITY = 256
	};

	void normalize();

	typedef
		map :: Scalar
		<
			value :: Real,
			value :: Real,
			allocator :: Heap
		>
		RealFunction_;
	typedef
		map :: Scalar
		<
			value :: Real,
			value :: Integer,
			allocator :: Heap
		>
		IntegerFunction_;

	IntegerFunction_ counter_;
	RealFunction_    function_;

	vector :: value :: Real xVector_;
	vector :: value :: Real yVector_;
};

}
}
}

#endif /*MDL_STUDY_BENCHMARK_DATA_1_HPP_*/
