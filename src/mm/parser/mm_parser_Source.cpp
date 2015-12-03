/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_parser_Source.cpp                                     */
/* Description:     metamath source parser                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_PARSER_SOURCE_CPP_
#define MM_PARSER_SOURCE_CPP_

#include "lexer/mm_lexer.hpp"
#include "ast/mm_ast.hpp"
#include "parser/mm_parser.hpp"

namespace mm {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Source :: Source (const bool isTop) :
	isTop_ (isTop),
	lexer_ (NULL),
	blockParser_ (new parser :: Block (true)),
	location_ (),
	include_ (NULL),
	block_ (NULL) {
	}
	Source :: ~ Source()
	{
		deleteAggregateObject (blockParser_);
		deleteAggregateObject (lexer_);
	}

	const mm :: source :: Source*
	Source :: parse (const Path* const path)
	{
		include_ = new ast :: source :: Include (path);
		source_ = new ast :: source :: Source (include_);
		const String& file = include_->getPath().getString();
		Table :: files()->add (file);
		open();
		location_ = lexer_->getLocation();
		block_ = new ast :: source :: Block (location_, source_);
		blockParser_->parse (lexer_, block_);
		close();
		source_->setBlock (block_);
		return source_;
	}
	mm :: source :: Block*
	Source :: parse
	(
		const mm :: source :: Include* const include,
		mm :: source :: Block* block
	)
	{
		include_ = include;
		source_ = new ast :: source :: Source (include_, block);

		open();
		block_ = new ast :: source :: Block (location_, NULL, block, source_);
		block = blockParser_->parse (lexer_, block_);
		close();
		source_->setBlock (block_);
		return block;
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
		volume += getAggregateVolume (blockParser_);
		volume += getAggregateVolume (lexer_);
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

	void
	Source :: open()
	{
		const String& file = include_->getPath().getString();
		if (lexer_ != NULL) {
			lexer_->open (file);
		} else {
			lexer_ = new Lexer (file);
			lexer_->open();
		}
	}
	void
	Source :: close()
	{
		if (lexer_ == NULL) {
			const String& path = include_->getPath().getString();
			Error* error = new Error (Error :: INPUT);
			error->message() << "attempt to close non opened " << path << endLine;
			throw error;
		}
		if (lexer_->getTokenType() != Token :: EOF_) {
			const String& path = include_->getPath().getString();
			Error* error = new Error (Error :: INPUT);
			error->message() << "unexpected token: "<< lexer_->getToken() << endLine;
			error->message() << "EOF expected in file " << path << endLine;
			throw error;
		}
		lexer_->close();
	}
}
}

#endif /*MM_PARSER_SOURCE_CPP_*/
