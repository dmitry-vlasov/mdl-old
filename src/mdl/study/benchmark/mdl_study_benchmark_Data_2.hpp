/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_benchmark_Data_2.hpp                           */
/* Description:     2 dimensional data for interpolation                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_BENCHMARK_DATA_2_HPP_
#define MDL_STUDY_BENCHMARK_DATA_2_HPP_

#include "mdl/interface/mdl_interface.hpp"

namespace mdl {
namespace study {
namespace benchmark {

template<>
class Data<2> :
	public object :: Object,
	public Scalar<Data<2> > {
public :
	typedef
		Polynomial<2, allocator :: Heap>
		Polynomial_2_;

	Data ();
	virtual ~ Data();

	void add
	(
		const value :: Real x,
		const value :: Real y,
		const value :: Real z
	);
	Polynomial_2_* interpolate();
	Polynomial_2_* interpolate
	(
		const value :: Integer degreeX,
		const value :: Integer degreeY
	);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	enum {
		MAX_COUNT_PER_SIZE = 16,
		INITIAL_VECTOR_CAPACITY = 16
	};

	typedef
		map :: Scalar
		<
			value :: Real,
			value :: Real,
			allocator :: Heap
		>
		RealFunctionY_;
	typedef
		map :: Scalar
		<
			value :: Real,
			value :: Integer,
			allocator :: Heap
		>
		IntegerFunctionY_;
	typedef
		map :: Scalar
		<
			value :: Real,
			RealFunctionY_*,
			allocator :: Heap
		>
		RealFunctionXY_;
	typedef
		map :: Scalar
		<
			value :: Real,
			IntegerFunctionY_*,
			allocator :: Heap
		>
		IntegerFunctionXY_;

	void addValue
	(
		const value :: Real x,
		const value :: Real y,
		const value :: Real z
	);
	void incCounter
	(
		const value :: Real x,
		const value :: Real y
	);
	void normalize();

	IntegerFunctionXY_ counter_;
	RealFunctionXY_    function_;

	vector :: value :: Real xVector_;
	vector :: value :: Real yVector_;
	vector :: value :: Real zVector_;
};

}
}
}

#endif /*MDL_STUDY_BENCHMARK_DATA_2_HPP_*/
