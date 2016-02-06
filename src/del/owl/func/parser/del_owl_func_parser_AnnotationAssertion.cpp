/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_parser_AnnotationAssertionAssertion.cpp              */
/* Description:     functional OWL2 annotation assertion parser              */
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
#include "del/owl/func/parser/del_owl_func_parser.hpp"

namespace del {
namespace owl {
namespace func {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	inline
	AnnotationAssertion :: AnnotationAssertion() :
	location_ (),
	annotationAssertion_ (NULL),
	property_ (INITIAL_STRING_CAPACITY),
	subject_ (INITIAL_STRING_CAPACITY),
	value_ (INITIAL_STRING_CAPACITY) {
	}
	AnnotationAssertion :: ~ AnnotationAssertion() {
	}

	const source :: AnnotationAssertion*
	AnnotationAssertion :: parse (Lexer* lexer)
	{
		location_ = lexer->getLocation();
		lexer->scan<Token :: OPEN_BRACKET>();
		lexer->scan<Token :: STRING>();
		property_.copy (lexer->getToken());
		lexer->scan<Token :: STRING>();
		subject_.copy (lexer->getToken());
		lexer->scan<Token :: STRING>();
		value_.copy (lexer->getToken());
		lexer->scan<Token :: CLOSE_BRACKET>();
		annotationAssertion_ = new source :: AnnotationAssertion
		(
			location_,
			property_,
			subject_,
			value_
		);
		return annotationAssertion_;
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
	void
	AnnotationAssertion :: show (String&) const {
	}
}
}
}
}


