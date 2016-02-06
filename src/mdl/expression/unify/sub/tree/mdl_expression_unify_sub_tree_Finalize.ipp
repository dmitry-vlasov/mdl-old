/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_sub_tree_Finalize.hpp               */
/* Description:     final procedure of a matrix unification                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/expression/unify/sub/mdl_expression_unify_sub_Finaly.hpp"

namespace mdl {
namespace expression {
namespace unify {
namespace sub {
namespace tree {

	/****************************
	 *		Public members
	 ****************************/

	template<class U, class T>
	inline
	Finalize<U, T> :: Finalize
	(
		const Substitution_* substitutionInt,
		Evidences_& evidences,
		const value :: Integer boundary
	) :
	substitutionInt_ (substitutionInt),
	evidences_ (evidences),
	boundary_ (boundary) {
	}

	template<class U, class T>
	inline void
	Finalize<U, T> :: operator () (const Unit_& unit)
	{
		Memory :: stack().push();
		const value :: Integer dimension = unit.getDimension();
		Matrix_ matrix (dimension);
		for (index :: Arity i = 0; i < dimension; ++ i) {
			const Container_&
				evidences = unit.getValues (i);
			matrix.getReference (i) = &evidences;
		}
		Multyindex_ multyindex (dimension, matrix);
		//const prover :: tree :: Tree*
		//	tree = unit.getValues (0).getFirstValue()->getNode()->getTree();
		while (true) {
			//tree->refresh ("finalizing tree sub unification");
			proceedMultyindex (unit, multyindex);
			if (++ multyindex) {
				break;
			}
		}
		Memory :: stack().pop();
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class U, class T>
	inline void
	Finalize<U, T> :: proceedMultyindex (const Unit_& unit, const Multyindex_& multyindex)
	{
		Memory :: stack().push();
		const Substitution_* theta = createTheta (unit, multyindex);
		const index :: Arity arity = unit.getDimension();
		Evidence_* evidenceUp [arity];
		for (index :: Arity i = 0; i < arity; ++ i) {
			evidenceUp [i] = multyindex.getValue (i);
		}
		sub :: template Finaly<Substitution_, Types_> :: finalize (
			theta,
			boundary_,
			substitutionInt_,
			unit.getSubstitution(),
			evidences_,
			evidenceUp,
			arity
		);
		Memory :: stack().pop();
	}
	template<class U, class T>
	inline const typename Finalize<U, T> :: Substitution_*
	Finalize<U, T> :: createTheta (const Unit_& unit) const
	{
		Substitution_*
			delta = Substitution_ :: create (unit.getSubstitution());
		Substitution_* theta = NULL;
		for (index :: Arity i = 0; i < unit.getDimension(); ++ i) {
			const Evidence_*
				evidence = unit.getValue (i);
			const Substitution_*
				substitution = Substitution_ :: create (evidence->getSubstitution());
			theta = theta->unite (substitution);
		}
		theta = theta->compose (delta);
		return theta;
	}
	template<class U, class T>
	inline const typename Finalize<U, T> :: Substitution_*
	Finalize<U, T> :: createTheta (const Unit_& unit, const Multyindex_& multyindex) const
	{
		Substitution_*
			delta = Substitution_ :: create (unit.getSubstitution());
		Substitution_* theta = NULL;
		for (index :: Arity i = 0; i < multyindex.getDimension(); ++ i) {
			const Evidence_*
				evidence = multyindex.getValue (i);
			const Substitution_*
				substitution = Substitution_ :: create (evidence->getSubstitution());
			theta = theta->unite (substitution);
		}
		theta = theta->compose (delta);
		return theta;
	}
}
}
}
}
}


