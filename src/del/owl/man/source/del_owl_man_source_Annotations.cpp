/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_source_Annotations.cpp                       */
/* Description:     manchester OWL annotations source                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_MAN_SOURCE_ANNOTATIONS_CPP_
#define DEL_OWL_MAN_SOURCE_ANNOTATIONS_CPP_

#include "del/lexer/del_lexer.hpp"
#include "del/source/del_source.hpp"

namespace del {
namespace owl {
namespace man {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Annotations :: Annotations (const Location& location) :
	location_ (location),
	annotationVector_ (INITIAL_ANNOTATION_VECTOR_CAPACITY) {
	}
	Annotations :: ~ Annotations() {
	}

	void
	Annotations :: addAnnotation (const Annotation* annotation) {
		annotationVector_.add (annotation);
	}

using manipulator :: space;
using manipulator :: endLine;
using manipulator :: tab;

	// del :: Writable implementation
	void
	Annotations :: translate (String& string) const
	{
		if (!Config :: commentStuff()) {
			return;
		}
		if (annotationVector_.getSize() == 0) {
			return;
		}
		string << location_.getIndent() << del :: Token :: commentBegin_;
		string << Token :: annotations_ << del :: Token :: commentEnd_ << endLine;
		const value :: Integer size = annotationVector_.getSize();
		for (value :: Integer i = 0; i < size; ++ i) {
			const Annotation* const
				annotation = annotationVector_.getValue (i);
			annotation->translate (string);
			string << endLine;
		}
		string << endLine;
	}
	void
	Annotations :: replicate (String& string) const
	{
		if (annotationVector_.getSize() == 0) {
			return;
		}
		string << location_.getIndent() << Token :: annotations_ << endLine;
		const value :: Integer size = annotationVector_.getSize();
		for (value :: Integer i = 0; i < size; ++ i) {
			const Annotation* const
				annotation = annotationVector_.getValue (i);
			string << *annotation;
			if (i < (size - 1)) {
				string << Token :: comma_ << endLine;
			} else {
				string << endLine << endLine;
			}
		}
	}

	// object :: Object implementation
	void
	Annotations :: commitSuicide() {
		delete this;
	}
	Size_t
	Annotations :: getVolume() const {
		return annotationVector_.getVolume();
	}
	Size_t
	Annotations :: getSizeOf() const {
		return sizeof (Annotations);
	}
}
}
}
}

#endif /*DEL_OWL_MAN_SOURCE_ANNOTATIONS_CPP_*/
