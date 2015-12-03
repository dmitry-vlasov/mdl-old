/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_fact_Unifier.cpp                    */
/* Description:     main unification algorithm. Static class                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_UNIFY_FACT_UNIFIER_CPP_
#define MDL_EXPRESSION_UNIFY_FACT_UNIFIER_CPP_

namespace mdl {
namespace expression {
namespace unify {
namespace fact {

	/****************************
	 *		Private members
	 ****************************/

	template<class U, class A, int P>
	typename Unifier<U, A, P> :: Result_
	Unifier<U, A, P> :: unifyNode (Unit_ unit)
	{
		Result_ result;
		while (unit != NULL) {
			if (unit.isReacheable()) {
				result.join (tryFixed (unit));
				result.join (DirectReplacer_ :: tryReplace (unit));
				result.join (InverseReplacer_ :: tryReplace (unit.inverse()));
			}
			+ unit;
		}
		return result;
	}
}
}
}
}

#endif /*MDL_EXPRESSION_UNIFY_FACT_UNIFIER_CPP_*/
