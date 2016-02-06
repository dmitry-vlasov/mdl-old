/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_sub_prod_Unify.ipp                  */
/* Description:     scalar substitution unifier module                       */
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
namespace sub {
namespace prod {

	/****************************
	 *		Public members
	 ****************************/

	template<class T, int P, int K, class A>
	inline
	Unify<T, P, K, A> :: Unify
	(
		const index :: Arity dimension,
		const Substitution_* substitutionInt,
		Evidences_& evidences
	) :
	dimension_ (dimension),
	substitutionInt_ (substitutionInt),
	evidences_ (evidences),
	matrix_ (NULL) {
	}

	template<class T, int P, int K, class A>
	inline void
	Unify<T, P, K, A> :: operator() (const Input_& matrix)
	{
		Memory :: stack().push();
		Substivector_ substivector (dimension_);
		Multyindex_ multyindex (dimension_, matrix);
		//const prover :: tree :: Tree*
		//	tree = multyindex.getValue (0)->getNode()->getTree();
		while (true) {
			//tree->refresh ("unifying prod matrix");
			substivector.clear();
			for (index :: Arity d = 0; d < dimension_; ++ d) {
				const Evidence_*
					evidence = multyindex.getValue (d);
				substivector.push() = evidence->getSubstitution();
			}
			Memory :: stack().push();
			tryMultyindex (substivector, multyindex);
			Memory :: stack().pop();
			if (++ multyindex) {
				break;
			}
		}
		Memory :: stack().pop();
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	template<class T, int P, int K, class A>
	void
	Unify<T, P, K, A> :: show (String& string) const {
		matrix_->show (string);
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class T, int P, int K, class A>
	inline void
	Unify<T, P, K, A> :: tryMultyindex
	(
		const Substivector_& substivector,
		const Multyindex_& multyindex
	)
	{
		matrix_ = new Matrix_ (substivector);
		if (!matrix_->unify()) {
			return;
		}
		Finalize_ finalize (this);
		finalize (multyindex);
	}
}
}
}
}
}


