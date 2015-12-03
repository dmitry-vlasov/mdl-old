/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_source_Annotation.cpp                        */
/* Description:     manchester OWL annotation source                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_MAN_ANNOTATION_PROPERTY_CPP_
#define DEL_OWL_MAN_ANNOTATION_PROPERTY_CPP_

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
	Annotation :: Annotation
	(
		const Location& location,
		const String& name,
		const String& contents
	) :
	location_ (location),
	name_ (name),
	contents_ (contents) {
	}
	Annotation :: ~ Annotation() {
	}

using manipulator :: space;
using manipulator :: endLine;
using manipulator :: tab;

	// del :: Writable implementation
	void
	Annotation :: translate (String& string) const
	{
		if (!Config :: commentStuff()) {
			return;
		}
		string << location_.getIndent() << Token :: commentBegin_;
		string << name_ << space << contents_ << Token :: commentEnd_;
	}
	void
	Annotation :: replicate (String& string) const {
		string << location_.getIndent() << name_ << space << contents_;
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
		volume += name_.getVolume();
		volume += contents_.getVolume();
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

#endif /*DEL_OWL_MAN_ANNOTATION_PROPERTY_CPP_*/
