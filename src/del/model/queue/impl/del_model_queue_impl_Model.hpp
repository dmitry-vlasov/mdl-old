/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_queue_impl_Model.hpp                          */
/* Description:     model of a theory                                        */
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
namespace queue {
namespace impl {

template<class A = allocator :: Heap>
class Model :
	public queue :: Model,
	public Scalar<Model<A>, A> {
public :
	typedef A Allocator_;

	Model();
	Model (const del :: Theory*);
	virtual ~ Model();

	// del :: Model interface
	virtual void build (const Theory* T, del :: model :: Model* = NULL);
	virtual bool isTrueSubseteq (const Symbol, const Symbol) const;

	// del :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	template<class>
	friend class Model;

	typedef
		del :: set :: Set
		<
			queue :: Domain,
			storage :: ByPointer,
			Allocator_
		>
		DomainSet_;
	typedef
		del :: set :: Set
		<
			queue :: Range,
			storage :: ByPointer,
			Allocator_
		>
		RangeSet_;
	typedef
		del :: set :: Set
		<
			value :: Variable,
			storage :: ByValue,
			Allocator_
		>
		ConceptSet_;

	void initQueueMap (const del :: Theory* theory);
	void initSimpleQueueMap (const del :: Formula* formula);
	void initConjQueueMap (const del :: Formula* formula);
	void initRightExistsQueueMap (const del :: Formula* formula);
	void initLeftExistsQueueMap (const del :: Formula* formula);
	void initConceptQueueMap (const del :: Formula* formula, const value :: Variable);
	void addDomainRangePair (queue :: Domain*, queue :: Range*);

	void processVicinity (ConceptSet_&, del :: model :: Model* model);
	bool processQueueElement (const value :: Variable, queue :: Range*, ConceptSet_&);
	bool processSimpleElement (const value :: Variable, queue :: Range*, ConceptSet_&);
	bool processConjElement (const value :: Variable, queue :: Range*, ConceptSet_&);
	bool processExistsElement (const value :: Variable, queue :: Range*, ConceptSet_&);

	enum {
		INITIAL_DOMAIN_SET_CAPACITY = 1024 * 4,
		INITIAL_RANGE_SET_CAPACITY  = 1024 * 4
	};

	queue :: Map* queueMap_;
	queue :: PredicateMap* predicateMap_;
	queue :: RelationMap*  relationMap_;

	DomainSet_ domainSet_;
	RangeSet_  rangeSet_;
};

}
}
}
}


