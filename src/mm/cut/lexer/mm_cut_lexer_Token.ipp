/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_cut_lexer_Token.ipp                                   */
/* Description:     mm source file cutting lexer tokens                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_CUT_LEXER_TOKEN_IPP_
#define MM_CUT_LEXER_TOKEN_IPP_

namespace mm {
namespace cut {
namespace lexer {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Token :: Token (const Type type, const char* const string) :
	type_ (type),
	string_ (string) {
	}
	inline
	Token :: Token (const Token& token) :
	type_ (token.type_),
	string_ (token.string_) {
	}
	Token :: ~ Token() {
	}

	inline void
	Token :: show (nstd :: String<>& string) const {
		string << getString();
	}

	/********************************
	 *		Overloaded operators
	 ********************************/

	template<class A>
	inline nstd :: String<A>&
	operator << (nstd :: String<A>& string, const Token& token) {
		return string.operator << (token.getString());
	}
}
}
}

#endif /*MM_CUT_LEXER_TOKEN_IPP_*/
