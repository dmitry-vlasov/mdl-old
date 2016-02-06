/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_queue_impl_PredicateMap.hpp                    */
/* Description:     predicate map in queue model                             */
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
namespace queue {
namespace impl {

template<class A>
class PredicateMap :
	public queue :: PredicateMap,
	public Scalar<PredicateMap<A>, A> {
public :
	typedef A Allocator_;

	PredicateMap();
	virtual ~ PredicateMap();

	// queue :: PredicateMap interface
	virtual value :: Integer getSize() const;
	virtual queue :: Predicate* get (const value :: Integer);
	virtual queue :: Predicate* map (const value :: Variable);

	// del :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	typedef
		Predicate<Allocator_>
		Predicate_;

	typedef
		map :: Scalar
		<
			value :: Variable,
			value :: Integer,
			Allocator_
		>
		PredicateMap_;

	typedef
		del :: vector :: Vector
		<
			Predicate_,
			storage :: ByPointer,
			Allocator_
		>
		PredicateVector_;

	enum {
		INITIAL_PREDICATE_VECTOR_CAPACITY = 1024 * 4
	};

	PredicateMap_    predicateMap_;
	PredicateVector_ predicateVector_;
};

}
}
}
}


