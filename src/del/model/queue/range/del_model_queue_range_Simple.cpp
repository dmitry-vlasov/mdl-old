/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_queue_range_Simple.cpp                        */
/* Description:     simple range element                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/auxiliary/del_auxiliary.hpp"
#include "del/source/del_source.hpp"
#include "del/model/del_model.hpp"

namespace del {
namespace model {
namespace queue {
namespace range {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Simple<A> :: Simple
	(
		const del :: Formula* formula,
		const value :: Variable concept
	) :
	formula_ (formula),
	concept_ (concept) {
	}
	template<class A>
	inline
	Simple<A> :: Simple (const Simple& simple) :
	formula_ (simple.formula_),
	concept_ (simple.concept_) {
	}
	template<class A>
	Simple<A> :: ~ Simple() {
	}

	// del :: Model implementation
	template<class A>
	typename Simple<A> :: Type
	Simple<A> :: getType() const {
		return SIMPLE;
	}
	template<class A>
	value :: Integer
	Simple<A> :: getSize() const {
		return 1;
	}
	template<class A>
	value :: Variable
	Simple<A> :: getConcept (const value :: Integer) const {
		return concept_;
	}
	template<class A>
	value :: Relation
	Simple<A> :: getRelation() const {
		return value :: undefined :: RELATION;
	}

	// queue :: Element implementation
	template<class A>
	const del :: Formula*
	Simple<A> :: getFormula() const {
		return formula_;
	}

using manipulator :: space;
using manipulator :: iterate;
using manipulator :: tab;

	// Object implementation
	template<class A>
	void
	Simple<A> :: commitSuicide() {
		delete this;
	}
	template<>
	void
	Simple<allocator :: Stack> :: commitSuicide() {
	}
	template<class A>
	Size_t
	Simple<A> :: getVolume() const
	{
		Size_t volume = 0;
		return volume;
	}
	template<class A>
	Size_t
	Simple<A> :: getSizeOf() const {
		return sizeof (Simple);
	}
	template<class A>
	void
	Simple<A> :: show (String& string) const {
		string << Table :: variables()->get (concept_);
	}
}
}
}
}


