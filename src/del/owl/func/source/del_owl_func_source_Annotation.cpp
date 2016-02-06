/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_source_Annotation.cpp                       */
/* Description:     functional OWL2 annotation source                        */
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
	Annotation :: Annotation (const String& string_1, const String& string_2) :
	location_ (),
	string_1_ (string_1),
	string_2_ (string_2) {
	}
	inline
	Annotation :: Annotation
	(
		const Location& location,
		const String& string_1,
		const String& string_2
	) :
	location_ (location),
	string_1_ (string_1),
	string_2_ (string_2) {
	}
	Annotation :: ~ Annotation() {
	}

	const String&
	Annotation :: getFirstString() const {
		return string_1_;
	}
	const String&
	Annotation :: getSecondString() const {
		return string_2_;
	}

using manipulator :: space;
using manipulator :: endLine;
using manipulator :: tab;

	// del :: Writable implementation
	void
	Annotation :: translate (String& string) const
	{
		/*if (!Config :: commentStuff()) {
			return;
		}
		string << location_.getIndent() << Token :: commentBegin_;
		string << name_ << space << contents_ << Token :: commentEnd_;*/
	}
	void
	Annotation :: replicate (String& string) const
	{
		string << location_.getIndent() << Token :: annotation_;
		string << Token :: openBracket_;
		string << string_1_ << space;
		string << string_2_;
		string << Token :: closeBracket_;
	}

	// object :: Object implementation
	void
	Annotation :: commitSuicide() {
		delete this;
	}
	Size_t
	Annotation :: getVolume() const
	{
		Size_t volume = 0;
		volume += string_1_.getVolume();
		volume += string_2_.getVolume();
		return volume;
	}
	Size_t
	Annotation :: getSizeOf() const {
		return sizeof (Annotation);
	}
}
}
}
}


