/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_Structure.hpp                                  */
/* Description:     structure - model of a theory                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface.hpp"
#include "del/model/interpretation/del_model_interpretation.hpp"

namespace del {
namespace model {

template<class A = allocator :: Heap>
class Structure :
	public Model,
	public Scalar<Structure<A>, A> {
public :
	typedef A Allocator_;
	typedef
		typename interpretation :: RelationMap<Allocator_>
		RelationMap_;
	typedef
		typename interpretation :: PredicateMap<Allocator_>
		PredicateMap_;
	typedef
		typename PredicateMap_ :: Predicate_
		Predicate_;
	typedef
		typename Predicate_ :: Singleton_
		Singleton_;
	typedef
		typename RelationMap_ :: Relation_
		Relation_;
	typedef
		typename RelationMap_ :: Pair_
		Pair_;

	Structure();
	Structure (const del :: Theory*);
	Structure (const Structure&);
	Structure (const del :: Model*);
	virtual ~ Structure();

	// del :: Model interface

	// build M such that M |- T
	virtual void build (const del :: Theory* T);

	// check if T |- phi
	virtual bool satisfies (const del :: Theory*, const del :: Formula*);

	// check if T |- a ⊑ b
	virtual bool isTrueSubseteq (const Symbol a, const Symbol b) const;

	// check if T \ U |- a ⊑ b
	virtual bool isTrueSubseteq
	(
		const Symbol a,
		const Symbol b,
		const del :: set :: Formula* U
	) const;

	// eval such d of signature delta, that T |- a ⊑ d and T |- d ⊑ b
	virtual const del :: Term* evalInterpolant
	(
		const Symbol a,
		const Symbol b,
		const del :: Signature* delta
	) const;

	virtual bool isEqual (const Model*, const bool show = false) const;
	virtual value :: Integer getSize() const;
	virtual const Node* getNode (const value :: Integer) const;
	virtual void registerNode (Node*);
	virtual void clearNodes();

	virtual PredicateMap& predicates();
	virtual RelationMap&  relations();
	virtual const PredicateMap& getPredicates() const;
	virtual const RelationMap&  getRelations() const;

	// del :: Cloneable interface
	virtual del :: Model* clone() const;

	// del :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	template<class>
	friend class Structure;

	typedef
		del :: vector :: Vector
		<
			Node*,
			storage :: ByValue,
			Allocator_
		>
		NodeVector_;
	typedef
		del :: vector :: Vector
		<
			Node*,
			storage :: ByValue,
			Allocator_
		>
		PositiveNodeVector_;
	typedef
		del :: vector :: Vector
		<
			Node,
			storage :: ByPointer,
			Allocator_
		>
		NegativeNodeVector_;

	NodeVector_         nodeVector_;
	PositiveNodeVector_ positiveNodeVector_;
	NegativeNodeVector_ negativeNodeVector_;
	PredicateMap_ predicateMap_;
	RelationMap_  relationMap_;
	enum {
		INITIAL_NODE_VECTOR_CAPACITY = 1024
	};
};

}
}


