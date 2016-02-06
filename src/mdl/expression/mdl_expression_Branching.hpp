/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_Branching.hpp                             */
/* Description:     general base for expression trees (set of expressions)   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/object/mdl_interface_object_Object.hpp"
#include "mdl/expression/node/mdl_expression_node.hpp"

namespace mdl {
namespace expression {

template
<
	class M,  // Implementation
	class N,  // Node
	class V,  // Value
	class A = allocator :: Heap
>
class Branching : public object :: Object {
public :
	typedef M Implementation_;
	typedef N Node_;
	typedef V Value_;
	typedef A Allocator_;

	typedef
		typename Node_ :: Term_
		Term_;
	typedef
		typename Node_ :: Data_
		Data_;
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
		int P = unify :: policy :: DIRECT,
		int K = unify :: kind :: PLAIN,
		class A1 = allocator :: Stack
	>
	class Equify_ : public Unify<Term_, typename E :: Term_, P, K, A1> {
	};
	template
	<
		class E,
		int P = unify :: policy :: DIRECT,
		int K = unify :: kind :: COMMON,
		class A1 = allocator :: Heap
	>
	class Unify_ : public Unify<Term_, typename E :: Term_, P, K, A1> {
	};
	template
	<
		class E,
		int P = unify :: policy :: SYMMETRIC,
		int K = unify :: kind :: COMMON,
		class A1 = allocator :: Heap
	>
	class FactorUnify_ : public unify :: fact :: Unify<Term_, typename E :: Term_, P, K, A1> {
	};

	Branching();
	~ Branching();

	bool isNull() const;
	bool isEmpty() const;

	Iterator_ getBegin();
	const_Iterator_ getBegin() const;
	value :: Integer getSymbolVolume() const;

	template<class T>
	static const Term_* createTerm (const T* const);

	template<class E>
	Iterator_ addBranch (const E* const, const Value_, const bool addData = true);

	template<class E>
	typename Equify_<E, unify :: policy :: DIRECT> :: Result_  equifyDirect (const E*) const;
	template<class E>
	typename Equify_<E, unify :: policy :: INVERSE> :: Result_ equifyInverse (const E*) const;
	template<class E>
	typename Equify_<E, unify :: policy :: SYMMETRIC> :: Result_ equifySymmetric (const E*) const;

	template<class E>
	typename Unify_<E, unify :: policy :: DIRECT> :: Result_ unifyDirect
	(
		const E*,
		const Substitution_* = NULL,
		const typename E :: Substitution_* = NULL,
		const index :: Step = index :: undefined :: STEP,
		const index :: Step = index :: undefined :: STEP
	) const;
	template<class E>
	typename Unify_<E, unify :: policy :: INVERSE> :: Result_ unifyInverse
	(
		const E*,
		const Substitution_* = NULL,
		const typename E :: Substitution_* = NULL,
		const index :: Step = index :: undefined :: STEP,
		const index :: Step = index :: undefined :: STEP
	) const;
	template<class E>
	typename Unify_<E, unify :: policy :: SYMMETRIC> :: Result_ unifySymmetric
	(
		const E*,
		const index :: Step = index :: undefined :: STEP,
		const index :: Step = index :: undefined :: STEP
	) const;

	template<class E>
	typename FactorUnify_<E> :: Result_ factorUnifySymmetric
	(
		const E*,
		value :: Integer& minDifference,
		const index :: Step = index :: undefined :: STEP,
		const index :: Step = index :: undefined :: STEP
	) const;

	void setKind (const value :: Kind) const;

	// object :: Object interface
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

protected :
	template<class I>
	void copyNode (Iterator_&, const I&) const;
	template<class I>
	bool findNode (Iterator_&, const I&) const;
	template<class I>
	void addFindNode (Iterator_&, const I&) const;

	void setKind (const value :: Kind, const Node_*) const;

	Node_* root_;
	Size_t symbolVolume_;
};

}
}


