/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_source_Unrecognized.cpp                     */
/* Description:     functional OWL2 unrecognized object                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/owl/func/lexer/del_owl_func_lexer.hpp"
#include "del/owl/func/source/del_owl_func_source.hpp"

namespace del {
namespace owl {
namespace func {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Unrecognized :: Unrecognized
	(
		const String& name,
		const vector :: String& stringVector
	) :
	location_ (),
	name_ (name),
	stringVector_ (stringVector) {
	}
	inline
	Unrecognized :: Unrecognized
	(
		const Location& location,
		const String& name,
		const vector :: String& stringVector
	) :
	location_ (location),
	name_ (name),
	stringVector_ (stringVector.getSize())
	{
		for (value :: Integer i = 0; i < stringVector.getSize(); ++ i) {
			const String* string_1 = stringVector.getValue (i);
			String* string_2 = stringVector_.push();
			string_2->copy (*string_1);
		}
	}
	Unrecognized :: ~ Unrecognized() {
	}

	value :: Integer
	Unrecognized :: getSize() const {
		return stringVector_.getSize();
	}
	const String*
	Unrecognized :: getString (const value :: Integer i) const {
		return stringVector_.getValue (i);
	}

using manipulator :: space;
using manipulator :: endLine;
using manipulator :: tab;

	// del :: Writable implementation
	void
	Unrecognized :: translate (String& string) const
	{
		/*if (!Config :: commentStuff()) {
			return;
		}
		string << location_.getIndent() << Token :: commentBegin_;
		string << name_ << space << contents_ << Token :: commentEnd_;*/
	}
	void
	Unrecognized :: replicate (String& string) const
	{
		string << location_.getIndent() << name_;
		//string << Token :: unrecognized_;
		string << Token :: openBracket_;
		const value :: Integer size = stringVector_.getSize();
		for (value :: Integer i = 0; i < size; ++ i) {
			string << *stringVector_.getValue (i);
			if (i + 1 < size) {
				string << space;
			}
		}
		string << Token :: closeBracket_;
	}

	// object :: Object implementation
	void
	Unrecognized :: commitSuicide() {
		delete this;
	}
	Size_t
	Unrecognized :: getVolume() const
	{
		Size_t volume = 0;
		volume += name_.getVolume();
		volume += stringVector_.getVolume();
		return volume;
	}
	Size_t
	Unrecognized :: getSizeOf() const {
		return sizeof (Unrecognized);
	}
}
}
}
}


