/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_fact_Replacer_SYM.ipp               */
/* Description:     symmetric unification variable substitution algorithm    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_UNIFY_FACT_REPLACER_SYM_IPP_
#define MDL_EXPRESSION_UNIFY_FACT_REPLACER_SYM_IPP_

namespace mdl {
namespace expression {
namespace unify {
namespace fact {

	/****************************
	 *		Public members
	 ****************************/

	template<class U, int D>
	inline typename Replacer<U, policy :: SYMMETRIC, D> :: Result_
	Replacer<U, policy :: SYMMETRIC, D> :: tryReplace (Unit_ unit)
	{
		Result_ result;
		const typename SourceTerms_ :: Initial_ :: Node_*
			node_1 = unit.getSource()->getTerms().getInitial().getFirst();
		const typename TargetTerms_ :: Initial_ :: Node_*
			node_2 = unit.getTarget()->getTerms().getInitial().getFirst();
		const SourceTerm_* term_1 = NULL;
		const TargetTerm_* term_2 = NULL;

		while (node_1 != NULL) {
			term_1 = node_1->getValue();
			#ifdef DEBUG
			term_1->verifyIntegrity();
			#endif
			while (node_2 != NULL) {
				term_2 = node_2->getValue();
				#ifdef DEBUG
				term_2->verifyIntegrity();
				#endif
				result.join (tryTerm (unit, term_1, term_2));
				node_2 = node_2->getNext();
			}
			node_1 = node_1->getNext();
		}
		return result;
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class U, int D>
	inline typename Replacer<U, policy :: SYMMETRIC, D> :: Result_
	Replacer<U, policy :: SYMMETRIC, D> :: tryTerm
	(
		Unit_ unit,
		const SourceTerm_* term_1,
		const TargetTerm_* term_2
	)
	{
		if (!unit.shift (term_1, term_2)) {
			return Result_();
		} else {
			return Policy_ :: unifyNext (unit);
		}
	}
}
}
}
}

#endif /*MDL_EXPRESSION_UNIFY_FACT_REPLACER_SYM_IPP_*/
