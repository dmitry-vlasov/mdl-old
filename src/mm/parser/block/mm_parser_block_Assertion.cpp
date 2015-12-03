/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_parser_block_Assertion.cpp                            */
/* Description:     assertion parser                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_PARSER_BLOCK_ASSERTION_CPP_
#define MM_PARSER_BLOCK_ASSERTION_CPP_

#include "ast/mm_ast.hpp"
#include "math/mm_math.hpp"
#include "parser/mm_parser.hpp"

namespace mm {
namespace parser {
namespace block {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Assertion :: Assertion (const parser :: Block* const blockParser) :
	label_ (value :: undefined :: LABEL),
	literalVector_ (INITIAL_LITERAL_VECTOR_CAPACITY),
	location_ (),
	blockParser_ (blockParser) {
	}
	Assertion :: ~ Assertion() {
	}

	// object :: Object implementation
	Size_t
	Assertion :: getVolume() const
	{
		Size_t volume = 0;
		volume += literalVector_.getVolume();
		volume += location_.getVolume();
		return volume;
	}
	Size_t
	Assertion :: getSizeOf() const {
		return sizeof (Assertion);
	}
	void
	Assertion :: show (String&) const {
	}

	/****************************
	 *		Private members
	 ****************************/
	void
	Assertion :: copyExpression (const vector :: Literal* const correctExpression)
	{
		literalVector_.clear();
		for (index :: Literal i = 0; i < correctExpression->getSize(); i++) {
			const value :: Literal
				literal = correctExpression->getValue (i);
			literalVector_.add (literal);
		}
	}
}
}
}

#endif /*MM_PARSER_BLOCK_ASSERTION_CPP_*/
