/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_Expansion.cpp                                 */
/* Description:     signature class                                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_EXPANSION_CPP_
#define DEL_SOURCE_EXPANSION_CPP_

#include "del/interface/del_interface.hpp"

namespace del {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	Expansion<A> :: Expansion (const del :: Signature* const delta) :
	delta_ (delta),
	map_ (INITIAL_MAP_CAPACITY) {
	}
	template<class A>
	Expansion<A> :: Expansion (const Expansion& expansion) :
	delta_ (expansion.delta_),
	map_ (expansion.map_) {
	}
	template<class A>
	Expansion<A> :: ~ Expansion() {
	}

	// del :: Expansion implementation
	template<class A>
	void
	Expansion<A> :: clear() {
		map_.clear();
	}
	template<class A>
	del :: Symbol
	Expansion<A> :: addPostfixToSymbol (const del :: Symbol& symbol) const
	{
		/*if (delta_->containsSymbol (symbol)) {
			return symbol;
		}*/
		const del :: Symbol newSymbol
		(
			symbol.getValue(),
			symbol.isRelation(),
			true,
			symbol.isTemporary()
		);
		return newSymbol;
		//return map_.addFind (symbol, newSymbol);
	}

	// del :: Cloneable implementation
	template<class A>
	del :: Expansion*
	Expansion<A> :: clone() const {
		return new Expansion (*this);
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: iterate;
using manipulator :: tab;

	// del :: Object implementation
	template<class A>
	void
	Expansion<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Expansion<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += map_.getVolume();
		return volume;
	}
	template<class A>
	Size_t
	Expansion<A> :: getSizeOf() const {
		return sizeof (Expansion);
	}
	template<class A>
	void
	Expansion<A> :: show (String& string) const
	{
		string << "expansion = " << space;
		string << Token :: openBrace_ << endLine;
		if (map_.getSize() > 0) {
			for (value :: Integer i = 0; i < map_.getSize() - 1; ++ i) {
				string << tab << map_.getKey (i) << space;
				string << "----->" << space;
				string << map_.getValue (i) << Token :: comma_ << endLine;
			}
			string << tab << map_.getLastKey() << space;
			string << "----->" << space;
			string << map_.getLastValue() << endLine;
		}
		string << Token :: closeBrace_<< endLine;
	}
}
}

#endif /*DEL_SOURCE_EXPANSION_CPP_*/
