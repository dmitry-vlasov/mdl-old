/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_parser_Proof.cpp                                     */
/* Description:     smm proof parser                                         */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "smm/lexer/smm_lexer.hpp"
#include "smm/source/smm_source.hpp"
#include "smm/parser/smm_parser.hpp"

namespace smm {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Proof :: Proof() :
	location_ () {
	}
	Proof :: ~ Proof() {
	}

using manipulator :: endLine;

	const smm :: Proof*
	Proof :: parse (Lexer* const lexer)
	{
		location_ = lexer->getLocation();
		vector :: Reference*
			referenceVector = new vector :: Reference();

		while (true) {
			switch (lexer->scan()) {
			case Token :: PREFIX_F :
			case Token :: PREFIX_E :
			case Token :: PREFIX_I : {
				source :: Reference& reference = referenceVector->push();
				reference.setKind (lexer->getTokenType());
				reference.setIndex (lexer->scanIndex());
				break;
			}
			case Token :: PREFIX_A :
			case Token :: PREFIX_P : {
				source :: Reference& reference = referenceVector->push();
				reference.setKind (lexer->getTokenType());
				reference.setIndex (Config :: noLabels() ? lexer->scanIndex() : lexer->scanLabel());
				break;
			}
			case Token :: END :
				goto end;
			default :
				Error* error = new Error (lexer->getLocation(), Error :: PARSER);
				error->message() << "unexpected token: " << lexer->getToken() << endLine;
				error->message() << "should be one of : $. or <prefix>" << endLine;
				throw error;
			}
		}
		end :
		return new source :: Proof (location_, referenceVector);
	}

	// object :: Object implementation
	void
	Proof :: commitSuicide() {
		delete this;
	}
	Size_t
	Proof :: getVolume() const {
		return location_.getVolume();
	}
	Size_t
	Proof :: getSizeOf() const {
		return sizeof (Proof);
	}
	void
	Proof :: show (String&) const {
	}
}
}


