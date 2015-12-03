/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_exp_Unifier.ipp                     */
/* Description:     main unification algorithm. Static class                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_UNIFY_EXP_UNIFIER_IPP_
#define MDL_EXPRESSION_UNIFY_EXP_UNIFIER_IPP_

namespace mdl {
namespace expression {
namespace unify {
namespace exp {

	/****************************
	 *		Public members
	 ****************************/

	template<class U, class A, int P>
	inline typename Unifier<U, A, P> :: Result_
	Unifier<U, A, P> :: proceed
	(
		const Iterator_1_ iterator_1,
		const Iterator_2_ iterator_2
	)
	{
		Unit_ unit (iterator_1, iterator_2);
		Result_ result = unifyNode (unit);
		#ifdef DEBUG
		if (!result.correct_) {
			unifyNode (unit);
		}
		#endif /*DEBUG*/
		return result;
	}
	template<class U, class A, int P>
	inline typename Unifier<U, A, P> :: Result_
	Unifier<U, A, P> :: proceed (Unit_ unit) {
		return unifyNode (unit);
	}

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
				result.join (tryUnit (unit));
			}
			+ unit;
		}
		return result;
	}

	template<class U, class A, int P>
	inline typename Unifier<U, A, P> :: Result_
	Unifier<U, A, P> :: tryUnit (Unit_ unit)
	{
		switch (unit.getReplaceability()) {
		case Unit_ :: NONE :
			return tryFixed (unit);
		case Unit_ :: DIRECT :
			return DirectReplacer_ :: tryReplace (unit);
		case Unit_ :: INVERSE :
			return InverseReplacer_ :: tryReplace (unit.inverse());
		case Unit_ :: BOTH :
			if (unit.isEqual()) {
				return unifyNext (unit);
			} else  {
				Result_ result = DirectReplacer_ :: tryReplace (unit);
				if (result.isEmpty()) {
					result = InverseReplacer_ :: tryReplace (unit.inverse());
				}
				return result;
			}
		}
	}
	template<class U, class A, int P>
	inline typename Unifier<U, A, P> :: Result_
	Unifier<U, A, P> :: tryFixed (Unit_ unit)
	{
		if (!unit.isFixed()) {
			return Result_();
		}
		if (!unit.isEqual()) {
			return Result_();
		}
		return unifyNext (unit);
	}
	template<class U, class A, int P>
	inline typename Unifier<U, A, P> :: Result_
	Unifier<U, A, P> :: unifyNext (Unit_ unit)
	{
		if (unit.isTerminal()) {
			if (unit.isFinal()) {
				return Result_ (unit);
			}
			return Result_();
		}
		++ unit;
		return unifyNode (unit);
	}
}
}
}
}

#endif /*MDL_EXPRESSION_UNIFY_EXP_UNIFIER_IPP_*/
