/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_parser_block_Reference.hpp                            */
/* Description:     reference in proof parser                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_PARSER_BLOCK_REFERENCE_HPP_
#define MM_PARSER_BLOCK_REFERENCE_HPP_

#include "interface/mm_interface.hpp"
#include "parser/mm_parser.dpp"
#include "lexer/mm_lexer.hpp"

namespace mm {
namespace parser {
namespace block {

class Reference :
	public object :: Object,
	public Scalar<Reference> {
public :
	Reference();
	virtual ~ Reference();

	const mm :: source :: Reference* parse (Lexer* const, const mm :: source :: Block* const);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	const mm :: source :: Reference* createAssertionReference (const String&) const;
	const mm :: source :: Reference* createHypothesisReference (const String&, const mm :: source :: Block* const ) const;
	Location location_;
};

}
}
}

#endif /*MM_PARSER_BLOCK_REFERENCE_HPP_*/
