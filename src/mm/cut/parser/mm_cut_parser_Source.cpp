/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_cut_parser_Source.cpp                                 */
/* Description:     mm source file cutting parser                            */
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
	Source :: Source() :
	lexer_ (NULL),
	path_ (NULL),
	location_ (),
	chapterParser_ (new parser :: Chapter()),
	sectionParser_ (new parser :: Section()),
	source_ (NULL),
	header_ (NULL),
	content_ (NULL),
	chapter_ (NULL),
	section_ (NULL),
	prevChapter_ (NULL),
	prevSection_ (NULL){
	}
	Source :: ~ Source()
	{
		deleteAggregateObject (path_);
		deleteAggregateObject (lexer_);
		deleteAggregateObject (chapterParser_);
		deleteAggregateObject (sectionParser_);
	}

	inline const cut :: Source*
	Source :: parse (const Path* const path)
	{
		path_ = new Path (*path);
		open();
		parseContents();
		close();
		return source_;
	}

	// object :: Object implementation
	void
	Source :: commitSuicide() {
		delete this;
	}
	Size_t
	Source :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (path_);
		volume += getAggregateVolume (lexer_);
		volume += getAggregateVolume (chapterParser_);
		volume += getAggregateVolume (sectionParser_);
		return volume;
	}
	Size_t
	Source :: getSizeOf() const {
		return sizeof (Source);
	}
	void
	Source :: show (String&) const {
	}

	/****************************
	 *		Private members
	 ****************************/

using manipulator :: space;
using manipulator :: endLine;

	void
	Source :: parseContents()
	{
		location_ = lexer_->getLocation();
		header_ = new source :: Header (location_, path_->getName());

		location_ = lexer_->getLocation();
		lexer_->scan<Token :: CONTENT, Token :: EOF_>();
		content_ = new source :: Content (location_, lexer_->getToken());

		source_ = new source :: Source (header_, content_);
		if (lexer_->getTokenType() == Token :: EOF_) {
			return;
		}
		while (true) {
			switch (lexer_->scan<Token :: CHAPTER_BEGIN, Token :: SECTION_BEGIN>()) {
			case Token :: CHAPTER_BEGIN : {
				chapter_ = chapterParser_->parse (source_, lexer_);
				chapter_->setPrevious (prevChapter_);
				prevSection_ = NULL;
				prevChapter_ = chapter_;
				source_->addChapter (chapter_);
				break;
			}
			case Token :: SECTION_BEGIN : {
				section_ = sectionParser_->parse (source_, chapter_, lexer_);
				if (prevSection_ == NULL) {
					if (prevChapter_ != NULL) {
						section_->setPrevious (prevChapter_->getPrevious());
					}
				} else {
					section_->setPrevious (prevSection_);
				}
				prevSection_ = section_;
				if (chapter_ == NULL) {
					source_->addSection (section_);
				} else {
					chapter_->addSection (section_);
				}
				break;
			}
			default :
				Error* error = new Error (location_, Error :: PARSER);
				error->message() << "unexpected token: " << lexer_->getToken () << space;
				error->message() << "should be one of : $c, ${, $[, EOF" << endLine;
				throw error;
			}
			if (lexer_->getTokenType() == Token :: EOF_) {
				break;
			}
		}
	}

	void
	Source :: open()
	{
		if (lexer_ != NULL) {
			throw new Error (Error :: INPUT, "attempt to reopen source file.\n");
		}
		const String& path = path_->getString();
		lexer_ = new Lexer (path);
		lexer_->open();
	}
	void
	Source :: close ()
	{
		if (lexer_ == NULL) {
			throw new Error (Error :: INPUT, "attempt to close non opened file.\n");
		}
		const Token :: Type
			lastToken = lexer_->getTokenType();
		if (lastToken != Token :: EOF_) {
			throw new Error (Error :: PARSER, "EOF expected");
		}
		lexer_->close();
	}
}
}
}


