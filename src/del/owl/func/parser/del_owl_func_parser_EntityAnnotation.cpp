/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_parser_EntityAnnotation.cpp                 */
/* Description:     functional OWL2 entity annotation parser                 */
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
	EntityAnnotation :: EntityAnnotation() :
	location_ (),
	annotation_ (NULL),
	entityAnnotation_ (NULL),
	name_ (INITIAL_NAME_CAPACITY),
	label_ (INITIAL_NAME_CAPACITY),
	annotationParser_ (new parser :: Annotation()) {
	}
	EntityAnnotation :: ~ EntityAnnotation() {
		deleteAggregateObject (annotationParser_);
	}

	const source :: EntityAnnotation*
	EntityAnnotation :: parse (Lexer* lexer)
	{
		location_ = lexer->getLocation();
		lexer->scan<Token :: OPEN_BRACKET>();
		const Token :: Type
			tokenType = lexer->scan<Token :: CLASS, Token :: OBJECT_PROPERTY>();
		lexer->scan<Token :: OPEN_BRACKET>();
		lexer->scan<Token :: STRING>();
		name_.copy (lexer->getToken());
		lexer->scan<Token :: CLOSE_BRACKET>();

		if (lexer->scan<Token :: ANNOTATION, Token :: LABEL>() == Token :: ANNOTATION) {
			annotation_ = annotationParser_->parse(lexer);
			entityAnnotation_ = new source :: EntityAnnotation
			(
				location_,
				(
					(tokenType == Token :: CLASS) ?
					source :: EntityAnnotation :: CLASS :
					source :: EntityAnnotation :: OBJECT_PROPERTY
				),
				name_,
				annotation_
			);
		} else {
			lexer->scan<Token :: OPEN_BRACKET>();
			lexer->scan<Token :: STRING>();
			label_.copy (lexer->getToken());
			lexer->scan<Token :: CLOSE_BRACKET>();
			entityAnnotation_ = new source :: EntityAnnotation
			(
				location_,
				(
					(tokenType == Token :: CLASS) ?
					source :: EntityAnnotation :: CLASS :
					source :: EntityAnnotation :: OBJECT_PROPERTY
				),
				name_,
				label_
			);
		}
		lexer->scan<Token :: CLOSE_BRACKET>();
		return entityAnnotation_;
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
		volume += label_.getVolume();
		volume += getAggregateVolume (annotationParser_);
		return volume;
	}
	Size_t
	EntityAnnotation :: getSizeOf() const {
		return sizeof (EntityAnnotation);
	}
	void
	EntityAnnotation :: show (String&) const {
	}
}
}
}
}


