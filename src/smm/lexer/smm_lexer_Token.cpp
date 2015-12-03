/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File Name:       smm_lexer_Token.cpp                                      */
/* Description:     smm tokens                                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_LEXER_TOKEN_CPP_
#define SMM_LEXER_TOKEN_CPP_

namespace smm {
namespace lexer {

	/********************************
	 *		Public static members
	 ********************************/

	const Token Token :: unknown_ (UNKNOWN, "unknown");
	const Token Token :: constant_ (CONSTANT, "$c");
	const Token Token :: variable_(VARIABLE, "$v");
	const Token Token :: floating_ (FLOATING, "$f");
	const Token Token :: disjointed_ (DISJOINTED, "$d");
	const Token Token :: essential_ (ESSENTIAL, "$e");
	const Token Token :: axiomatic_ (AXIOMATIC, "$a");
	const Token Token :: provable_ (PROVABLE, "$p");
	const Token Token :: equality_ (EQUALITY, "$=");
	const Token Token :: end_ (END, "$.");

	const Token Token :: blockBegin_ (BLOCK_BEGIN, "${");
	const Token Token :: blockEnd_ (BLOCK_END, "$}");
	const Token Token :: inclusionBegin_ (INCLUSION_BEGIN, "$[");
	const Token Token :: inclusionEnd_ (INCLUSION_END, "$]");
	const Token Token :: commentBegin_ (COMMENT_BEGIN, "$(");
	const Token Token :: commentEnd_ (COMMENT_END, "$)");

	const Token Token :: literal_ (LITERAL, "[!-#%-~]+");
	const Token Token :: index_ (INDEX, "[0-9]+");
	const Token Token :: label_ (LABEL, "[a-zA-Z0-9]+");
	const Token Token :: path_ (INDEX, "[a-zA-Z0-9\\-_./]+");

	const Token Token :: prefix_e_ (PREFIX_E, "e");
	const Token Token :: prefix_f_ (PREFIX_F, "f");
	const Token Token :: prefix_i_ (PREFIX_I, "i");
	const Token Token :: prefix_a_ (PREFIX_A, "a");
	const Token Token :: prefix_p_ (PREFIX_P, "p");
	const Token Token :: eof_ (EOF_, "eof");

	const Token Token :: tokens_[NUMBER_OF_TOKENS] =
	{
		unknown_,   constant_,  variable_, floating_, disjointed_,
		essential_, axiomatic_, provable_, equality_, end_,
		prefix_e_,  prefix_f_,  prefix_i_, prefix_a_, prefix_p_,
		blockBegin_,   blockEnd_,   inclusionBegin_, inclusionEnd_,
		commentBegin_, commentEnd_, literal_, eof_,  index_, label_, path_
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
		return unknown_.getString();
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
}
}

#endif /* SMM_LEXER_TOKEN_CPP_ */
