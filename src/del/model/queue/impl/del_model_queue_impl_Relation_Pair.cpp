/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_queue_impl_Relation_Pair.cpp                   */
/* Description:     pair of concepts as elements of relations                */
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

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Relation<A> :: Pair :: Pair () :
	x_ (value :: undefined :: VARIABLE),
	y_ (value :: undefined :: VARIABLE) {
	}
	template<class A>
	inline
	Relation<A> :: Pair :: Pair
	(
		const value :: Variable x,
		const value :: Variable y
	) :
	x_ (x), y_ (y) {
	}
	template<class A>
	inline
	Relation<A> :: Pair :: Pair (const Pair& pair) :
	x_ (pair.x_), y_ (pair.y_) {
	}
	template<class A>
	Relation<A> :: Pair :: ~ Pair () {
	}

	template<class A>
	inline bool
	Relation<A> :: Pair :: operator < (const Pair& pair) const {
		return (x_ < pair.x_) || ((x_ == pair.x_) && (y_ < pair.y_));
	}
	template<class A>
	inline bool
	Relation<A> :: Pair :: operator > (const Pair& pair) const {
		return pair.operator < (*this);
	}
	template<class A>
	inline bool
	Relation<A> :: Pair :: operator == (const Pair& pair) const {
		return (x_ == pair.x_) && (y_ == pair.y_);
	}
	template<class A>
	inline void
	Relation<A> :: Pair :: operator = (const Pair& pair)
	{
		x_ = pair.x_;
		y_ = pair.y_;
	}

	// del :: Object implementation
	template<class A>
	void
	Relation<A> :: Pair :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Relation<A> :: Pair :: getVolume() const {
		return 0;
	}
	template<class A>
	Size_t
	Relation<A> :: Pair :: getSizeOf() const {
		return sizeof (Pair);
	}
	template<class A>
	void
	Relation<A> :: Pair :: show (String& string) const
	{
		string << "(" << Table :: variables()->get (x_) << ", ";
		string << Table :: variables()->get (y_) << ")";
	}

	/****************************
	 *		Private members
	 ****************************/
}
}
}
}


