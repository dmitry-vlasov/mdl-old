/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_parser_ObjectProperty.cpp                    */
/* Description:     manchester OWL object property parser                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

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
	ObjectProperty :: ObjectProperty() :
	location_ (),
	name_ (INITIAL_NAME_CAPACITY),
	characteristics_ (INITIAL_CHARACTERISTICS_CAPACITY),
	annotations_ (NULL),
	annotationsParser_ (new parser :: Annotations()) {
	}
	ObjectProperty :: ~ ObjectProperty() {
		deleteAggregateObject (annotationsParser_);
	}

	const source :: ObjectProperty*
	ObjectProperty :: parse (Lexer* lexer)
	{
		name_.clear();
		characteristics_.clear();
		annotations_ = NULL;

		location_ = lexer->getLocation();
		lexer->scan<Token :: NAME>();
		name_.copy (lexer->getToken());

		bool insideProperties = true;
		bool lastWasCharacteristics = false;
		while (insideProperties) {
			switch (lexer->scan()) {
			case Token :: CHARACTERISTICS : {
				lexer->scan<Token :: NAME>();
				characteristics_.copy (lexer->getToken());
				lastWasCharacteristics = true;
				break;
			}
			case Token :: ANNOTATIONS : {
				annotations_ = annotationsParser_->parse (lexer);
				break;
			}
			default :
				if (!lastWasCharacteristics) {
					lexer->setIdleScan();
				}
				lastWasCharacteristics = false;
				insideProperties = false;
			}
		}
		return new source :: ObjectProperty
		(
			location_,
			name_,
			characteristics_,
			annotations_
		);
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
		volume += getAggregateVolume (annotationsParser_);
		volume += name_.getVolume();
		volume += characteristics_.getVolume();
		return volume;
	}
	Size_t
	ObjectProperty :: getSizeOf() const {
		return sizeof (ObjectProperty);
	}
	void
	ObjectProperty :: show (String&) const {
	}
}
}
}
}


