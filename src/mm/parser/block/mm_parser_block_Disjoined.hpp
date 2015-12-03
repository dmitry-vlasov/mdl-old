/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_parser_block_Disjoined.hpp                            */
/* Description:     disjoined parser                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_PARSER_BLOCK_DISJOINED_HPP_
#define MM_PARSER_BLOCK_DISJOINED_HPP_

#include "interface/mm_interface.hpp"
#include "parser/mm_parser.dpp"
#include "lexer/mm_lexer.hpp"

namespace mm {
namespace parser {
namespace block {

class Disjoined :
	public object :: Object,
	public Scalar<Disjoined> {
public :
	Disjoined();
	virtual ~ Disjoined();

	const mm :: source :: Disjoined* parse (Lexer* const, mm :: source :: Block* const);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	vector :: Literal literalVector_;
	Location location_;
	enum {
		INITIAL_DISJOINED_VECTOR_CAPACITY = 256,
	};
};

}
}
}

#endif /*MM_PARSER_BLOCK_DISJOINED_HPP_*/
