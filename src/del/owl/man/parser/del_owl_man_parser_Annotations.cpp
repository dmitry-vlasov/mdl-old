/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_parser_Annotations.cpp                       */
/* Description:     manchester OWL annotations parser                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_MAN_PARSER_ANNOTATIONS_CPP_
#define DEL_OWL_MAN_PARSER_ANNOTATIONS_CPP_

#include "del/owl/man/lexer/del_owl_man_lexer.hpp"
#include "del/owl/man/source/del_owl_man_source.hpp"
#include "del/owl/man/parser/del_owl_man_parser.hpp"

namespace del {
namespace owl {
namespace man {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Annotations :: Annotations() :
	location_ (),
	annotations_ (NULL),
	annotation_ (NULL),
	name_ (INITIAL_NAME_CAPACITY),
	contents_ (INITIAL_CONTENTS_CAPACITY) {
	}
	Annotations :: ~ Annotations() {
	}

	const source :: Annotations*
	Annotations :: parse (Lexer* lexer)
	{
		location_ = lexer->getLocation();
		annotations_ = new source :: Annotations (location_);

		while (true) {
			location_ = lexer->getLocation();
			lexer->scan<Token :: NAME>();
			name_.copy (lexer->getToken());
			lexer->scanLine();
			contents_.copy (lexer->getToken());
			if (contents_.getLastValue() != ',') {
				break;
			}
			annotation_ = new source :: Annotation (location_, name_, contents_);
			annotations_->addAnnotation (annotation_);
		}
		return annotations_;
	}

	// object :: Object implementation
	void
	Annotations :: commitSuicide() {
		delete this;
	}
	Size_t
	Annotations :: getVolume() const
	{
		Size_t volume = 0;
		volume += name_.getVolume();
		volume += contents_.getVolume();
		return volume;
	}
	Size_t
	Annotations :: getSizeOf() const {
		return sizeof (Annotations);
	}
	void
	Annotations :: show (String&) const {
	}
}
}
}
}

#endif /*DEL_OWL_MAN_PARSER_ANNOTATIONS_CPP_*/
