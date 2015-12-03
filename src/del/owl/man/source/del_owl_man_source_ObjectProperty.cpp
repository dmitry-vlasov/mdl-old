/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_source_ObjectProperty.cpp                    */
/* Description:     manchester OWL object property source                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_MAN_SOURCE_OBJECT_PROPERTY_CPP_
#define DEL_OWL_MAN_SOURCE_OBJECT_PROPERTY_CPP_

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
	ObjectProperty :: ObjectProperty
	(
		const Location& location,
		const String& name,
		const String& characteristics,
		const Annotations* annotations
	) :
	location_ (location),
	name_ (name),
	characteristics_ (characteristics),
	annotations_ (annotations) {
	}
	inline
	ObjectProperty :: ObjectProperty (const Symbol& relation) :
	location_ (),
	name_ (),
	characteristics_ (),
	annotations_ (NULL) {
		relation.replicate (const_cast<String&>(name_));
	}
	ObjectProperty :: ~ ObjectProperty() {
		deleteAggregateObject (annotations_);
	}

using manipulator :: space;
using manipulator :: endLine;
using manipulator :: tab;

	// del :: Writable implementation
	void
	ObjectProperty :: translate (String& string) const
	{
		if (!Config :: commentStuff()) {
			return;
		}
		string << location_.getIndent() << del :: Token :: commentBegin_;
		string << Token :: object_property_ << space;
		string << name_ << endLine;
		if (annotations_ != NULL) {
			string << *annotations_;
		}
		if (!characteristics_.isEmpty()) {
			string << Token :: characteristics_ << endLine;
			string << tab << characteristics_ << endLine;
		}
		string << del :: Token :: commentEnd_ << endLine;
	}
	void
	ObjectProperty :: replicate (String& string) const
	{
		string << location_.getIndent() << Token :: object_property_ << space;
		string << name_ << endLine;
		if (annotations_ != NULL) {
			string << *annotations_;
		}
		if (!characteristics_.isEmpty()) {
			string << Token :: characteristics_ << endLine;
			string << tab << characteristics_ << endLine;
		}
		string << endLine;
	}

	// object :: Object implementation
	void
	ObjectProperty :: commitSuicide() {
		delete this;
	}
	Size_t
	ObjectProperty :: getVolume() const
	{
		Size_t volume = 0;
		volume += name_.getVolume();
		volume += characteristics_.getVolume();
		volume += getAggregateVolume (annotations_);
		return volume;
	}
	Size_t
	ObjectProperty :: getSizeOf() const {
		return sizeof (ObjectProperty);
	}
}
}
}
}

#endif /*DEL_OWL_MAN_SOURCE_OBJECT_PROPERTY_CPP_*/
