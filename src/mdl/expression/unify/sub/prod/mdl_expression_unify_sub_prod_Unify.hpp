/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_sub_prod_Unify.hpp                  */
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

template
<
	class T,
	int P = policy :: SYMMETRIC,
	int K = kind :: COMMON,
	class A = allocator :: Stack
>
class Unify : public Scalar<A> {
public :
	typedef T Types_;
	enum { policy_ = P };
	enum { kind_ = K };
	typedef A Allocator_;

	typedef
		typename Types_ :: Expression_
		Expression_;
	typedef
		typename Types_ :: Evidences_
		Evidences_;
	typedef
		typename Types_ :: Evidence_
		Evidence_;
	typedef
		typename Types_ :: Matrix_
		Input_;
	typedef
		Evidences_ Container_;

	typedef Matrix<Types_, policy_, kind_, Allocator_> Matrix_;
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
	typedef
		Multyindex<Container_, Types_>
		Multyindex_;

	Unify
	(
		const index :: Arity,
		const Substitution_*,
		Evidences_&
	);

	void operator() (const Input_&);
	void show (String&) const;

private :
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
		vector :: Vector
		<
			InnerExpression_*,
			storage :: ByValue,
			Allocator_
		>
		InnerExprevector_;

	template<class, class>
	friend class Finalize;
	typedef Finalize<Unify, Types_> Finalize_;

	void tryMultyindex (const Substivector_&, const Multyindex_&);

	const index :: Arity dimension_;
	const Substitution_* substitutionInt_;
	Evidences_& evidences_;
	Matrix_* matrix_;
};

}
}
}
}
}


