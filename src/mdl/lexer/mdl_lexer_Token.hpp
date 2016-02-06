/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_lexer_Token.hpp                                      */
/* Description:     mdl tokens                                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace lexer {

class Token : public nstd :: Object {
public :
	// mdl lexer token types.
	enum Type
	{
		UNKNOWN         = 0,  ///< unknown token
		IMPORT          = 1,  ///< "import"
		THEORY          = 2,  ///< "theory"

		CONSTANT        = 3,  ///< "constant"
		TYPE            = 4,  ///< "type"
		RULE            = 5,  ///< "rule"
		AXIOM           = 6,  ///< "axiom"
		DEFINITION      = 7,  ///< "definition"
		THEOREM         = 8,  ///< "theorem"
		PROBLEM         = 9,  ///< "problem"
		PROOF           = 10, ///< "proof"

		TERM            = 11, ///< "term"
		HYP             = 12, ///< "hyp"
		PROP            = 13, ///< "prop"
		DISJOINTED      = 14, ///< "disjointed"
		DEFIENDUM       = 15, ///< "defiendum"
		DEFINIENS       = 16, ///< "definiens"

		VARIABLE        = 17, ///< "var"
		CLAIM           = 18, ///< "claim"
		NOTATION        = 19, ///< "notation"
		STEP            = 20, ///< "step"
		QED             = 21, ///< "qed"
		ABBREVIATION    = 22, ///< "abbreviation"
		MEANING         = 23, ///< "meaning"

		OPEN_BRACE      = 24, ///< "{"
		CLOSE_BRACE     = 25, ///< "}"
		OPEN_BRACKET    = 26, ///< "("
		CLOSE_BRACKET   = 27, ///< ")"

		HORISONTAL_BAR  = 28, ///< "----*"
		TURNSTILE       = 29, ///< "|-"

		// symbols section
		SHARP           = 30, ///< "#"
		SEMICOLON       = 31, ///< ";"
		COLON           = 32, ///< ":"
		COMMA           = 33, ///< ","
		DOT             = 34, ///< "."
		EQUALITY        = 35, ///< "="
		QUESTION        = 36, ///< "?"
		EXCLAMATION     = 37, ///< "!"
		UP_ARROW        = 38, ///< "^"
		AST             = 39, ///< "*"

		NAME            = 40, ///< "[a-zA-Z][a-zA-Z0-9_\-]*"
		LITERAL         = 41, ///< "[!-:<-~]+"
		NUMBER          = 42, ///< [1-9][0-9]*

		CONTENTS        = 43, ///< "contents"
		OF              = 44, ///< "of"
		COMMENT_BEGIN   = 45, ///< "/*"
		COMMENT_END     = 46, ///< "*/"
		LINE_COMMENT    = 47, ///< "*//"

		SYMBOL          = 48, ///< "symbol"
		ASCII           = 49, ///< "ascii"
		LATEX           = 50, ///< "latex"

		// evaluation section
		EVALUATION      = 51, ///< "evaluation"
		OPEN_SQ_BRACKET = 52, ///< "["
		CLOSE_SQ_BRACKET= 53, ///< "]"
		PLUS            = 54, ///< "+"
		MINUS           = 55, ///< "-"
		SUM             = 56, ///< "sum"
		MULT            = 57, ///< "mult"
		CONST           = 58, ///< "const"
		LEXP            = 59, ///< "lexp"
		SUB_CPLX        = 60, ///< "sub_cplx"
		EXP_CPLX        = 61, ///< "exp_cplx"
		EXP_AVG         = 62, ///< "exp_avg"
		EXP_SIM         = 63, ///< "exp_sim"
		EXP_EQ          = 64, ///< "exp_eq"
		EXP_DISP        = 65, ///< "exp_disp"
		FORKING         = 66, ///< "forking"
		REAL_NUMBER     = 67, ///< "3.149215"
		WEIGHTED_SUM    = 68, ///< "w_sum"
		BARRIER         = 69, ///< "barrier"

		EOF_            = 70  ///< end of file
	};

	enum {
		NUMBER_OF_TOKENS = EOF_ + 1
	};

	static const Token unknown_;
	static const Token import_;
	static const Token theory_;

	static const Token constant_;
	static const Token type_;
	static const Token rule_;
	static const Token axiom_;
	static const Token definition_;
	static const Token theorem_;
	static const Token problem_;
	static const Token proof_;

	static const Token term_;
	static const Token hyp_;
	static const Token prop_;
	static const Token disjointed_;
	static const Token defiendum_;
	static const Token definiens_;

	static const Token variable_;
	static const Token claim_;
	static const Token notation_;
	static const Token step_;
	static const Token qed_;
	static const Token abbreviation_;
	static const Token meaning_;

	static const Token openBrace_;
	static const Token closeBrace_;
	static const Token openBracket_;
	static const Token closeBracket_;

	static const Token horisontalBar_;
	static const Token turnstile_;

	static const Token sharp_;
	static const Token semicolon_;
	static const Token colon_;
	static const Token comma_;
	static const Token dot_;
	static const Token equality_;
	static const Token question_;
	static const Token exclamation_;
	static const Token upArrow_;
	static const Token ast_;

	static const Token name_;
	static const Token literal_;
	static const Token number_;

	static const Token contents_;
	static const Token of_;
	static const Token commentBegin_;
	static const Token commentEnd_;
	static const Token lineComment_;

	static const Token symbol_;
	static const Token ascii_;
	static const Token latex_;

	static const Token evaluation_;
	static const Token openSqBracket_;
	static const Token closeSqBracket_;
	static const Token plus_;
	static const Token minus_;
	static const Token sum_;
	static const Token mult_;
	static const Token const_;
	static const Token lexp_;
	static const Token subCplx_;
	static const Token expCplx_;
	static const Token expAvg_;
	static const Token expSim_;
	static const Token expEq_;
	static const Token expDisp_;
	static const Token forking_;
	static const Token realNumber_;
	static const Token weightedSum_;
	static const Token barrier_;

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

#include "mdl/lexer/mdl_lexer_Token.ipp"
#include "mdl/lexer/mdl_lexer_Token.cpp"


