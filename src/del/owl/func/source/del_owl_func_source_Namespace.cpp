/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_source_Namespace.cpp                        */
/* Description:     functional OWL2 namespace source                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_FUNC_SOURCE_NAMESPACE_CPP_
#define DEL_OWL_FUNC_SOURCE_NAMESPACE_CPP_

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
	Namespace :: Namespace (const String& string) :
	location_ (),
	string_ (string) {
	}
	inline
	Namespace :: Namespace
	(
		const Location& location,
		const String& string
	) :
	location_ (location),
	string_ (string) {
	}
	Namespace :: ~ Namespace() {
	}

	const String&
	Namespace :: getString() const {
		return string_;
	}

using manipulator :: space;
using manipulator :: endLine;
using manipulator :: tab;

	// del :: Writable implementation
	void
	Namespace :: translate (String& string) const
	{
		/*if (!Config :: commentStuff()) {
			return;
		}
		string << location_.getIndent() << Token :: commentBegin_;
		string << name_ << space << contents_ << Token :: commentEnd_;*/
	}
	void
	Namespace :: replicate (String& string) const
	{
		string << location_.getIndent() << Token :: namespace_;
		string << Token :: openBracket_;
		string << string_;
		string << Token :: closeBracket_;
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
		volume += string_.getVolume();
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

#endif /*DEL_OWL_FUNC_SOURCE_NAMESPACE_CPP_*/
