/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_parser_Block.hpp                                      */
/* Description:     metamath block parser                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "interface/mm_interface.hpp"
#include "parser/mm_parser.dpp"
#include "lexer/mm_lexer.hpp"

namespace mm {
namespace parser {

class Block :
	public object :: Object,
	public Scalar<Block> {
public :
	Block (const bool);
	virtual ~ Block();

	const String& getLabel() const;
	mm :: source :: Block* parse (Lexer* const, mm :: source :: Block*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	void parseLabeledNode (Lexer* const, mm :: source :: Block* const);

	// internal part
	parser :: Constants* constants_;
	parser :: Variables* variables_;
	parser :: Disjoined* disjoined_;
	parser :: Include* include_;
	parser :: Source* source_;
	parser :: Floating* floating_;
	parser :: Essential* essential_;
	parser :: Axiomatic* axiomatic_;
	parser :: Provable* provable_;
	parser :: Block* block_;

	String label_;
	Location location_;
	const bool isTop_;
	enum {
		INITIAL_LABEL_CAPACITY = 256
	};
};

}
}

#include "parser/mm_parser_Block.ipp"


