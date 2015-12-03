/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_sub_Finaly.ipp                      */
/* Description:     final procedure of a substitution unification            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_UNIFY_SUB_FINALY_IPP_
#define MDL_EXPRESSION_UNIFY_SUB_FINALY_IPP_

namespace mdl {
namespace expression {
namespace unify {
namespace sub {

	/****************************
	 *		Public members
	 ****************************/

	template<class S, class T>
	inline void
	Finaly<S, T> :: finalize
	(
		const Substitution_* substitutionInt,
		Evidences_& evidences,
		Evidence_* evidenceUp [],
		const value :: Integer arity
	)
	{
		Memory :: stack().push();
		doJob (substitutionInt, evidences, evidenceUp, arity);
		Memory :: stack().pop();
	}
	template<class S, class T>
	void
	Finaly<S, T> :: finalize
	(
		const Substitution_* theta,
		const value :: Integer compClosureBoundary,
		const Substitution_* substitutionInt,
		const Substitution_* delta,
		Evidences_& evidences,

		Evidence_* evidenceUp [],
		const value :: Integer arity
	)
	{
		Memory :: stack().push();
		bool success = true;
		Substitution_*
			substitution = createSubstitution (compClosureBoundary, substitutionInt, delta, theta, success);
		if (success) {
			doJob (substitution, evidences, evidenceUp, arity);
		}
		Memory :: stack().pop();
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class S, class T>
	void
	Finaly<S, T> :: doJob
	(
		const Substitution_* substitution,
		Evidences_& evidences,
		Evidence_* evidenceUp [],
		const value :: Integer arity
	)
	{
		typedef
			prover :: evidence :: Prop<Allocator_>
			Prop_;

		Prop_* evidenceProp = new Prop_
		(
			evidences.getNode(),
			arity,
			evidenceUp
		);
		evidences.add (substitution, evidenceProp);
	}
	template<class S, class T>
	inline typename Finaly<S, T> :: Substitution_*
	Finaly<S, T> :: createSubstitution
	(
		const value :: Integer boundary,
		const Substitution_* sb,
		const Substitution_* dl,
		const Substitution_* th,
		bool& success
	)
	{
		Substitution_*
			delta = Substitution_ :: create (dl);
		Substitution_*
			theta = Substitution_ :: create (th);

		if (!Substitution_ :: unifyCommonVariables (delta, theta)) {
			success = false;
			return NULL;
		}
		delta = delta->compose (theta, false);
		theta = theta->compose (delta);

		if (!Substitution_ :: compositionClosure (boundary, theta)) {
			success = false;
			return NULL;
		}

		Substitution_*
			substitution = Substitution_ :: create (sb);

		if (!Substitution_ :: unifyCommonVariables (substitution, theta)) {
			success = false;
			return NULL;
		}
		substitution = substitution->compose (theta);

		// This code causes errors:
		//
		//if (!Substitution_ :: compositionClosure (boundary, substitution)) {
		//	success = false;
		//	return NULL;
		//}

		success = true;
		return substitution;
	}
}
}
}
}

#endif /*MDL_EXPRESSION_UNIFY_SUB_FINALY_IPP_*/
