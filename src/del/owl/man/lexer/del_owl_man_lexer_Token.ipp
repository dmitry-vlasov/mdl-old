/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_lexer_Token.ipp                              */
/* Description:     manchester OWL tokens                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace del {
namespace owl {
namespace man {
namespace lexer {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Token :: Token () :
	type__ (UNKNOWN),
	token_ () {
	}
	inline
	Token :: Token (const Type type, const char* const token) :
	type__ (type),
	token_ (token) {
	}
	inline
	Token :: Token (const Token& token) :
	type__ (token.type__),
	token_ (token.token_) {
	}
	Token :: ~ Token() {
	}

	inline const char*
	Token :: getString() const {
		return token_;
	}
	inline Token :: Type
	Token :: getType() const {
		return type__;
	}
	inline nstd :: Size_t
	Token :: getLength() const {
		return nstd :: String<> :: getStringLength (token_);
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
}


