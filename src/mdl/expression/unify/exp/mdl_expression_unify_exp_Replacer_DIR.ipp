/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_exp_Replacer_DIR.ipp                */
/* Description:     directed unification variable substitution algorithm     */
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
namespace unify {
namespace exp {

	/****************************
	 *		Public members
	 ****************************/

	template<class U, int P, int D>
	inline typename Replacer<U, P, D> :: Result_
	Replacer<U, P, D> :: tryReplace (Unit_ unit)
	{
		bool substituted = false;
		const Target_
			iterator = unit.follow (substituted);

		if (substituted) {
			return tryUsed (unit, iterator);
		} else {
			return tryNew (unit, iterator);
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class U, int P, int D>
	inline typename Replacer<U, P, D> :: Result_
	Replacer<U, P, D> :: tryUsed (Unit_ unit, Target_ iterator)
	{
		if (iterator == NULL) {
			return Result_();
		}
		unit.target() = iterator;
		if (!unit.isReacheable()) {
			return Result_();
		}
		return Policy_ :: unifyNext (unit);
	}
	template<class U, int P, int D>
	typename Replacer<U, P, D> :: Result_
	Replacer<U, P, D> :: tryNew (Unit_ unit, Target_ iterator)
	{
		Result_ result;
		const typename Terms_ :: Initial_ :: Node_*
			node = iterator->getTerms().getInitial().getFirst();
		const Term_*
			term = NULL;

		while (node != NULL)
		{
			term = node->getValue();
			result.join (tryTerm (unit, term));
			node = node->getNext();
		}
		return result;
	}
	template<class U, int P, int D>
	typename Replacer<U, P, D> :: Result_
	Replacer<U, P, D> :: tryTerm (Unit_ unit, const Term_* term)
	{
		if (!unit.newSubstitution (term)) {
			return Result_();
		}
		if (!unit.isReacheable()) {
			return Result_();
		}
		return Policy_ :: unifyNext (unit);
	}
}
}
}
}


