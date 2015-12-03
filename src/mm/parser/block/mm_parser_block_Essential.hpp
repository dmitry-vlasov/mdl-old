/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_parser_block_Essential.hpp                            */
/* Description:     essential hypothesis parser                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_PARSER_BLOCK_ESSENTIAL_HPP_
#define MM_PARSER_BLOCK_ESSENTIAL_HPP_

#include "interface/mm_interface.hpp"
#include "parser/mm_parser.dpp"
#include "lexer/mm_lexer.hpp"

namespace mm {
namespace parser {
namespace block {

class Essential :
	public object :: Object,
	public Scalar<Essential>  {
public :
	Essential (const parser :: Block* const);
	virtual ~ Essential();

	const mm :: source :: Hypothesis* parse (Lexer* const, mm :: source :: Block* const);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	void readExpression (Lexer* const);
	void scanExpression (Lexer* const);
	void copyExpression (const vector :: Literal* const);

	const parser :: Block* const blockParser_;

	value :: Label label_;
	vector :: Literal literalVector_;
	Location location_;
	enum {
		INITIAL_LITERAL_VECTOR_CAPACITY = 256,
	};
};

}
}
}

#endif /*MM_PARSER_BLOCK_ESSENTIAL_HPP_*/
