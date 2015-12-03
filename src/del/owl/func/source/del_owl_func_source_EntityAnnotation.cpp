/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_source_EntityAnnotation.cpp                 */
/* Description:     functional OWL2 entity annotation source                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_FUNC_SOURCE_ENTITY_ANNOTATION_CPP_
#define DEL_OWL_FUNC_SOURCE_ENTITY_ANNOTATION_CPP_

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
	EntityAnnotation :: EntityAnnotation
	(
		const Location& location,
		const Kind kind,
		const String& name,
		const Annotation* annotation
	) :
	location_ (location),
	kind_ (kind),
	name_ (name),
	label_ (),
	annotation_ (annotation) {
	}
	inline
	EntityAnnotation :: EntityAnnotation
	(
		const Location& location,
		const Kind kind,
		const String& name,
		const String& label
	) :
	location_ (location),
	kind_ (kind),
	name_ (label),
	label_ (),
	annotation_ (NULL) {
	}
	EntityAnnotation :: ~ EntityAnnotation() {
		deleteAggregateObject (annotation_);
	}

	EntityAnnotation :: Kind
	EntityAnnotation :: getKind() const {
		return kind_;
	}
	const String&
	EntityAnnotation :: getName() const {
		return name_;
	}
	const Annotation*
	EntityAnnotation :: getAnnotation() const {
		return annotation_;
	}
	void
	EntityAnnotation :: setAnnotation (const Annotation* annotation) {
		annotation_ = annotation;
	}

using manipulator :: space;
using manipulator :: endLine;
using manipulator :: tab;

	// del :: Writable implementation
	void
	EntityAnnotation :: translate (String& string) const
	{
		/*if (!Config :: commentStuff()) {
			return;
		}
		string << location_.getIndent() << Token :: commentBegin_;
		string << name_ << space << contents_ << Token :: commentEnd_;*/
	}
	void
	EntityAnnotation :: replicate (String& string) const
	{
		string << location_.getIndent() << Token :: entityAnnotation_;
		string << Token :: openBracket_;
		switch (kind_) {
		case CLASS :
			string << Token :: class_; break;
		case OBJECT_PROPERTY :
			string << Token :: objectProperty_; break;
		default :
			string << "<...>"; break;
		}
		string << Token :: openBracket_;
		string << name_;
		string << Token :: closeBracket_ << space;
		if (annotation_ != NULL) {
			annotation_->replicate (string);
		} else {
			string << Token :: label_;
			string << Token :: openBracket_;
			string << label_;
			string << Token :: closeBracket_ << space;
		}
		string << Token :: closeBracket_;
	}

	// object :: Object implementation
	void
	EntityAnnotation :: commitSuicide() {
		delete this;
	}
	Size_t
	EntityAnnotation :: getVolume() const
	{
		Size_t volume = 0;
		volume += name_.getVolume();
		volume += getAggregateVolume (annotation_);
		return volume;
	}
	Size_t
	EntityAnnotation :: getSizeOf() const {
		return sizeof (EntityAnnotation);
	}
}
}
}
}

#endif /*DEL_OWL_FUNC_SOURCE_ENTITY_ANNOTATION_CPP_*/
