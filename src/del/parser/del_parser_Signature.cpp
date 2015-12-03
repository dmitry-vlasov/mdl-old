/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_parser_Signature.cpp                                 */
/* Description:     theory contents parser                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_PARSER_SIGNATURE_CPP_
#define DEL_PARSER_SIGNATURE_CPP_

#include "del/lexer/del_lexer.hpp"
#include "del/source/del_source.hpp"
#include "del/parser/del_parser.hpp"

namespace del {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	Signature :: Signature() :
	location_ (),
	comments_ (NULL),
	name_ (value :: undefined :: SIGNATURE),
	signature_ (NULL) {
	}
	Signature :: ~ Signature() {
	}

	const del :: Signature*
	Signature :: parse (Lexer* lexer)
	{
		location_ = lexer->getLocation();
		name_ = lexer->scanSignatureName (true);
		lexer->scan<Token :: EQUALITY>();
		lexer->scan<Token :: OPEN_BRACE>();

		comments_ =
			lexer->comments().isEmpty() ?
			NULL :
			new source :: Comments (lexer->comments());
		lexer->comments().clear();
		signature_ = new source :: Signature<> (location_, comments_, name_);

		bool inSignature = true;
		while (inSignature) {
			lexer->scan
			<
				Token :: CONCEPT,
				Token :: RELATION,
				Token :: CONCEPTS,
				Token :: RELATIONS,
				Token :: CLOSE_BRACE
			>();
			switch (lexer->getTokenType()) {
			case Token :: CONCEPT : {
				const value :: Variable concept = lexer->scanVariableName();
				signature_->addSymbol (Symbol (concept, false));
				if (lexer->scan<Token :: COMMA, Token :: CLOSE_BRACE>() == Token :: CLOSE_BRACE) {
					inSignature = false;
				}
				break;
			}
			case Token :: RELATION : {
				const value :: Relation relation = lexer->scanRelationName();
				signature_->addSymbol (Symbol (relation, true));
				if (lexer->scan<Token :: COMMA, Token :: CLOSE_BRACE>() == Token :: CLOSE_BRACE) {
					inSignature = false;
				}
				break;
			}
			case Token :: CONCEPTS :
				lexer->scan<Token :: OPEN_BRACE>();
				while (true) {
					lexer->scan
					<
						Token :: COMMA,
						Token :: CLOSE_BRACE,
						Token :: NAME
					> ();
					if (lexer->getTokenType() == Token :: CLOSE_BRACE) {
						break;
					}
					if (lexer->getTokenType() == Token :: NAME) {
						const value :: Variable
							concept = Table :: variables()->add (lexer->getToken());
						signature_->addSymbol (Symbol (concept, false));
					}
				}
				break;
			case Token :: RELATIONS :
				lexer->scan<Token :: OPEN_BRACE>();
				while (true) {
					lexer->scan
					<
						Token :: COMMA,
						Token :: CLOSE_BRACE,
						Token :: NAME
					> ();
					if (lexer->getTokenType() == Token :: CLOSE_BRACE) {
						break;
					}
					if (lexer->getTokenType() == Token :: NAME) {
						const value :: Relation
							relation = Table :: relations()->add (lexer->getToken());
						signature_->addSymbol (Symbol (relation, true));
					}
				}
				break;
			case Token :: CLOSE_BRACE :
				inSignature = false;
				break;
			default :
				inSignature = false;
				break;
			}
		}
		lexer->comments().clear();
		return signature_;
	}

	// object :: Object implementation
	void
	Signature :: commitSuicide() {
		delete this;
	}
	Size_t
	Signature :: getVolume() const {
		return 0;
	}
	Size_t
	Signature :: getSizeOf() const {
		return sizeof (Signature);
	}
	void
	Signature :: show (String&) const {
	}
}
}

#endif /*DEL_PARSER_SIGNATURE_CPP_*/
