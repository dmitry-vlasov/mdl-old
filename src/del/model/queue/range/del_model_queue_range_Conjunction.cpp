/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_queue_range_Conjunction.cpp                   */
/* Description:     conjunction range element                                */
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
	Conjunction<A> :: Conjunction
	(
		const del :: Formula* formula,
		const value :: Variable concepts[],
		const value :: Integer size,
		const value :: Variable concept
	) :
	formula_ (formula),
	concepts_ (size),
	concept_ (concept)
	{
		for (value :: Integer i = 0; i < size; ++ i) {
			concepts_.add (concepts [i]);
		}
	}
	template<class A>
	inline
	Conjunction<A> :: Conjunction (const Conjunction& simple) :
	formula_ (simple.formula_) {
	}
	template<class A>
	Conjunction<A> :: ~ Conjunction() {
	}

	// del :: Model implementation
	template<class A>
	typename Conjunction<A> :: Type
	Conjunction<A> :: getType() const {
		return CONJ;
	}
	template<class A>
	value :: Integer
	Conjunction<A> :: getSize() const {
		return concepts_.getSize();
	}
	template<class A>
	value :: Variable
	Conjunction<A> :: getConcept (const value :: Integer i) const {
		return concepts_.getValue (i);
	}
	template<class A>
	value :: Relation
	Conjunction<A> :: getRelation() const {
		return value :: undefined :: RELATION;
	}

	// queue :: Element implementation
	template<class A>
	const del :: Formula*
	Conjunction<A> :: getFormula() const {
		return formula_;
	}

using manipulator :: space;
using manipulator :: iterate;
using manipulator :: tab;

	// Object implementation
	template<class A>
	void
	Conjunction<A> :: commitSuicide() {
		delete this;
	}
	template<>
	void
	Conjunction<allocator :: Stack> :: commitSuicide() {
	}
	template<class A>
	Size_t
	Conjunction<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += concepts_.getVolume();
		return volume;
	}
	template<class A>
	Size_t
	Conjunction<A> :: getSizeOf() const {
		return sizeof (Conjunction);
	}
	template<class A>
	void
	Conjunction<A> :: show (String& string) const
	{
		for (value :: Integer i = 0; i < concepts_.getSize(); ++ i) {
			const value :: Variable concept = concepts_.getValue (i);
			string << Table :: variables()->get (concept);
			if (i + 1 < concepts_.getSize()) {
				string << ", ";
			}
		}
		string << " -> " << Table :: variables()->get (concept_);
	}
}
}
}
}


