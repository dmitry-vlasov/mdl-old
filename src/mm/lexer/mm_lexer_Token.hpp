/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_lexer_Token.hpp                                       */
/* Description:     metamath tokens                                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mm {
namespace lexer {

class Token {
public :
	enum Type
	{
		UNKNOWN	= 0,  ///< unknown token

		CONSTANT   = 1, ///< "$c"
		VARIABLE   = 2, ///< "$v"
		FLOATING   = 3, ///< "$f"
		DISJOINED  = 4, ///< "$d"
		ESSENTIAL  = 5, ///< "$e"
		AXIOMATIC  = 6, ///< "$a"
		PROVABLE   = 7, ///< "$p"
		PROOF      = 8, ///< "$="
		END        = 9, ///< "$."

		BLOCK_BEGIN      = 10, ///< "${"
		BLOCK_END        = 11, ///< "$}"
		INCLUSION_BEGIN  = 12, ///< "$["
		INCLUSION_END    = 13, ///< "$]"
		COMMENT_BEGIN    = 14, ///< "$("
		COMMENT_END      = 15, ///< "$)"

		LITERAL          = 16, ///< string of any of 94 printable ASCI characters except for the '$' symbol.
		IDENTIFICATOR    = 17, ///< string of letters, numbers, hyphen, underscope and period.
		PATH             = 18, ///< path to file

		EOF_  = 19  ///< end of file
	};

	enum {
		NUMBER_OF_TOKENS = EOF_ + 1
	};

	static const Token unknown_;
	static const Token constant_;
	static const Token variable_;
	static const Token floating_;
	static const Token disjoined_;
	static const Token essential_;
	static const Token axiomatic_;
	static const Token provable_;
	static const Token proof_;
	static const Token end_;
	static const Token blockBegin_;
	static const Token blockEnd_;
	static const Token inclusionBegin_;
	static const Token inclusionEnd_;
	static const Token commentBegin_;
	static const Token commentEnd_;
	static const Token literal_;
	static const Token identificator_;
	static const Token path_;
	static const Token eof_;

	static const Token tokens_[NUMBER_OF_TOKENS];

	Token (const Type, const char* const);
	Token (const Token&);
	virtual ~ Token();

	static const char* getString (const Type);
	Type getType() const;
	const char* getString() const;

	// nstd :: Object interface
	virtual void commitSuicide();
	nstd :: Size_t getSizeOf() const;
	nstd :: Size_t getVolume() const;
	void show (nstd :: String<>&) const;

private :
	const Type type_;
	const char* const string_;
};

	template<class A>
	nstd :: String<A>&
	operator << (nstd :: String<A>&, const Token&);
}
	using lexer :: Token;
}

#include "mm/lexer/mm_lexer_Token.ipp"
#include "mm/lexer/mm_lexer_Token.cpp"


