/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_source_Namespace.cpp                         */
/* Description:     manchester OWL namespace source                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_MAN_SOURCE_NAMESPACE_CPP_
#define DEL_OWL_MAN_SOURCE_NAMESPACE_CPP_

#include "del/owl/man/lexer/del_owl_man_lexer.hpp"
#include "del/owl/man/source/del_owl_man_source.hpp"

namespace del {
namespace owl {
namespace man {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Namespace :: Namespace
	(
		const Location& location,
		const String& name,
		const String& contents
	) :
	location_ (location),
	name_ (name),
	contents_ (contents) {
	}
	Namespace :: ~ Namespace() {
	}

using manipulator :: space;
using manipulator :: endLine;
using manipulator :: tab;

	// del :: Writable implementation
	void
	Namespace :: translate (String& string) const
	{
		if (!Config :: commentStuff()) {
			return;
		}
		string << location_.getIndent() << del :: Token :: commentBegin_;
		string << Token :: namespace_ << space;
		string << name_ << space << Token :: leftAngle_;
		string << contents_ << Token :: rightAngle_;
		string << del :: Token :: commentEnd_ << endLine;
	}
	void
	Namespace :: replicate (String& string) const
	{
		string << location_.getIndent() << Token :: namespace_ << space;
		string << name_ << space << Token :: leftAngle_;
		string << contents_ << Token :: rightAngle_ << endLine;
	}

	// object :: Object implementation
	void
	Namespace :: commitSuicide() {
		delete this;
	}
	Size_t
	Namespace :: getVolume() const
	{
		Size_t volume = 0;
		volume += name_.getVolume();
		volume += contents_.getVolume();
		return volume;
	}
	Size_t
	Namespace :: getSizeOf() const {
		return sizeof (Namespace);
	}
}
}
}
}

#endif /*DEL_OWL_MAN_SOURCE_NAMESPACE_CPP_*/
