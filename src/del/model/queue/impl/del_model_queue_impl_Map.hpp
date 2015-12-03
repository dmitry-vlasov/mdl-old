/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_queue_impl_Map.hpp                            */
/* Description:     mapping from domain to the range                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_MODEL_QUEUE_IMPL_MAP_HPP_
#define DEL_MODEL_QUEUE_IMPL_MAP_HPP_

#include "del/interface/del_interface.hpp"
#include "del/model/interpretation/del_model_interpretation.hpp"

namespace del {
namespace model {
namespace queue {
namespace impl {

template<class A = allocator :: Heap>
class Map :
	public queue :: Map,
	public Scalar<Map<A>, A> {
public :
	typedef A Allocator_;

	Map();
	virtual ~ Map();

	// queue :: Map interface
	virtual const queue :: set :: Range* map (Domain*) const;
	virtual queue :: set :: Range* map (Domain*);
	virtual del :: model :: queue :: set :: Range* map (const value :: Variable);
	virtual del :: model :: queue :: set :: Range* map (const value :: Variable, const value :: Relation);

	// del :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	template<class>
	friend class Map;
	typedef
		del :: vector :: Vector
		<
			queue :: set :: Range,
			storage :: ByPointer,
			Allocator_
		>
		RangeVector_;

	// concept (simple) part of a mapping
	typedef
		map :: Scalar
		<
			value :: Variable,
			value :: Integer,
			Allocator_
		>
		ConceptMap_;

	// exists part of a mapping
	typedef
		del :: vector :: Vector
		<
			ConceptMap_,
			storage :: ByPointer,
			Allocator_
		>
		ExistsVector_;
	typedef
		map :: Scalar
		<
			value :: Relation,
			value :: Integer,
			Allocator_
		>
		ExistsMap_;

	enum {
		INITIAL_RANGE_VECTOR_CAPACITY = 32,
		INITIAL_CONCEPT_MAP_CAPACITY = 32,
		INITIAL_EXISTS_VECTOR_CAPACITY = 32,
		INITIAL_EXISTS_MAP_CAPACITY = 32,
	};

	RangeVector_ rangeVector_;
	ConceptMap_  conceptMap_;

	ExistsVector_ existsVector_;
	ExistsMap_    existsMap_;
};

}
}
}
}

#endif /*DEL_MODEL_QUEUE_IMPL_MAP_HPP_*/
