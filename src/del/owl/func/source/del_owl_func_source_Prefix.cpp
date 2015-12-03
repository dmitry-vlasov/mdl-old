/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_source_Prefix.cpp                           */
/* Description:     functional OWL2 prefix source                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_FUNC_SOURCE_PREFIX_CPP_
#define DEL_OWL_FUNC_SOURCE_PREFIX_CPP_

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
	Prefix :: Prefix (const String& string) :
	location_ (),
	string_ (string) {
	}
	inline
	Prefix :: Prefix
	(
		const Location& location,
		const String& string
	) :
	location_ (location),
	string_ (string) {
	}
	Prefix :: ~ Prefix() {
	}

	const String&
	Prefix :: getString() const {
		return string_;
	}
	const Prefix*
	Prefix :: clone() const {
		return new Prefix (string_);
	}

using manipulator :: space;
using manipulator :: endLine;
using manipulator :: tab;

	// del :: Writable implementation
	void
	Prefix :: translate (String& string) const
	{
		/*if (!Config :: commentStuff()) {
			return;
		}
		string << location_.getIndent() << Token :: commentBegin_;
		string << name_ << space << contents_ << Token :: commentEnd_;*/
	}
	void
	Prefix :: replicate (String& string) const
	{
		string << location_.getIndent() << Token :: prefix_;
		string << Token :: openBracket_;
		string << string_;
		string << Token :: closeBracket_;
	}

	// object :: Object implementation
	void
	Prefix :: commitSuicide() {
		delete this;
	}
	Size_t
	Prefix :: getVolume() const
	{
		Size_t volume = 0;
		volume += string_.getVolume();
		return volume;
	}
	Size_t
	Prefix :: getSizeOf() const {
		return sizeof (Prefix);
	}
}
}
}
}

#endif /*DEL_OWL_FUNC_SOURCE_PREFIX_CPP_*/
