/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_queue_impl_RelationMap.hpp                     */
/* Description:     predicate map in queue models                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_MODEL_QUEUE_IMPL_RELATION_MAP_HPP_
#define DEL_MODEL_QUEUE_IMPL_RELATION_MAP_HPP_

#include "del/interface/del_interface.hpp"

namespace del {
namespace model {
namespace queue {
namespace impl {

template<class A>
class RelationMap :
	public queue :: RelationMap,
	public Scalar<RelationMap<A>, A> {
public :
	typedef A Allocator_;

	RelationMap();
	virtual ~ RelationMap();

	// queue :: RelationMap interface
	virtual value :: Integer getSize() const;
	virtual queue :: Relation* get (const value :: Integer);
	virtual queue :: Relation* map (const value :: Relation);

	// del :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	typedef
		Relation<Allocator_>
		Relation_;

	typedef
		map :: Scalar
		<
			value :: Relation,
			value :: Integer,
			Allocator_
		>
		RelationMap_;

	typedef
		del :: vector :: Vector
		<
			Relation_,
			storage :: ByPointer,
			Allocator_
		>
		RelationVector_;

	enum {
		INITIAL_RELATION_VECTOR_CAPACITY = 256
	};

	RelationMap_    relationMap_;
	RelationVector_ relationVector_;
};

}
}
}
}

#endif /*DEL_MODEL_QUEUE_IMPL_RELATION_MAP_HPP_*/
