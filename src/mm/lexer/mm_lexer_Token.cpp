/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_lexer_Token.cpp                                       */
/* Description:     metamath tokens                                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mm/lexer/mm_lexer.hpp"

namespace mm {
namespace lexer {

	/********************************
	 *		Public static members
	 ********************************/

	const Token Token :: unknown_ (UNKNOWN, "unknown");
	const Token Token :: constant_ (CONSTANT, "$c");
	const Token Token :: variable_(VARIABLE, "$v");
	const Token Token :: floating_ (FLOATING, "$f");
	const Token Token :: disjoined_ (DISJOINED, "$d");
	const Token Token :: essential_ (ESSENTIAL, "$e");
	const Token Token :: axiomatic_ (AXIOMATIC, "$a");
	const Token Token :: provable_ (PROVABLE, "$p");
	const Token Token :: proof_ (PROOF, "$=");
	const Token Token :: end_ (END, "$.");
	const Token Token :: blockBegin_ (BLOCK_BEGIN, "${");
	const Token Token :: blockEnd_ (BLOCK_END, "$}");
	const Token Token :: inclusionBegin_ (INCLUSION_BEGIN, "$[");
	const Token Token :: inclusionEnd_ (INCLUSION_END, "$]");
	const Token Token :: commentBegin_ (COMMENT_BEGIN, "$(");
	const Token Token :: commentEnd_ (COMMENT_END, "$)");
	const Token Token :: literal_ (LITERAL, "literal");
	const Token Token :: identificator_ (IDENTIFICATOR, "identificator");
	const Token Token :: path_ (PATH, "path");
	const Token Token :: eof_ (EOF_, "eof");

	const Token Token :: tokens_[NUMBER_OF_TOKENS] =
	{
		unknown_,		constant_,		variable_,		floating_, 		disjoined_,
		essential_,		axiomatic_,		provable_,	proof_,			end_,

		blockBegin_,	blockEnd_,
		inclusionBegin_,	inclusionEnd_,
		commentBegin_,		commentEnd_,

		literal_,				identificator_,	path_,  			eof_
	};

	/****************************
	 *		Public members
	 ****************************/

	const char*
	Token :: getString (const Type type)
	{
		for (int i = 0 ; i < NUMBER_OF_TOKENS; i ++) {
			if (tokens_[i].getType() == type) {
				return tokens_[i].getString();
			}
		}
		return "unknown";
	}

	// nstd :: Object implementation
	void
	Token :: commitSuicide() {
		delete this;
	}
	nstd :: Size_t
	Token :: getSizeOf() const {
		return sizeof (Token);
	}
	nstd :: Size_t
	Token :: getVolume() const {
		return 0;
	}
	void
	Token :: show (nstd :: String<>& string) const {
		string << getString();
	}
}
}



