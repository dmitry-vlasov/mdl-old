/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_parser_Include.cpp                                    */
/* Description:     inclusion parser                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "lexer/mm_lexer.hpp"
#include "ast/mm_ast.hpp"
#include "parser/mm_parser.hpp"

namespace mm {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Include :: Include() :
	path_ (INITIAL_PATH_CAPACITY),
	location_ () {
	}
	Include :: ~ Include() {
	}

	const mm :: source :: Include*
	Include :: parse (Lexer* const lexer)
	{
		location_ = lexer->getLocation();
		lexer->scan<Token :: PATH>();
		path_ = lexer->getToken();
		lexer->scan<Token :: INCLUSION_END>();
		return new ast :: source :: Include (location_, path_);
	}

	// object :: Object implementation
	void
	Include :: commitSuicide() {
		delete this;
	}
	Size_t
	Include :: getVolume() const
	{
		Size_t volume = 0;
		volume += path_.getVolume();
		volume += location_.getVolume();
		return volume;
	}
	Size_t
	Include :: getSizeOf() const {
		return sizeof (Include);
	}
	void
	Include :: show (String&) const {
	}
}
}


