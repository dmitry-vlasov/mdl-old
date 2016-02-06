/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_queue_impl_Relation.hpp                        */
/* Description:     relations in queue models                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface.hpp"

namespace del {
namespace model {
namespace queue{
namespace impl {

template<class A>
class Relation :
	public queue :: Relation,
	public Scalar<Relation<A>, A>{
public :
	typedef A Allocator_;

	Relation();
	virtual ~ Relation();

	// queue :: Relation interface
	virtual void addPair (const value :: Variable, const value :: Variable);
	virtual bool isTrue (const value :: Variable, const value :: Variable) const;

	// del :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	class Pair;

	typedef
		del :: set :: Set
		<
			Pair,
			storage :: ByValue,
			Allocator_
		>
		RelationSet_;

	enum {
		INITIAL_RELATION_SET_CAPACITY = 256
	};

	RelationSet_ relationSet_;
};

}
}
}
}


