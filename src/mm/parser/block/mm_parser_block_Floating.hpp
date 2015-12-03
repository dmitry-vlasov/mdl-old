/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_parser_block_Floating.hpp                             */
/* Description:     floating hypothesis parser                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_PARSER_BLOCK_FLOATING_HPP_
#define MM_PARSER_BLOCK_FLOATING_HPP_

#include "interface/mm_interface.hpp"
#include "parser/mm_parser.dpp"
#include "lexer/mm_lexer.hpp"

namespace mm {
namespace parser {
namespace block {

class Floating :
	public object :: Object,
	public Scalar<Floating> {
public :
	Floating (const parser :: Block* const);
	virtual ~ Floating();

	const mm :: source :: Hypothesis* parse (Lexer* const, mm :: source :: Block* const);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	const parser :: Block* const blockParser_;

	value :: Label label_;
	value :: Literal type_;
	value :: Literal variable_;
	Location location_;
};

}
}
}

#endif /*MM_PARSER_BLOCK_FLOATING_HPP_*/
