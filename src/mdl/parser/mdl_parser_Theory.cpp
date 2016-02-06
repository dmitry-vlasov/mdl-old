/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_Theory.cpp                                    */
/* Description:     theory parser                                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/lexer/mdl_lexer.hpp"
#include "mdl/form/mdl_form.hpp"
#include "mdl/parser/mdl_parser.hpp"

namespace mdl {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Theory :: Theory() :
	location_ (),
	comments_ (NULL),
	name_ (value :: undefined :: NAME) {
	}
	Theory :: ~ Theory() {
	}

	mdl :: Theory*
	Theory :: parse (Lexer* lexer, mdl :: Theory* theory)
	{
		location_ = lexer->getLocation();
		name_ = lexer->scanName();
		lexer->scan<Token :: SEMICOLON>();
		comments_ =
			lexer->comments().isEmpty() ?
			NULL :
			new form :: Comments (lexer->comments());
		lexer->comments().clear();
		return new form :: Theory (location_, comments_, name_, theory);
	}

	// object :: Object implementation
	void
	Theory :: commitSuicide() {
		delete this;
	}
	Size_t
	Theory :: getVolume() const {
		return 0;
	}
	Size_t
	Theory :: getSizeOf() const {
		return sizeof (Theory);
	}
	void
	Theory :: show (String&) const {
	}
}
}


