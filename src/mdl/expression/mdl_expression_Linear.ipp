/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_Linear.ipp                                */
/* Description:     linear expression base class                             */
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

	/****************************
	 *		Public members
	 ****************************/

	template<template<class> class N, class A>
	inline
	Linear<N, A> :: Linear () {
	}
	template<template<class> class N, class A>
	inline
	Linear<N, A> :: ~ Linear () {
	}

	template<template<class> class N, class A>
	inline typename Linear<N, A> :: const_Iterator_
	Linear<N, A> :: getBegin() const {
		return getTerm()->getBegin();
	}
	template<template<class> class N, class A>
	inline typename Linear<N, A> :: const_Iterator_
	Linear<N, A> :: getEnd() const {
		return getTerm()->getEnd();
	}
	template<template<class> class N, class A>
	inline typename Linear<N, A> :: Iterator_
	Linear<N, A> :: getBegin() {
		return getTerm()->getBegin();
	}
	template<template<class> class N, class A>
	inline typename Linear<N, A> :: Iterator_
	Linear<N, A> :: getEnd() {
		return getTerm()->getEnd();
	}

	template<template<class> class N, class A>
	inline mdl :: Type*
	Linear<N, A> :: getType()
	{
		Term_* term = getTerm();
		return const_cast<mdl :: Type*>(term->getType());
	}
	template<template<class> class N, class A>
	inline const mdl :: Type*
	Linear<N, A> :: getType() const
	{
		const Term_* term = getTerm();
		return term->getType();
	}
	template<template<class> class N, class A>
	inline value :: Integer
	Linear<N, A> :: getLength() const {
		return getTerm()->getLength();
	}
	template<template<class> class N, class A>
	inline value :: Integer
	Linear<N, A> :: getSymbolVolume() const {
		return getTerm()->getSymbolVolume();
	}
	template<template<class> class N, class A>
	inline value :: Integer
	Linear<N, A> :: getComplexity() const {
		return getTerm()->getComplexity();
	}

	template<template<class> class N, class A>
	void
	Linear<N, A> :: write (String& string) const
	{
		if (Config :: expressionsMultyline()) {
			writeMultyline (string, Indent());
		} else {
			writePlain (string);
		}
	}
	template<template<class> class N, class A>
	void
	Linear<N, A> :: write (String& string, const Indent indent) const
	{
		if (Config :: expressionsMultyline()) {
			writeMultyline (string, indent);
		} else {
			writePlain (string);
		}
	}

	template<template<class> class N, class A>
	template<class E>
	bool
	Linear<N, A> :: unifyDirect
	(
		const E* expression,
		const Substitution_*& substitution_1,
		const typename E :: Substitution_*& substitution_2
	) const
	{
		#ifdef DEBUG
		verifyIntegrity();
		#endif
		typedef Linear Expression_1;
		typedef E Expression_2;
		typedef Substitution_ Substitution_1;
		typedef
			typename Expression_2 :: Substitution_
			Substitution_2;
		typedef Term_ Term_1;
		typedef
			typename Expression_2 :: Term_
			Term_2;
		typedef
			Unify
			<
				Term_1,
				Term_2,
				unify :: policy :: DIRECT,
				unify :: kind :: COMMON,
				allocator :: Stack
			>
			Unifier;
		typedef
			typename Unifier :: Unit_
			Unit;

		const Expression_1* expression_1 = this;
		const Expression_2* expression_2 = expression;

		const Unit unit
		(
			expression_1->getBegin(),
			expression_2->getBegin(),
			substitution_2,
			substitution_1
		);
		const typename Unifier :: Result_
			result = Unifier :: proceed (unit);

		if (result.isEmpty()) {
			return false;
		} else {
			substitution_1 = result.getFirst()->getValue().getSecond().getSubstitution();
			substitution_2 = result.getFirst()->getValue().getFirst().getSubstitution();
			return true;
		}
	}
	template<template<class> class N, class A>
	template<class E>
	typename Linear<N, A> ::
	template FactorUnify_<E> :: Result_
	Linear<N, A> :: factorUnifySymmetric
	(
		const E* expression,
		value :: Integer& minDifference
	) const
	{
		#ifdef DEBUG
		verifyIntegrity();
		#endif
		typedef Linear Expression_1;
		typedef E Expression_2;
		typedef Term_ Term_1;
		typedef
			typename Expression_2 :: Term_
			Term_2;
		typedef
			typename unify :: fact :: Unify
			<
				Term_1,
				Term_2,
				unify :: policy :: SYMMETRIC,
				unify :: kind :: COMMON,
				allocator :: Stack
			>
			Unifier;
		typedef
			typename Unifier :: Result_
			Result;
		value :: Integer minDifference_1 = value :: undefined :: INTEGER;
		value :: Integer minDifference_2 = value :: undefined :: INTEGER;
		Unifier unifier;
		Result result = Unifier :: proceed
		(
			getBegin(),
			expression->getBegin(),
			minDifference_1,
			minDifference_2
		);
		if (!result.isEmpty()) {
			minDifference = minDifference_1 + minDifference_2;
		} else {
			minDifference = value :: undefined :: INTEGER;
		}
		return result;
	}
	template<template<class> class N, class A>
	bool
	Linear<N, A> :: unifySymmetric
	(
		const Linear* expression,
		const Substitution_*& substitution
	) const
	{
		#ifdef DEBUG
		verifyIntegrity();
		#endif
		typedef
			Unify
			<
				Term_,
				Term_,
				unify :: policy :: SYMMETRIC,
				unify :: kind :: COMMON,
				allocator :: Stack
			>
			Unifier;
		typedef
			typename Unifier :: Unit_
			Unit;

		const Linear* expression_1 = this;
		const Linear* expression_2 = expression;

		const Unit unit
		(
			expression_1->getBegin(),
			expression_2->getBegin()
		);
		const typename Unifier :: Result_
			result = Unifier :: proceed (unit);

		if (result.isEmpty()) {
			return false;
		} else {
			const Unit unit = result.getFirst()->getValue();
			substitution = unit.template getSubstitution<Allocator_>();
			return true;
		}
	}

using manipulator :: iterate;
using manipulator :: tab;
using manipulator :: space;
using manipulator :: endLine;

	template<template<class> class N, class A>
	inline void
	Linear<N, A> :: showTerms (String& string) const {
		getTerm()->showTerms (string);
	}
	template<template<class> class N, class A>
	void
	Linear<N, A> :: showTypes (String& string) const
	{
		const_Iterator_ i = getBegin();
		const const_Iterator_ end = getEnd();
		set :: value :: Literal shownVariableSet;
		while (true) {
			const Symbol& symbol = *i;
			if (symbol.isVariable() &&
				!shownVariableSet.contains (symbol.getLiteral())) {
				if (!shownVariableSet.isEmpty()) {
					string << ", ";
				}
				shownVariableSet.add (symbol.getLiteral());
				const mdl :: Type* type = symbol.getType();
				symbol.write (string);
				string << space << Token :: colon_ << space;
				type->replicateName (string);
			}
			if (i == end) {
				break;
			}
			++ i;
		}
	}
	template<template<class> class N, class A>
	void
	Linear<N, A> :: writePlain (String& string) const
	{
		const const_Iterator_ begin = getBegin();
		const const_Iterator_ end = getEnd();
		const_Iterator_ iterator = begin;

		while (true) {
			iterator->write (string);
			string << space;
			if (iterator == end) {
				break;
			}
			++ iterator;
		}
	}
	template<template<class> class N, class A>
	inline void
	Linear<N, A> :: writeMultyline (String& string, const Indent indent) const
	{
		if (getTerm()->getLength() >= Config :: multylineMaxWidth()) {
			string << endLine << indent;
		}
		getTerm()->writeMultylineForward (string, indent, 0);
	}

	template<template<class> class N, class A>
	template<class I>
	inline void
	Linear<N, A> :: copyNode (Iterator_& target, const I& source) {
		*target = static_cast<const Symbol&>(*source);
	}
	template<template<class> class N, class A>
	template<class I>
	inline bool
	Linear<N, A> :: findNode (Iterator_& target, const I& source) {
		return getTerm()->template findNode<I> (target, source);
	}
	template<template<class> class N, class A>
	template<class I>
	inline void
	Linear<N, A> :: addFindNode (Iterator_& target, const I& source) {
		getTerm()->template addFindNode<I> (target, source);
	}

	template<template<class> class N, class A>
	inline bool
	Linear<N, A> :: operator == (const Linear& expression) const {
		#ifdef DEBUG
		verifyIntegrity();
		#endif
		return (*getTerm() == *expression.getTerm());
	}
	template<template<class> class N, class A>
	inline bool
	Linear<N, A> :: operator != (const Linear& expression) const {
		return !(operator == (expression));
	}
	template<template<class> class N, class A>
	template<template<class> class N1, class A1>
	inline bool
	Linear<N, A> :: coinsides (const Linear<N1, A1>& expression) const
	{
		#ifdef DEBUG
		verifyIntegrity();
		#endif
		typedef Term_ Term_0;
		typedef Linear<N1, A1> Linear1;
		typedef
			typename Linear1 :: Term_
			Term_1;
		const Term_0* const
			term_0 = getTerm();
		const Term_1* const
			term_1 = expression.getTerm();
		const bool result = term_0->coinsides (*term_1);
		/*if (!result) {
			String str (1024);
			str << "***** term_0 *****" << endLine;
			term_0->showTerms (str);
			str << "***** term_1 *****" << endLine;
			term_1->showTerms (str);
			std :: cout << str << std ::endl;
		}*/
		return result;
	}

	template<template<class> class N, class A>
	inline void
	Linear<N, A> :: setKind (const value :: Kind kind) const {
		getTerm()->setKind (kind);
	}
	template<template<class> class N, class A>
	void
	Linear<N, A> :: setReplaceable (const bool variablesAreReplaceabe)
	{
		const Iterator_ begin = getBegin();
		const Iterator_ end = getEnd();
		Iterator_ iterator = begin;

		while (true) {
			iterator->setReplaceable (variablesAreReplaceabe);
			if (iterator == end) {
				break;
			}
			++ iterator;
		}
	}

	template<template<class> class N, class A>
	inline void
	Linear<N, A> :: verifyIntegrity () const
	{
		const Term_* term = getTerm();
		if (term == NULL) {
			Error* error = new Error (Error :: SEMANTIC);
			error->message() << "unparsed term:" << endLine;
			error->message() << *this << endLine;
			throw error;
		}
		try {
			term->verifyIntegrity (true);
		} catch (Error* error) {
			error->message() << "integrity verification fail:" << endLine;
			error->message() << *this << endLine;
			throw error;
		}
	}

	// object :: Object interface
	template<template<class> class N, class A>
	Size_t
	Linear<N, A> :: getVolume() const
	{
		Size_t volume = 0;
		const const_Iterator_ begin = getBegin();
		const const_Iterator_ end = getEnd();
		const_Iterator_ iterator = begin;

		while (true) {
			volume += iterator->getVolume();
			volume += iterator->getSizeOf();
			if (iterator == end) {
				break;
			}
			++ iterator;
		}
		return volume;
	}
	template<template<class> class N, class A>
	inline Size_t
	Linear<N, A> :: getSizeOf() const {
		return sizeof (Linear);
	}
	template<template<class> class N, class A>
	inline void
	Linear<N, A> :: show (String& string) const
	{
		if (Config :: expressionsMultyline()) {
			writeMultyline (string, Indent());
		} else {
			writePlain (string);
		}
	}

	/****************************
	 *		Private members
	 ****************************/
}
}


