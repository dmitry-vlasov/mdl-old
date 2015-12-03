/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_Identificator.cpp                             */
/* Description:     identificator parser                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_IDENTIFICATOR_CPP_
#define MDL_PARSER_IDENTIFICATOR_CPP_

#include "mdl/lexer/mdl_lexer.hpp"
#include "mdl/form/mdl_form.hpp"
#include "mdl/parser/mdl_parser.hpp"

namespace mdl {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Identificator :: Identificator() :
	location_(),
	identificator_ (NULL) {
	}
	Identificator :: ~ Identificator() {
	}

	mdl :: Identificator*
	Identificator :: parse (Lexer* lexer, const bool create)
	{
		mdl :: Identificator* id = NULL;
		identificator_ = NULL;

		while (true) {
			location_ = lexer->getLocation();
			const value :: Name
				name = lexer->scanName();
			if (create) {
				if (id == NULL) {
					identificator_ = new form :: Identificator (name, location_);
					id = identificator_;
				} else {
					id->setNext (new form :: Identificator (name, location_));
					id = id->getNext();
				}
			}
			lexer->scan
			<
				Token :: DOT,
				Token :: COMMA,
				Token :: SEMICOLON,
				Token :: EQUALITY,
				Token :: COLON,
				Token :: OPEN_BRACKET,
				Token :: OPEN_BRACE,
				Token :: CLOSE_BRACKET
			>();
			if (lexer->getTokenType() == Token :: DOT) {
				continue;
			} else {
				break;
			}
		}
		return identificator_;
	}

	// object :: Object implementation
	void
	Identificator :: commitSuicide() {
		delete this;
	}
	Size_t
	Identificator :: getVolume() const {
		return 0;
	}
	Size_t
	Identificator :: getSizeOf() const {
		return sizeof (Identificator);
	}
	void
	Identificator :: show (String&) const {
	}
}
}

#endif /*MDL_PARSER_IDENTIFICATOR_CPP_*/
