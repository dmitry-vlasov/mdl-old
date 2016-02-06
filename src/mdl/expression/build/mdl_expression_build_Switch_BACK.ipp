/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_build_Switch_BACK.ipp                     */
/* Description:     expression building routines                             */
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
	inline const typename Switch<B, BACK> :: Terms_2_&
	Switch<B, BACK> :: getTerms (const Iterator_2_& iterator) {
		return iterator->getTerms().getTerminal();
	}
	template<class B>
	inline void
	Switch<B, BACK> :: inc (Iterator_1_& iterator_1, Iterator_2_& iterator_2)
	{
		-- iterator_1;
		-- iterator_2;
	}
	template<class B>
	inline bool
	Switch<B, BACK> :: end (const Term_2_* term, const Iterator_2_& iterator) {
		return (term->getBegin() == iterator);
	}
	template<class B>
	inline typename Switch<B, BACK> :: Term_1_*
	Switch<B, BACK> :: newTerm
	(
		const Iterator_1_& iterator_1,
		const Iterator_1_& iterator_2,
		const mdl :: Type* type
	)
	{
		Term_1_* const
			result = Term_1_ :: template create<Allocator_>
			(
				iterator_2,
				iterator_1,
				type
			);
		result->addSelf (false);
		return result;
	}
	template<class B>
	inline typename Switch<B, BACK> :: Iterator_1_
	Switch<B, BACK> :: startTarget (Expression_* const expression)
	{
		if ((expression == NULL) || expression->isNull()) {
			return Iterator_1_ (new Node_1_ ());
		} else {
			return expression->getEnd();
		}
	}
	template<class B>
	inline typename Switch<B, BACK> :: Iterator_2_
	Switch<B, BACK> :: startSource (const Term_2_* const term) {
		return term->getEnd();
	}

	template<class B>
	inline typename Switch<B, BACK> :: Iterator_2_
	Switch<B, BACK> :: beginSource (const Term_2_* const term) {
		return term->getEnd();
	}
	template<class B>
	inline typename Switch<B, BACK> :: Iterator_2_
	Switch<B, BACK> :: endSource (const Term_2_* const term) {
		return term->getBegin();
	}
}
}
}


