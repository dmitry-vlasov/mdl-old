/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_lexer_Token.ipp                                      */
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

	/****************************
	 *		Public members
	 ****************************/

	inline
	Token :: Token (const Type type, const char* const string) :
	type__ (type),
	string_ (string) {
	}
	inline
	Token :: Token (const Token& token) :
	type__ (token.type__),
	string_ (token.string_) {
	}
	Token :: ~ Token() {
	}

	inline const char*
	Token :: getString() const {
		return string_;
	}
	inline Token :: Type
	Token :: getType() const {
		return type__;
	}
	inline nstd :: Size_t
	Token :: getLength() const {
		return nstd :: String<> :: getStringLength (string_);
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


