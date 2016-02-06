/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_simify_Simifier.ipp                       */
/* Description:     main simification algorithm. Static class                */
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
namespace simify {

	/****************************
	 *		Public members
	 ****************************/

	template<class U, class A>
	inline typename Simifier<U, A> :: Similarity_
	Simifier<U, A> :: proceed
	(
		const Iterator_1_ iterator_1,
		const Iterator_2_ iterator_2,
		const index :: Step level_1,
		const index :: Step level_2
	)
	{
		Unit_ unit
		(
			iterator_1,
			iterator_2,
			level_1,
			level_2
		);
		return simifyNode (unit);
	}
	template<class U, class A>
	inline typename Simifier<U, A> :: Similarity_
	Simifier<U, A> :: proceed (Unit_ unit) {
		return simifyNode (unit);
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class U, class A>
	inline typename Simifier<U, A> :: Similarity_
	Simifier<U, A> :: simifyNext (Unit_ unit)
	{
		if (unit.isTerminal()) {
			if (unit.isFinal()) {
				return Similarity_ (unit);
			}
			return Similarity_();
		}
		++ unit;
		return simifyNode (unit);
	}
	template<class U, class A>
	inline typename Simifier<U, A> :: Similarity_
	Simifier<U, A> :: tryFixed (Unit_ unit)
	{
		if (!unit.isFixed()) {
			return Similarity_();
		}
		if (!unit.isEqual()) {
			return Similarity_();
		}
		return simifyNext (unit);
	}
	template<class U, class A>
	typename Simifier<U, A> :: Similarity_
	Simifier<U, A> :: tryReplaceable (Unit_ unit)
	{
		if (!unit.isReplaceable()) {
			return Similarity_();
		}
		const Iterator_1_
			iterator = unit.second();
		const typename Iterator_1_ :: Node_ :: Terms_ :: Initial_ :: Node_*
			node = iterator->getTerms().getInitial().getFirst();

		Similarity_ result;
		while (node != NULL)
		{
			const Term_* term = node->getValue();
			result += tryTerm (unit, term);
			node = node->getNext();
		}
		return result;
	}
	template<class U, class A>
	inline typename Simifier<U, A> :: Similarity_
	Simifier<U, A> :: tryTerm (Unit_ unit, const Term_* const term)
	{
		unit.second() += term;
		if (unit.isReacheable()) {
			return simifyNext (unit);
		} else {
			return Similarity_();
		}
	}
}
}
}


