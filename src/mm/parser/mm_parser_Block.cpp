/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_parser_Block.cpp                                      */
/* Description:     metamath block parser                                    */
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

	Block :: Block (const bool isTop) :
	constants_ (new parser :: Constants()),
	variables_ (new parser :: Variables()),
	disjoined_ (new parser :: Disjoined()),
	include_ (new parser :: Include()),
	source_ (NULL),
	floating_ (new parser :: Floating (this)),
	essential_ (new parser :: Essential (this)),
	axiomatic_ (new parser :: Axiomatic (this)),
	provable_ (new parser :: Provable (this)),
	block_ (NULL),
	location_ (),
	isTop_ (isTop) {
	}
	Block :: ~ Block()
	{
		deleteAggregateObject (constants_);
		deleteAggregateObject (variables_);
		deleteAggregateObject (disjoined_);
		deleteAggregateObject (include_);
		deleteAggregateObject (source_);
		deleteAggregateObject (floating_);
		deleteAggregateObject (essential_);
		deleteAggregateObject (axiomatic_);
		deleteAggregateObject (provable_);
		deleteAggregateObject (block_);
	}

using manipulator :: endLine;

	mm :: source :: Block*
	Block :: parse
	(
		Lexer* const lexer,
		mm :: source :: Block* mmBlock
	)
	{
		mm :: source :: Block* outerBlock = mmBlock;
		while (true){
			location_ = lexer->getLocation();
			switch (lexer->scan()) {
			case Token :: CONSTANT :
				constants_->parse (lexer, mmBlock); break;
			case Token :: VARIABLE :
				variables_->parse (lexer, mmBlock); break;
			case Token :: DISJOINED :
				disjoined_->parse (lexer, mmBlock); break;
			case Token :: BLOCK_BEGIN :{
				if (block_ == NULL) {
					block_ = new parser :: Block (false);
				}
				mm :: source :: Block* const
					newMmBlock = new ast :: source :: Block (location_, mmBlock, NULL);
				lexer->comments().clear();
				block_->parse (lexer, newMmBlock);
				break;
			}
			case Token :: INCLUSION_BEGIN : {
				const mm :: source :: Include* const
					include = include_->parse (lexer);
				const String& path = include->getPath().getString();
				outerBlock->pushInclude (include);
				if (!Table :: files()->contains (path)) {
					Table :: files()->add (path);
					if (source_ == NULL) {
						source_ = new parser :: Source (false);
					}
					lexer->comments().clear();
					mmBlock = source_->parse (include, mmBlock);
				}
				break;
			}
			case Token :: IDENTIFICATOR :
				label_ = lexer->getToken();
				//std :: cout << "label: " << label_ << std :: endl;
				parseLabeledNode (lexer, mmBlock); break;
			case Token :: BLOCK_END :
			case Token :: EOF_ :
				lexer->comments().clear();
				return mmBlock;
			default :
				Error* error = new Error (location_, Error :: PARSER);
				error->message() << "unexpected token: "<< lexer->getToken() << endLine;
				error->message() << "should be one of : $c, $v, $d, ${, $( or <label> token" << endLine;
				throw error;
			}
		}
	}

	// object :: Object implementation
	void
	Block :: commitSuicide() {
		delete this;
	}
	Size_t
	Block :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (constants_);
		volume += getAggregateVolume (variables_);
		volume += getAggregateVolume (disjoined_);
		volume += getAggregateVolume (include_);
		volume += getAggregateVolume (source_);
		volume += getAggregateVolume (floating_);
		volume += getAggregateVolume (essential_);
		volume += getAggregateVolume (axiomatic_);
		volume += getAggregateVolume (provable_);
		volume += getAggregateVolume (block_);
		volume += location_.getVolume();
		volume += label_.getVolume();
		return volume;
	}
	Size_t
	Block :: getSizeOf() const {
		return sizeof (Block);
	}
	void
	Block :: show (String&) const {
	}

	/****************************
	 *		private members
	 ****************************/

	void
	Block :: parseLabeledNode (Lexer* const lexer, mm :: source :: Block* const mmBlock)
	{
		switch (lexer->scan()) {
		case Token :: FLOATING :
			floating_->parse (lexer, mmBlock); break;
		case Token :: ESSENTIAL :
			essential_->parse (lexer, mmBlock); break;
		case Token :: AXIOMATIC :
			axiomatic_->parse (lexer, mmBlock); break;
		case Token :: PROVABLE :
			provable_->parse (lexer, mmBlock); break;
		default :
			Error* error = new Error (location_, Error :: PARSER);
			error->message() << "unexpected token: " << lexer->getToken() << endLine;
			error->message() << "should be one of : $f, $e, $a or $p token" << endLine;
			throw error;
		}
	}
}
}


