/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_fact_Unifier.ipp                    */
/* Description:     main unification algorithm. Static class                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_UNIFY_FACT_UNIFIER_IPP_
#define MDL_EXPRESSION_UNIFY_FACT_UNIFIER_IPP_

namespace mdl {
namespace expression {
namespace unify {
namespace fact {

	/****************************
	 *		Public members
	 ****************************/

	template<class U, class A, int P>
	inline typename Unifier<U, A, P> :: Result_
	Unifier<U, A, P> :: proceed
	(
		const Iterator_1_ iterator_1,
		const Iterator_2_ iterator_2,
		value :: Integer& minDifference_1,
		value :: Integer& minDifference_2,
		const index :: Step level_1,
		const index :: Step level_2
	)
	{
		minDifference_1 = value :: undefined :: INTEGER;
		minDifference_2 = value :: undefined :: INTEGER;
		Unit_ unit
		(
			iterator_1,
			iterator_2,
			minDifference_1,
			minDifference_2,
			level_1,
			level_2
		);
		return unifyNode (unit);
	}

	/****************************
	 *		Private members
	 ****************************/

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

#endif /*MDL_EXPRESSION_UNIFY_FACT_UNIFIER_IPP_*/
