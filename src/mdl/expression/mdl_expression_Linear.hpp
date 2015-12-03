/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_Linear.hpp                                */
/* Description:     linear expression base class                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_LINEAR_HPP_
#define MDL_EXPRESSION_LINEAR_HPP_

#include "mdl/interface/object/mdl_interface_object_Object.hpp"

namespace mdl {
namespace expression {

template
<
	template<class> class N,
	class A = allocator :: Heap
>
class Linear : public object :: Object {
public :
	typedef A Allocator_;
	typedef N<Allocator_> Node_;
	typedef
		typename Node_ :: Term_
		Term_;
	typedef
		typename Term_ :: Substitution_
		Substitution_;
	typedef
		typename Term_ :: const_Iterator_
		const_Iterator_;
	typedef
		typename Term_ :: Iterator_
		Iterator_;

	template
	<
		class E,
		int P = unify :: policy :: SYMMETRIC,
		int K = unify :: kind :: COMMON,
		class A1 = allocator :: Heap
	>
	class FactorUnify_ : public unify :: fact :: Unify<Term_, typename E :: Term_, P, K, A1> {
	};

	Linear();
	virtual ~ Linear();

	Iterator_ getBegin();
	Iterator_ getEnd();
	const_Iterator_ getBegin() const;
	const_Iterator_ getEnd() const;

	mdl :: Type* getType();
	const mdl :: Type* getType() const;
	value :: Integer getLength() const;
	value :: Integer getSymbolVolume() const;
	value :: Integer getComplexity() const;

	virtual const Term_* getTerm() const = 0;
	virtual Term_* getTerm() = 0;

	void write (String&) const;
	void write (String&, const Indent) const;

	template<class E>
	bool unifyDirect
	(
		const E*,
		const Substitution_*&,
		const typename E :: Substitution_*&
	) const;
	template<class E>
	typename FactorUnify_<E> :: Result_ factorUnifySymmetric (const E*, value :: Integer&) const;
	bool unifySymmetric (const Linear*, const Substitution_*&) const;

	void showTerms (String&) const;
	void showTypes (String&) const;
	void writePlain (String&) const;
	void writeMultyline (String&, const Indent) const;

	template<class I>
	void copyNode (Iterator_&, const I&);
	template<class I>
	bool findNode (Iterator_&, const I&);
	template<class I>
	void addFindNode (Iterator_&, const I&);

	bool operator == (const Linear&) const;
	bool operator != (const Linear&) const;
	template<template<class> class N1, class A1>
	bool coinsides (const Linear<N1, A1>&) const;

	void setKind (const value :: Kind) const;
	void setReplaceable (const bool);
	void verifyIntegrity() const;

	// object :: Object interface
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;
};

}
}

#endif /*MDL_EXPRESSION_LINEAR_HPP_*/
