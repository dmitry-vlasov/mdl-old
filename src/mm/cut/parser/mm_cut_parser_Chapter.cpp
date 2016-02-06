/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_cut_parser_Chapter.cpp                                */
/* Description:     mm cutter chapter parser                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mm/cut/parser/mm_cut_parser.hpp"

namespace mm {
namespace cut {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Chapter :: Chapter() :
	location_ (),
	header_ (NULL),
	content_ (NULL) {
	}
	Chapter :: ~ Chapter() {
	}

	inline source :: Chapter*
	Chapter :: parse (const source :: Source* source, Lexer* lexer)
	{
		location_ = lexer->getLocation();
		lexer->scan<Token :: HEADER>();
		header_ = new source :: Header (location_, lexer->getToken());

		lexer->scan<Token :: CHAPTER_END>();
		location_ = lexer->getLocation();
		lexer->scan<Token :: CONTENT, Token :: EOF_>();
		content_ = new source :: Content (location_, lexer->getToken());

		return new source :: Chapter (source, header_, content_);
	}

	// object :: Object implementation
	void
	Chapter :: commitSuicide() {
		delete this;
	}
	Size_t
	Chapter :: getVolume() const {
		return 0;
	}
	Size_t
	Chapter :: getSizeOf() const {
		return sizeof (Chapter);
	}
	void
	Chapter :: show (String&) const {
	}

	/****************************
	 *		Private members
	 ****************************/
}
}
}


