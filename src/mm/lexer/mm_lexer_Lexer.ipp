/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_lexer_Lexer.ipp                                       */
/* Description:     metamath lexer class                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_LEXER_LEXER_IPP_
#define MM_LEXER_LEXER_IPP_

#include "auxiliary/mm_auxiliary.hpp"

namespace mm {
namespace lexer {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Lexer :: Lexer (const String& fileName) :
	source_ (fileName),
	scaner_ (source_),
	tokenType_ (Token :: UNKNOWN),
	token_ (INITIAL_TOKEN_CAPACITY) {
	}
	Lexer :: ~ Lexer() {
	}

using manipulator :: endLine;

	inline void
	Lexer :: open()
	{
		if (!source_.open()) {
			Error* error = new Error (Error :: INPUT);
			error->message() << source_ <<  "not found or empty." << endLine;
			throw error;
		}
	}
	inline void
	Lexer :: open (const String& fileName)
	{
		if (!source_.open (fileName.c_str())) {
			Error* error = new Error (Error :: INPUT);
			error->message() << source_ <<  "not found or empty." << endLine;
			throw error;
		}
	}
	inline void
	Lexer :: close() {
		source_.close();
	}

	inline Token :: Type
	Lexer :: scan()
	{
		tokenType_ = scaner_.scan();
		return tokenType_;
	}

using manipulator :: tab;

	template<Token :: Type type_1>
	Token :: Type
	Lexer :: scan ()
	{
		tokenType_ = scaner_.scan();
		if (tokenType_ != type_1) {
			Error* error = new Error (getLocation(), Error :: PARSER);
			error->message() << tab << "token \"" << guessToken() << "\" was scaned while" << endLine;
			error->message() << tab << "token \"" << Token :: getString (type_1) << "\" was expected." << endLine;
			throw error;
		}
		return tokenType_;
	}


	template<Token :: Type type_1, Token :: Type type_2>
	Token :: Type
	Lexer :: scan ()
	{
		tokenType_ = scaner_.scan();
		switch (tokenType_) {
		case type_1 :
		case type_2 :
			break;
		default :
			Error* error = new Error (getLocation(), Error :: PARSER);
			guessToken();
			error->message() << tab << "token \"" << guessToken() << "\" was scaned while" << endLine;
			error->message() << tab << "tokens \"" << Token :: getString (type_1) << "\" or \"";
			error->message() << Token :: getString (type_2) << "\" was expected." << endLine;
			throw error;
		}
		return tokenType_;
	}

	inline Lexer :: Comments_&
	Lexer :: comments() {
		return scaner_.comments();
	}
	inline void
	Lexer :: scanComments() {
		scaner_.scanComments();
	}

	inline Token :: Type
	Lexer :: getTokenType() const {
		return tokenType_;
	}
	inline const String&
	Lexer :: getToken() const {
		token_.copyFrom (source_.getTokenStart(), source_.getTokenStop());
		return token_;
	}
	inline const Location&
	Lexer :: getLocation() const {
		return source_.getLocation();
	}

	/****************************
	 *		Private members
	 ****************************/

	inline const String&
	Lexer :: guessToken()
	{
		if (source_.getTokenStart() == source_.getTokenStop()) {
			while (!source_.getChar().isWhitespace()) {
				++ source_;
			}
			source_.stopToken();
		}
		token_.copyFrom (source_.getTokenStart(), source_.getTokenStop());
		return token_;
	}
}
}

#endif /*MM_LEXER_LEXER_IPP_*/
