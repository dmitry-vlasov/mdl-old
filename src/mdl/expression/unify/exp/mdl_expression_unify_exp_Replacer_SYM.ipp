/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_exp_Replacer_SYM.ipp                */
/* Description:     symmetric unification variable substitution algorithm    */
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

	template<class U, int D>
	inline typename Replacer<U, policy :: SYMMETRIC, D> :: Result_
	Replacer<U, policy :: SYMMETRIC, D> :: tryReplace (Unit_ unit)
	{
		const Substitution_* const
			substitution = unit.findSubstitution();
		if (substitution == NULL) {
			return tryNew (unit);
		} else {
			return tryUsed (unit, substitution);
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class U, int D>
	inline typename Replacer<U, policy :: SYMMETRIC, D> :: Result_
	Replacer<U, policy :: SYMMETRIC, D> :: tryUsed (Unit_ unit, const Substitution_* substitution)
	{
		typedef
			typename Substitution_ :: Term_
			Term_0;
		const Term_0* const
			term = substitution->getTerm();
		#ifdef DEBUG
		term->verifyIntegrity();
		#endif

		typedef
			typename Unit_ :: Term_1_
			Term_1;
		typedef
			Builder
			<
				typename Term_1 :: template Alternative<allocator :: Stack> :: Result_,
				Term_0
			>
			Builder;
		Builder builder (term);

		Term_1* const
			insertion = builder.build()->template castAway<typename Term_1 :: Allocator_>();

		insertion->getEnd()->template
			link<expression :: direction :: RIGHT> (unit.source().getNode()->goRight());
		#ifdef DEBUG
		insertion->verifyIntegrity();
		#endif
		unit.source() = const_cast<const Term_1*>(insertion)->getBegin();

		if (!unit.isReacheable()) {
			return Result_();
		}
		return Policy_ :: unifyThis (unit);
	}
	template<class U, int D>
	inline typename Replacer<U, policy :: SYMMETRIC, D> :: Result_
	Replacer<U, policy :: SYMMETRIC, D> :: tryNew (Unit_ unit)
	{
		Result_ result;
		typedef typename Terms_ :: Initial_ :: Node_ Node;
		const Node*
			node = unit.getTarget()->getTerms().getInitial().getFirst();
		const Term_*
			term = NULL;

		while (node != NULL)
		{
			term = node->getValue();
			#ifdef DEBUG
			term->verifyIntegrity();
			#endif
			result.join (tryTerm (unit, term));
			node = node->getNext();
		}
		return result;
	}
	template<class U, int D>
	inline typename Replacer<U, policy :: SYMMETRIC, D> :: Result_
	Replacer<U, policy :: SYMMETRIC, D> :: tryTerm (Unit_ unit, const Term_* term)
	{
		if (!unit.newSubstitution (term)) {
			return Result_();
		}
		return Policy_ :: unifyNext (unit);
	}
}
}
}
}


