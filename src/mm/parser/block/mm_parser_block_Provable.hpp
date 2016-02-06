/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_parser_block_Provable.hpp                             */
/* Description:     provable assertion parser                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "parser/block/mm_parser_block_Assertion.hpp"

namespace mm {
namespace parser {
namespace block {

class Provable :
	public Assertion,
	public Scalar<Provable> {
public :
	Provable (const parser :: Block* const);
	virtual ~ Provable();

	const mm :: source :: Assertion* parse (Lexer* const, mm :: source :: Block* const);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	// internal part
	parser :: Proof* proofParser_;

	// external part
	const mm :: source :: Proof* proof_;
};

}
}
}


