/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_parser_block_Assertion.hpp                            */
/* Description:     assertion parser                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_PARSER_BLOCK_ASSERTION_HPP_
#define MM_PARSER_BLOCK_ASSERTION_HPP_

#include "interface/mm_interface.hpp"
#include "parser/mm_parser.dpp"
#include "lexer/mm_lexer.hpp"

namespace mm {
namespace parser {
namespace block {

class Assertion : public object :: Object {
public :
	Assertion (const parser :: Block* const);
	virtual ~ Assertion();

	// object :: Object interface
	virtual void commitSuicide() = 0;
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

protected :
	template<Token :: Type>
	void parseHeader (Lexer* const);

	value :: Label label_;
	vector :: Literal literalVector_;
	Location location_;

private :
	template<Token :: Type>
	void readExpression (Lexer* const);
	template<Token :: Type>
	void scanExpression (Lexer* const);
	void copyExpression (const vector :: Literal* const);

	const parser :: Block* const blockParser_;
	enum {
		INITIAL_LITERAL_VECTOR_CAPACITY = 256,
	};
};

}
}
}

#include "parser/block/mm_parser_block_Assertion.ipp"

#endif /*MM_PARSER_BLOCK_ASSERTION_HPP_*/
