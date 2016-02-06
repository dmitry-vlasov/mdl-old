/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_source_TransitiveObjectProperty.cpp         */
/* Description:     functional OWL2 transitive object property               */
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
	TransitiveObjectProperty :: TransitiveObjectProperty (const String& string) :
	location_ (),
	string_ (string) {
	}
	inline
	TransitiveObjectProperty :: TransitiveObjectProperty
	(
		const Location& location,
		const String& string
	) :
	location_ (location),
	string_ (string) {
	}
	TransitiveObjectProperty :: ~ TransitiveObjectProperty() {
	}

	const String&
	TransitiveObjectProperty :: getString() const {
		return string_;
	}

using manipulator :: space;
using manipulator :: endLine;
using manipulator :: tab;

	// del :: Writable implementation
	void
	TransitiveObjectProperty :: translate (String& string) const
	{
		/*if (!Config :: commentStuff()) {
			return;
		}
		string << location_.getIndent() << Token :: commentBegin_;
		string << name_ << space << contents_ << Token :: commentEnd_;*/
	}
	void
	TransitiveObjectProperty :: replicate (String& string) const
	{
		string << location_.getIndent() << Token :: transitiveObjectProperty_;
		string << Token :: openBracket_;
		string << string_;
		string << Token :: closeBracket_;
	}

	// object :: Object implementation
	void
	TransitiveObjectProperty :: commitSuicide() {
		delete this;
	}
	Size_t
	TransitiveObjectProperty :: getVolume() const
	{
		Size_t volume = 0;
		volume += string_.getVolume();
		return volume;
	}
	Size_t
	TransitiveObjectProperty :: getSizeOf() const {
		return sizeof (TransitiveObjectProperty);
	}
}
}
}
}


