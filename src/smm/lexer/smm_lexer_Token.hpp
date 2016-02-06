/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File Name:       smm_lexer_Token.hpp                                      */
/* Description:     smm tokens                                               */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace smm {
namespace lexer {

class Token : public nstd :: Object {
public :
	enum Type
	{
		UNKNOWN,    ///< unknown token
		CONSTANT,   ///< "$c"
		VARIABLE,   ///< "$v"
		FLOATING,   ///< "$f"
		DISJOINTED, ///< "$d"
		ESSENTIAL,  ///< "$e"
		AXIOMATIC,  ///< "$a"
		PROVABLE,   ///< "$p"
		EQUALITY,   ///< "$="
		END,        ///< "$."

		BLOCK_BEGIN,     ///< "${"
		BLOCK_END,       ///< "$}"
		INCLUSION_BEGIN, ///< "$["
		INCLUSION_END,   ///< "$]"
		COMMENT_BEGIN,   ///< "$("
		COMMENT_END,     ///< "$)"

		LITERAL,  ///< string of any of 94 printable ASCI characters except for the '$' symbol.
		INDEX,    ///< assertion index - and non negative integer.
		LABEL,    ///< assertion label
		PATH,     ///< file path

		PREFIX_E,    ///< "e"
		PREFIX_F,    ///< "f"
		PREFIX_I,    ///< "i"
		PREFIX_A,    ///< "a"
		PREFIX_P,    ///< "p"
		EOF_   ///< end of file
	};

	enum {
		NUMBER_OF_TOKENS = EOF_ + 1
	};

	static const Token unknown_;
	static const Token constant_;
	static const Token variable_;
	static const Token floating_;
	static const Token disjointed_;
	static const Token essential_;
	static const Token axiomatic_;
	static const Token provable_;
	static const Token equality_;
	static const Token end_;
	static const Token blockBegin_;
	static const Token blockEnd_;
	static const Token inclusionBegin_;
	static const Token inclusionEnd_;
	static const Token commentBegin_;
	static const Token commentEnd_;
	static const Token literal_;
	static const Token index_;
	static const Token label_;
	static const Token path_;
	static const Token equal_;
	static const Token prefix_e_;
	static const Token prefix_f_;
	static const Token prefix_i_;
	static const Token prefix_a_;
	static const Token prefix_p_;
	static const Token eof_;

	Token (const Type, const char* const);
	Token (const Token&);
	virtual ~ Token();

	static const char* getString (const Type);
	const char* getString() const {
		return string_;
	}
	Type getType() const {
		return type_;
	}

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual nstd :: Size_t getSizeOf() const;
	virtual nstd :: Size_t getVolume() const;
	virtual void show (nstd :: String<>&) const;

private :
	static const Token tokens_[NUMBER_OF_TOKENS];
	const Type type_;
	const char* const string_;
};

	template<class A>
	nstd :: String<A>&
	operator << (nstd :: String<A>&, const Token&);
}
	using lexer :: Token;
}

#include "smm/lexer/smm_lexer_Token.ipp"
#include "smm/lexer/smm_lexer_Token.cpp"


