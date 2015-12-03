/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_lexer_Token.hpp                                      */
/* Description:     del tokens                                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_LEXER_TOKEN_HPP_
#define DEL_LEXER_TOKEN_HPP_

namespace del {
namespace lexer {

class Token : public nstd :: Object {
public :
	// del lexer token types.
	enum Type
	{
		UNKNOWN          = 0,  ///< unknown token
		SUBSET           = 1,  ///< "⊑", \u2291
		INTERSECT        = 2,  ///< "⊓", \u2293
		EXISTS           = 3,  ///< "∃", \u2203
		EQUAL            = 4,  ///< "≡", \u2261
		TOP              = 5,  ///< "⊤", \u22a4
		MODELS           = 6,  ///< "⊨", \u22a8
		DOES_NOT_MODEL   = 7,  ///< "⊭", \u22ad
		DOT              = 8,  ///< "."

		THEORY           = 9,  ///< "theory"
		DOES             = 10, ///< "does"
		SOLUTION         = 11, ///< "solution"

		EQUALITY         = 12,  ///< "="
		QUESTION         = 13, ///< "?"
		ASSERTION        = 14, ///< "!"
		COMMA            = 15, ///< ","

		OPEN_BRACE       = 16, ///< "{"
		CLOSE_BRACE      = 17, ///< "}"
		OPEN_BRACKET     = 18, ///< "("
		CLOSE_BRACKET    = 19, ///< ")"

		NAME             = 20, ///< "[a-zA-Z][a-zA-Z0-9_\-]*"
		PATH             = 21, ///< "<path to a file>"

		COMMENT_BEGIN    = 22, ///< "/*"
		COMMENT_END      = 23, ///< "*/"
		LINE_COMMENT     = 24, ///< "//"

		SIGNATURE        = 25, ///< "signature"
		CONCEPT          = 26, ///< "concept"
		RELATION         = 27, ///< "relation"
		COPY             = 28, ///< "copy"
		DECOMPOSE        = 29, ///< "decompose"
		DECOMPOSITION_OF = 30, ///< "decomposition_of"
		UNION            = 31, ///< "⊔",  \u2294
		ASSERT           = 32, ///< "assert"
		CONCEPTS         = 33, ///< "concepts"
		RELATIONS        = 34, ///< "relations"
		FILE             = 35, ///< "file:"
		MINIMIZE         = 36, ///< "minimize
		MINIMIZATION_OF  = 37, ///< "minimization_of

		EOF_             = 38  ///< end of file
	};

	enum {
		NUMBER_OF_TOKENS = EOF_ + 1
	};

	static const Token unknown_;
	static const Token subset_;
	static const Token intersect_;
	static const Token exists_;
	static const Token equal_;
	static const Token top_;
	static const Token models_;
	static const Token does_not_model_;
	static const Token dot_;

	static const Token theory_;
	static const Token does_;
	static const Token solution_;
	static const Token equality_;
	static const Token question_;
	static const Token assertion_;
	static const Token comma_;
	static const Token openBrace_;
	static const Token closeBrace_;
	static const Token openBracket_;
	static const Token closeBracket_;

	static const Token name_;
	static const Token path_;

	static const Token commentBegin_;
	static const Token commentEnd_;
	static const Token lineComment_;

	static const Token signature_;
	static const Token concept_;
	static const Token relation_;
	static const Token copy_;
	static const Token decompose_;
	static const Token decompositionOf_;
	static const Token union_;
	static const Token assert_;
	static const Token concepts_;
	static const Token relations_;
	static const Token file_;
	static const Token minimize_;
	static const Token minimizationOf_;

	static const Token eof_;

	Token (const Type, const char* const);
	Token (const Token&);
	virtual ~ Token();

	static const char* getString (const Type);
	const char* getString() const;
	Type getType() const;
	nstd :: Size_t getLength() const;

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual nstd :: Size_t getSizeOf() const;
	virtual nstd :: Size_t getVolume() const;
	virtual void show (nstd :: String<>&) const;

private :
	static const Token tokens_[NUMBER_OF_TOKENS];

	const Type type__;
	const char* const string_;
};

	template<class A>
	nstd :: String<A>&
	operator << (nstd :: String<A>&, const Token&);
}
	using lexer :: Token;
}

#include "del/lexer/del_lexer_Token.ipp"
#include "del/lexer/del_lexer_Token.cpp"

#endif /*DEL_LEXER_TOKEN_HPP_*/
