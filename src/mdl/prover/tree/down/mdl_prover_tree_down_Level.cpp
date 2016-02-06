/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_tree_down_Level.cpp                           */
/* Description:     level in proof variant tree                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace prover {
namespace tree {
namespace down {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Level<A> :: Level (const value :: Integer initialCapacity) :
	level_ (initialCapacity) {
	}
	template<class A>
	Level<A> :: ~ Level() {
	}

	// prover :: Level implementation
	template<class A>
	inline value :: Integer
	Level<A> :: getSize () const {
		return level_.getSize();
	}
	template<class A>
	inline typename Level<A> :: Evidence_*
	Level<A> :: getValue (const value :: Integer i) const {
		return level_.getValue (i);
	}

	template<class A>
	inline bool
	Level<A> :: isEmpty() const {
		return level_.isEmpty();
	}
	template<class A>
	inline void
	Level<A> :: add (Evidence_* node) {
		level_.add (node);
	}
	template<class A>
	inline void
	Level<A> :: remove (Evidence_* node) {
		level_.removeValue (node);
	}
	template<class A>
	bool
	Level<A> :: contains (Evidence_* node) const {
		return level_.contains (node);
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;

	// object :: Object implementation
	template<class A>
	void
	Level<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Level<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += level_.getVolume();
		return volume;
	}
	template<class A>
	Size_t
	Level<A> :: getSizeOf() const {
		return sizeof (Level);
	}
	template<class A>
	void
	Level<A> :: show (String& string) const
	{
		const value :: Integer size = level_.getSize();
		for (value :: Integer j = 0; j < size; ++ j) {
			const value :: Integer k = size - j - 1;
			const Evidence_* node = level_.getValue (k);
			/*if (showPropNode (node, string)) {
				continue;
			}
			if (showHypNode (node, string)) {
				continue;
			}*/
			//string << tab << *node->getExpression() << endLine;
		}
		string <<  endLine;
	}

	/****************************
	 *		Private members
	 ****************************/
}
}
}
}


