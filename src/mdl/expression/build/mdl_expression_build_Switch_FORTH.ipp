/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_build_Switch_FORTH.ipp                    */
/* Description:     expression building routines                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_BUILD_SWITCH_FORTH_IPP_
#define MDL_EXPRESSION_BUILD_SWITCH_FORTH_IPP_

namespace mdl {
namespace expression {
namespace build {

	/****************************
	 *		Public members
	 ****************************/

	template<class B>
	inline const typename Switch<B, FORTH> :: Terms_2_&
	Switch<B, FORTH> :: getTerms (const Iterator_2_& iterator) {
		return iterator->getTerms().getInitial();
	}
	template<class B>
	inline void
	Switch<B, FORTH> :: inc (Iterator_1_& iterator_1, Iterator_2_& iterator_2)
	{
		++ iterator_1;
		++ iterator_2;
	}
	template<class B>
	inline bool
	Switch<B, FORTH> :: end (const Term_2_* term, const Iterator_2_& iterator) {
		return (term->getEnd() == iterator);
	}
	template<class B>
	inline typename Switch<B, FORTH> :: Term_1_*
	Switch<B, FORTH> :: newTerm
	(
		const Iterator_1_& iterator_1,
		const Iterator_1_& iterator_2,
		const mdl :: Type* type
	)
	{
		typedef
			typename Terms_1_ :: Terminal_
			Terminal;
		typedef
			typename Terminal :: Node_
			Node;
		const Terminal&
			terminalTerms = iterator_2->getTerms().getTerminal();
		const Node* node = terminalTerms.getFirst();
		while (node != NULL) {
			const Term_1_*
				term = node->getValue();
			if (term->isEqual(iterator_1, iterator_2, type)) {
				return const_cast<Term_1_*>(term);
			}
			node = node->getNext();
		}

		Term_1_* const
			result = Term_1_ :: template create<Allocator_>
			(
				iterator_1,
				iterator_2,
				type
			);
		result->addSelf (false);
		return result;
	}
	template<class B>
	inline typename Switch<B, FORTH> :: Iterator_1_
	Switch<B, FORTH> :: startTarget (Expression_* const expression)
	{
		if ((expression == NULL) || expression->isNull()) {
			return Iterator_1_ (new Node_1_ ());
		} else {
			return expression->getBegin();
		}
	}
	template<class B>
	inline typename Switch<B, FORTH> :: Iterator_2_
	Switch<B, FORTH> :: startSource (const Term_2_* const term) {
		return term->getBegin();
	}

	template<class B>
	inline typename Switch<B, FORTH> :: Iterator_2_
	Switch<B, FORTH> :: beginSource (const Term_2_* const term) {
		return term->getBegin();
	}
	template<class B>
	inline typename Switch<B, FORTH> :: Iterator_2_
	Switch<B, FORTH> :: endSource (const Term_2_* const term) {
		return term->getEnd();
	}
}
}
}

#endif /*MDL_EXPRESSION_BUILD_SWITCH_FORTH_IPP_*/
