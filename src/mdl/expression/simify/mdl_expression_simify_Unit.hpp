/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_simify_Unit.hpp                           */
/* Description:     pair of iterators for the simification algorithm         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/expression/iterator/mdl_expression_iterator.hpp"

namespace mdl {
namespace expression {
namespace simify {

template<class T_1, class T_2>
class Unit : public
	iterator :: modifier :: Pair
	<
		Lengthirator<T_1>,
		Lengthirator<T_2>
	> {
public :
	typedef T_1 Term_1_;
	typedef T_2 Term_2_;
	typedef
		typename Term_1_ :: const_Iterator_
		_Iterator_1_;
	typedef
		typename Term_2_ :: const_Iterator_
		_Iterator_2_;
	typedef
		Lengthirator<Term_1_>
		Lengthirator_1_;
	typedef
		Lengthirator<Term_2_>
		Lengthirator_2_;
	typedef
		typename iterator :: modifier :: Pair
		<
			Lengthirator_1_,
			Lengthirator_2_
		>
		Pair_;
	typedef
		typename Pair_ :: Iterator_1_
		Iterator_1_;
	typedef
		typename Pair_ :: Iterator_2_
		Iterator_2_;
	typedef Unit Unit_;
	typedef
		Unit<Term_2_, Term_1_>
		InverseUnit_;

	Unit
	(
		const _Iterator_1_,
		const _Iterator_2_,
		const index :: Step = index :: undefined :: STEP,
		const index :: Step = index :: undefined :: STEP
	);
	Unit (const Iterator_1_, const Iterator_2_);
	Unit (const Unit&);

	InverseUnit_ inverse() const;

	bool isReacheable() const;
	bool isReplaceable() const;
	bool isFixed() const;

	void operator = (const Unit&);

	void show (String&) const;
	void show() const;

private :
	const index :: Step level_1_;
	const index :: Step level_2_;
};

	template<class T_1, class T_2>
	String&
	operator << (String&, const Unit<T_1, T_2>&);
}
}
}


