/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_build_Node_ADD_DATA.ipp                   */
/* Description:     manager for data in expression node building routines    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace expression {
namespace build {

	/****************************
	 *		Public members
	 ****************************/

	template<class B>
	inline void
	Node<B, ADD_DATA> :: manage
	(
		Expression_* const target,
		Iterator_1_& targetEnd,
		Iterator_2_& sourceEnd,
		Value_ value
	)
	{
		if (target != NULL) {
			target->template addFindNode<Iterator_2_> (targetEnd, sourceEnd);
		} else {
			target->template copyNode<Iterator_2_> (targetEnd, sourceEnd);
		}
		targetEnd->getData().addValue (value);
	}
}
}
}


