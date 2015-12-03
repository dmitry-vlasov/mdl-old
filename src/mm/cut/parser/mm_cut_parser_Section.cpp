/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_cut_parser_Section.cpp                                */
/* Description:     mm cutter section parser                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_CUT_PARSER_SECTION_CPP_
#define MM_CUT_PARSER_SECTION_CPP_

#include "mm/cut/parser/mm_cut_parser.hpp"

namespace mm {
namespace cut {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Section :: Section() :
	location_ (),
	header_ (NULL),
	content_ (NULL) {
	}
	Section :: ~ Section() {
	}

	inline source :: Section*
	Section :: parse
	(
		const source :: Source* source,
		const source :: Chapter* chapter,
		Lexer* lexer
	)
	{
		location_ = lexer->getLocation();
		lexer->scan<Token :: HEADER>();
		header_ = new source :: Header (location_, lexer->getToken());

		lexer->scan<Token :: SECTION_END>();
		location_ = lexer->getLocation();
		lexer->scan<Token :: CONTENT, Token :: EOF_>();
		content_ = new source :: Content (location_, lexer->getToken());

		return new source :: Section (source, chapter, header_, content_);
	}

	// object :: Object implementation
	void
	Section :: commitSuicide() {
		delete this;
	}
	Size_t
	Section :: getVolume() const {
		return 0;
	}
	Size_t
	Section :: getSizeOf() const {
		return sizeof (Section);
	}
	void
	Section :: show (String&) const {
	}

	/****************************
	 *		Private members
	 ****************************/
}
}
}

#endif /*MM_CUT_PARSER_SECTION_CPP_*/
