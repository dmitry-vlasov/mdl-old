/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_Import.cpp                                    */
/* Description:     import parser                                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_IMPORT_CPP_
#define MDL_PARSER_IMPORT_CPP_

#include "mdl/lexer/mdl_lexer.hpp"
#include "mdl/form/mdl_form.hpp"
#include "mdl/parser/mdl_parser.hpp"

namespace mdl {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	Import :: Import() :
	identificatorParser_ (new parser :: Identificator()),
	location_ (),
	identificator_ (NULL) {
	}
	Import :: ~ Import() {
		deleteAggregateObject (identificatorParser_);
	}

	mdl :: Import*
	Import :: parse (Lexer* lexer)
	{
		location_ = lexer->getLocation();
		identificator_ = identificatorParser_->parse (lexer);
		lexer->scan<Token :: SEMICOLON>();
		return new form :: Import (location_, identificator_);
	}

	// object :: Object implementation
	void
	Import :: commitSuicide() {
		delete this;
	}
	Size_t
	Import :: getVolume() const {
		return getAggregateVolume (identificatorParser_);
	}
	Size_t
	Import :: getSizeOf() const {
		return sizeof (Import);
	}
	void
	Import :: show (String&) const {
	}
}
}

#endif /*MDL_PARSER_IMPORT_CPP_*/
