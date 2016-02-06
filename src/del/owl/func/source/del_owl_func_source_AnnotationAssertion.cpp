/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_source_AnnotationAssertion.cpp              */
/* Description:     functional OWL2 annotation assertion source              */
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
	AnnotationAssertion :: AnnotationAssertion
	(
		const Location& location,
		const String& property,
		const String& subject,
		const String& value
	) :
	location_ (location),
	property_ (property),
	subject_ (subject),
	value_ (value),
	symbol_ () {
	}
	inline
	AnnotationAssertion :: AnnotationAssertion (const AnnotationAssertion& annotationAssertion) :
	location_ (),
	property_ (annotationAssertion.property_),
	subject_ (annotationAssertion.subject_),
	value_ (annotationAssertion.value_),
	symbol_ (annotationAssertion.symbol_) {
	}
	AnnotationAssertion :: ~ AnnotationAssertion() {
	}

	inline const String&
	AnnotationAssertion :: getProperty() const {
		return property_;
	}
	inline const String&
	AnnotationAssertion :: getSubject() const {
		return subject_;
	}
	inline const String&
	AnnotationAssertion :: getValue() const {
		return value_;
	}

	bool
	AnnotationAssertion :: relatesTo (const del :: Symbol& symbol) const
	{
		if (symbol_.isUndefined()) {
			if (Table :: variables()->contains (subject_)) {
				const value :: Variable v = Table :: variables()->add (subject_);
				symbol_ = Symbol (v, false);
			}
			if (Table :: relations()->contains (subject_)) {
				const value :: Relation r = Table :: relations()->add (subject_);
				symbol_ = Symbol (r, true);
			}
		}
		return (symbol_ == symbol);
	}
	inline const AnnotationAssertion*
	AnnotationAssertion :: clone() const {
		return new AnnotationAssertion (*this);
	}

using manipulator :: space;
using manipulator :: endLine;
using manipulator :: tab;

	// del :: Writable implementation
	void
	AnnotationAssertion :: translate (String& string) const {
	}
	void
	AnnotationAssertion :: replicate (String& string) const
	{
		string << location_.getIndent() << Token :: annotationAssertion_;
		string << Token :: openBracket_;
		string << property_ << space;
		string << subject_ << space;
		string << value_;
		string << Token :: closeBracket_;
	}

	// object :: Object implementation
	void
	AnnotationAssertion :: commitSuicide() {
		delete this;
	}
	Size_t
	AnnotationAssertion :: getVolume() const
	{
		Size_t volume = 0;
		volume += property_.getVolume();
		volume += subject_.getVolume();
		volume += value_.getVolume();
		return volume;
	}
	Size_t
	AnnotationAssertion :: getSizeOf() const {
		return sizeof (AnnotationAssertion);
	}
}
}
}
}


