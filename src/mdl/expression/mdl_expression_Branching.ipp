/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_Branching.ipp                             */
/* Description:     general base for expression trees (set of expressions)   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/auxiliary/mdl_auxiliary.hpp"

namespace mdl {
namespace expression {

	/****************************
	 *		Public members
	 ****************************/

	template<class M, class N, class V, class A>
	inline
	Branching<M, N, V, A> :: Branching() :
	root_ (NULL),
	symbolVolume_ (0) {
	}
	template<class M, class N, class V, class A>
	inline
	Branching<M, N, V, A> :: ~ Branching()
	{
		if (root_ != NULL) {
			root_->deleteNodes();
			delete root_;
			root_ = NULL;
		}
	}

	template<class M, class N, class V, class A>
	inline bool
	Branching<M, N, V, A> :: isNull() const {
		return (root_ == NULL);
	}
	template<class M, class N, class V, class A>
	inline bool
	Branching<M, N, V, A> :: isEmpty() const {
		return (root_ == NULL);
	}

	template<class M, class N, class V, class A>
	inline typename Branching<M, N, V, A> :: Iterator_
	Branching<M, N, V, A> :: getBegin() {
		return Iterator_ (root_);
	}
	template<class M, class N, class V, class A>
	inline typename Branching<M, N, V, A> :: const_Iterator_
	Branching<M, N, V, A> :: getBegin() const {
		return const_Iterator_ (root_);
	}
	template<class M, class N, class V, class A>
	inline value :: Integer
	Branching<M, N, V, A> :: getSymbolVolume() const {
		return symbolVolume_;
	}

	template<class M, class N, class V, class A>
	template<class T>
	inline const typename Branching<M, N, V, A> :: Term_*
	Branching<M, N, V, A> :: createTerm (const T* const term)
	{
		typedef T Term;
		return Builder<Implementation_, Term> :: build (term);
	}

	template<class M, class N, class V, class A>
	template<class E>
	inline typename Branching<M, N, V, A> :: Iterator_
	Branching<M, N, V, A> :: addBranch
	(
		const E* const expression,
		const Value_ value,
		const bool addData
	)
	{
		typedef E Expression;
		typedef
			typename Expression :: Term_
			Term;
		const bool addRoot = isEmpty();
		Term_* term = NULL;
		if (addData) {
			Builder<Implementation_, Term> builder (expression->getTerm());
			term = builder.build (dynamic_cast<Implementation_*>(this));
			term->getEnd()->getData().addValue (value);
		} else {
			Builder<Implementation_, Term, Value_> builder (expression->getTerm(), value);
			term = builder.build (dynamic_cast<Implementation_*>(this));
		}
		if (addRoot) {
			root_ = term->getBegin().getNode();
		}
		symbolVolume_ += expression->getSymbolVolume();
		return term->getEnd();
	}

	template<class M, class N, class V, class A>
	template<class E>
	typename Branching<M, N, V, A> ::
	template Equify_<E, unify :: policy :: DIRECT> :: Result_
	Branching<M, N, V, A> :: equifyDirect (const E* expression) const
	{
		typedef Branching Expression_1;
		typedef E Expression_2;
		typedef
			Equify_<E, unify :: policy :: DIRECT>
			Equifier;
		typedef
			typename Equifier :: Result_
			Result;
		typedef
			typename Equifier :: Unit_
			Unit;

		if (root_ == NULL) {
			return Result();
		}
		const Expression_1* expression_1 = this;
		const Expression_2* expression_2 = expression;

		const Unit unit
		(
			expression_1->getBegin(),
			expression_2->getBegin()
		);
		return Equifier :: proceed (unit);
	}
	template<class M, class N, class V, class A>
	template<class E>
	typename Branching<M, N, V, A> ::
	template Equify_<E, unify :: policy :: INVERSE> :: Result_
	Branching<M, N, V, A> :: equifyInverse (const E* expression) const
	{
		typedef Branching Expression_1;
		typedef E Expression_2;
		typedef
			Equify_<E, unify :: policy :: INVERSE>
			Equifier;
		typedef
			typename Equifier :: Result_
			Result;
		typedef
			typename Equifier :: Unit_
			Unit;

		if (root_ == NULL) {
			return Result();
		}
		const Expression_1* expression_1 = this;
		const Expression_2* expression_2 = expression;

		const Unit unit
		(
			expression_1->getBegin(),
			expression_2->getBegin()
		);
		return Equifier :: proceed (unit);
	}
	template<class M, class N, class V, class A>
	template<class E>
	typename Branching<M, N, V, A> ::
	template Equify_<E, unify :: policy :: SYMMETRIC> :: Result_
	Branching<M, N, V, A> :: equifySymmetric (const E* expression) const
	{
		typedef Branching Expression_1;
		typedef E Expression_2;
		typedef
			Equify_<E, unify :: policy :: SYMMETRIC>
			Equifier;
		typedef
			typename Equifier :: Result_
			Result;
		typedef
			typename Equifier :: Unit_
			Unit;

		if (root_ == NULL) {
			return Result();
		}
		const Expression_1* expression_1 = this;
		const Expression_2* expression_2 = expression;

		const Unit unit
		(
			expression_1->getBegin(),
			expression_2->getBegin()
		);
		return Equifier :: proceed (unit);
	}

	template<class M, class N, class V, class A>
	template<class E>
	typename Branching<M, N, V, A> ::
	template Unify_<E, unify :: policy :: DIRECT> :: Result_
	Branching<M, N, V, A> :: unifyDirect
	(
		const E* expression,
		const Substitution_* substitution_1,
		const typename E :: Substitution_* substitution_2,
		const index :: Step level_1,
		const index :: Step level_2
	) const
	{
		typedef Branching Expression_1;
		typedef E Expression_2;
		typedef
			Unify_<Expression_2, unify :: policy :: DIRECT>
			Unifier;
		typedef
			typename Unifier :: Result_
			Result;
		typedef
			typename Unifier :: Unit_
			Unit;

		if (root_ == NULL) {
			return Result();
		}
		const Expression_1* expression_1 = this;
		const Expression_2* expression_2 = expression;

		const Unit unit
		(
			expression_1->getBegin(),
			expression_2->getBegin(),
			substitution_2,
			substitution_1,
			level_1,
			level_2
		);
		return Unifier :: proceed (unit);
	}
	template<class M, class N, class V, class A>
	template<class E>
	typename Branching<M, N, V, A> ::
	template Unify_<E, unify :: policy :: INVERSE> :: Result_
	Branching<M, N, V, A> :: unifyInverse
	(
		const E* expression,
		const Substitution_* substitution_1,
		const typename E :: Substitution_* substitution_2,
		const index :: Step level_1,
		const index :: Step level_2
	) const
	{
		typedef Branching Expression_1;
		typedef E Expression_2;
		typedef
			Unify_<Expression_2, unify :: policy :: INVERSE>
			Unifier;
		typedef
			typename Unifier :: Result_
			Result;
		typedef
			typename Unifier :: Unit_
			Unit;

		if (root_ == NULL) {
			return Result();
		}
		const Expression_1* expression_1 = this;
		const Expression_2* expression_2 = expression;

		const Unit unit
		(
			expression_1->getBegin(),
			expression_2->getBegin(),
			substitution_2,
			substitution_1,
			level_1,
			level_2
		);
		return Unifier :: proceed (unit);
	}
	template<class M, class N, class V, class A>
	template<class E>
	typename Branching<M, N, V, A> ::
	template Unify_<E, unify :: policy :: SYMMETRIC> :: Result_
	Branching<M, N, V, A> :: unifySymmetric
	(
		const E* expression,
		const index :: Step level_1,
		const index :: Step level_2
	) const
	{
		typedef Branching Expression_1;
		typedef E Expression_2;
		typedef
			Unify_<Expression_2, unify :: policy :: SYMMETRIC>
			Unifier;
		typedef
			typename Unifier :: Result_
			Result;
		typedef
			typename Unifier :: Unit_
			Unit;

		if (root_ == NULL) {
			return Result();
		}
		const Expression_1* expression_1 = this;
		const Expression_2* expression_2 = expression;

		const Unit unit
		(
			expression_1->getBegin(),
			expression_2->getBegin(),
			level_1,
			level_2
		);
		return Unifier :: proceed (unit);
	}

	template<class M, class N, class V, class A>
	template<class E>
	typename Branching<M, N, V, A> ::
	template FactorUnify_<E> :: Result_
	Branching<M, N, V, A> :: factorUnifySymmetric
	(
		const E* expression,
		value :: Integer& minDifference,
		const index :: Step level_1,
		const index :: Step level_2
	) const
	{
		typedef Branching Expression_1;
		typedef E Expression_2;
		typedef
			FactorUnify_<Expression_2>
			Unifier;
		typedef
			typename Unifier :: Result_
			Result;
		if (root_ == NULL) {
			return Result();
		}
		const Expression_1* expression_1 = this;
		const Expression_2* expression_2 = expression;
		value :: Integer minDifference_1 = value :: undefined :: INTEGER;
		value :: Integer minDifference_2 = value :: undefined :: INTEGER;
		Result result = Unifier :: proceed
		(
			expression_1->getBegin(),
			expression_2->getBegin(),
			minDifference_1,
			minDifference_2,
			level_1,
			level_2
		);
		if (!result.isEmpty()) {
			minDifference = minDifference_1 + minDifference_2;
		} else {
			minDifference = value :: undefined :: INTEGER;
		}
		return result;
	}
	template<class M, class N, class V, class A>
	inline void
	Branching<M, N, V, A> :: setKind (const value :: Kind kind) const {
		setKind (kind, root_);
	}

using manipulator :: endLine;
using manipulator :: tab;

	// object :: Object interface
	template<class M, class N, class V, class A>
	Size_t
	Branching<M, N, V, A> :: getVolume() const
	{
		Size_t volume = 0;
		if (root_ != NULL) {
			volume += root_->getVolume();
			volume += root_->getSizeOf();
		}
		return volume;
	}
	template<class M, class N, class V, class A>
	Size_t
	Branching<M, N, V, A> :: getSizeOf() const {
		return sizeof (Branching);
	}
	template<class M, class N, class V, class A>
	void
	Branching<M, N, V, A> :: show (String& string) const
	{
		string << "tree:" << endLine;
		string << "symbol volume: " << symbolVolume_ << endLine;
		if (root_ != NULL) {
			root_->showTree (string);
		} else {
			string << tab << "NULL";
		}
		string << endLine;
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class M, class N, class V, class A>
	template<class I>
	void
	Branching<M, N, V, A> :: copyNode (Iterator_& target, const I& source) const {
		*target = static_cast<const Symbol&>(*source);
	}
	template<class M, class N, class V, class A>
	template<class I>
	bool
	Branching<M, N, V, A> :: findNode (Iterator_& target, const I& source) const
	{
		while (true) {
			if (*target == *source) {
				return true;
			}
			+ target;
		}
		return false;
	}
	template<class M, class N, class V, class A>
	template<class I>
	void
	Branching<M, N, V, A> :: addFindNode (Iterator_& target, const I& source) const
	{
		while (true) {
			if (*target == *source) {
				break;
			}
			if (target->isUndefined()) {
				*target = static_cast<const Symbol&>(*source);
				break;
			}
			+ target;
		}
	}

	template<class M, class N, class V, class A>
	void
	Branching<M, N, V, A> :: setKind (const value :: Kind kind, const Node_* node) const
	{
		if (node == NULL) {
			return;
		}
		const_cast<Node_*>(node)->setKind (kind);
		const Node_* left = node->goLeft();
		const Node_* up = node->goUp();
		setKind (kind, left);
		setKind (kind, up);
	}
}
}


