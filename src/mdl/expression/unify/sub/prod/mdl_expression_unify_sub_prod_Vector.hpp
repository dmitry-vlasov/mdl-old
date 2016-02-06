/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_unify_sub_prod_Vector.hpp                 */
/* Description:     most general  vector unifier module                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/expression/unify/sub/prod/mdl_expression_unify_sub_prod.dpp"

namespace mdl {
namespace expression {
namespace unify {
namespace sub {
namespace prod {

template<class M, class E, int P, int K, class A>
class Vector : public Scalar<Vector<M, E, P, K, A>, A> {
public :
	typedef A Allocator_;
	typedef E Expression_;
	typedef M Matrix_;
	enum { policy_ = P };
	enum { kind_ = K };
	typedef
		typename Expression_ :: Term_
		Term_;
	typedef
		Substitution<Term_>
		Substitution_;
	typedef
		vector :: Vector
		<
			Expression_*,
			storage :: ByValue,
			Allocator_
		>
		Exprevector_;
	typedef
		typename Expression_ :: const_Iterator_
		Iterator_;
	typedef
		typename Substitution_ :: Substiunit_
		Substiunit_;

	Vector
	(
		const Matrix_*,
		const index :: Arity,
		Substitution_*&,
		Substitution_*&
	);

	bool unify (const Exprevector_*);
	void show (String&) const;

private :
	typedef
		vector :: Vector
		<
			Iterator_,
			storage :: ByValue,
			Allocator_
		>
		Itervector_;
	typedef
		vector :: Vector
		<
			const Term_*,
			storage :: ByValue,
			Allocator_
		>
		Diffvector_;

	void calculateDifference();
	bool initItervector();
	bool incItervector();
	bool hasDifference() const;
	void buildDifference();

	typedef
		Unit<Expression_, Substiunit_, policy_, kind_>
		Unit_;

	const Substiunit_* findUnit() const;
	bool useUnit (const Substiunit_*);

	const Matrix_* matrix_;
	const index :: Arity dimension_;
	Substitution_*& delta_;
	Substitution_*& epsilon_;
	const Exprevector_* exprevector_;
	Itervector_ itervector_;
	Diffvector_ diffvector_;
};

	template<class M, class E, int P, int K, class A>
	String&
	operator << (String&, const Vector<M, E, P, K, A>&);
	template<class M, class E, int P, int K, class A>
	std :: ostream&
	operator << (std :: ostream&, const Vector<M, E, P, K, A>&);
}
}
}
}
}


