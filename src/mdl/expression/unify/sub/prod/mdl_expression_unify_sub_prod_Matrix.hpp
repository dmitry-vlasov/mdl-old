/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_sub_prod_Matirx.hpp                 */
/* Description:     most general matrix unifier module                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_UNIFY_SUB_PROD_MATRIX_HPP_
#define MDL_EXPRESSION_UNIFY_SUB_PROD_MATRIX_HPP_

#include "mdl/expression/unify/sub/prod/mdl_expression_unify_sub_prod_Vector.hpp"
#include "mdl/expression/mdl_expression_List.hpp"

namespace mdl {
namespace expression {
namespace unify {
namespace sub {
namespace prod {

template<class T, int P, int K, class A>
class Matrix : public Scalar<Matrix<T, P, K, A>, A> {
public :
	typedef T Types_;
	enum { policy_ = P };
	enum { kind_ = K };
	typedef A Allocator_;
	typedef
		typename Types_ :: Expression_
		Expression_;
	typedef
		typename Expression_ :: Term_
		Term_;
	typedef
		Substitution<typename Expression_ :: Term_>
		Substitution_;
	typedef
		vector :: Vector
		<
			const Substitution_*,
			storage :: ByValue,
			Allocator_
		>
		Substivector_;

	Matrix (const Substivector_&);

	bool unify();
	void show (String&) const;

private :
	template<class, class>
	friend class Finalize;
	template<class, class, int, int, class>
	friend class Vector;

	typedef
		List<Allocator_>
		InnerExpression_;
	typedef
		typename InnerExpression_ :: Term_
		InnerTerm_;
	typedef
		Substitution<InnerTerm_>
		InnerSubstitution_;
	typedef
		typename InnerSubstitution_ :: Substiunit_
		Substiunit_;
	typedef
		vector :: Vector
		<
			InnerExpression_*,
			storage :: ByValue,
			Allocator_
		>
		InnerExprevector_;
	typedef
		vector :: Vector
		<
			InnerExprevector_*,
			storage :: ByValue,
			Allocator_
		>
		InnerExprematrix_;
	typedef
		vector :: Vector
		<
			Symbol,
			storage :: ByValue,
			Allocator_
		>
		Variables_;
	typedef
		Vector
		<
			Matrix,
			InnerExpression_,
			policy_, kind_,
			Allocator_
		>
		Vector_;

	void calculateVariables();
	void fillMatrix();
	void executeDelta();

	void verifyIntegrity() const;
	void verifyColumn (const InnerExprevector_*) const;
	void verifyExpressions (const bool show = false) const;

	const Substivector_& data_;

	const index :: Arity dimensionX_;
	const index :: Arity dimensionY_;

	Variables_          variables_;
	InnerExprematrix_   exprematrix_;
	InnerSubstitution_* delta_;
	InnerSubstitution_* epsilon_;
	Vector_             vectorUnifier_;
};

	template<class T, int P, int K, class A>
	String&
	operator << (String&, const Matrix<T, P, K, A>&);
	template<class T, int P, int K, class A>
	std :: ostream&
	operator << (std :: ostream&, const Matrix<T, P, K, A>&);

}
}
}
}
}

#endif /*MDL_EXPRESSION_UNIFY_SUB_PROD_MATRIX_HPP_*/
