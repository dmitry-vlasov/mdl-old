/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_sub_prod_Finalize.ipp                */
/* Description:     scalar substitution unifier module                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_UNIFY_SUB_PROD_FINALIZE_IPP_
#define MDL_EXPRESSION_UNIFY_SUB_PROD_FINALIZE_IPP_

namespace mdl {
namespace expression {
namespace unify {
namespace sub {
namespace prod {

	/****************************
	 *		Public members
	 ****************************/

	template<class U, class T>
	inline
	Finalize<U, T> :: Finalize (Unifier_* unifier) :
	dimension_ (unifier->dimension_),
	substitutionInt_ (unifier->substitutionInt_),
	evidences_ (unifier->evidences_),
	matrix_ (unifier->matrix_) {
	}

	template<class U, class T>
	inline void
	Finalize<U, T> :: operator() (const Multyindex_& multyindex)
	{
		Memory :: stack().push();
		const InnerSubstitution_* theta = createTheta();
		Evidence_* evidenceUp [dimension_];
		for (index :: Arity i = 0; i < dimension_; ++ i) {
			evidenceUp [i] = multyindex.getValue (i);
		}
		sub :: template Finaly<InnerSubstitution_, Types_> :: finalize (
			theta,
			matrix_->variables_.getSize(),
			substitutionInt_->template castAway<allocator :: Stack>(),
			matrix_->delta_,
			evidences_,
			evidenceUp,
			dimension_
		);
		Memory :: stack().pop();
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;


	/****************************
	 *		Private members
	 ****************************/

	template<class U, class T>
	typename Finalize<U, T> :: InnerSubstitution_*
	Finalize<U, T> :: createTheta()
	{
		InnerSubstitution_* theta = NULL;
		for (index :: Arity i = 0; i < matrix_->dimensionY_; ++ i) {
			const InnerExpression_*
				innerExpression = NULL;
			const InnerExprevector_*
				exprevector = matrix_->exprematrix_.getValue (i);
			for (index :: Arity j = 0; j < matrix_->dimensionX_; ++ j) {
				innerExpression = exprevector->getValue (j);
				if (innerExpression != NULL) {
					break;
				}
			}
			if (innerExpression != NULL) {
				const InnerTerm_* const
					term = InnerExpression_ :: createTerm (innerExpression->getTerm());
				const Symbol&
					variable = matrix_->variables_.getValue (i);
				if (*term == variable) {
					continue;
				}
				theta = new InnerSubstitution_
				(
					matrix_->variables_.getValue (i),
					term, theta, true
				);
			}
		}
		return theta;
	}
}
}
}
}
}

#endif /*MDL_EXPRESSION_UNIFY_SUB_PROD_FINALIZE_IPP_*/
