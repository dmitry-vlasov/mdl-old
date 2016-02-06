/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_lexer_Lexer.ipp                                      */
/* Description:     lexer class                                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/auxiliary/del_auxiliary.hpp"

namespace del {
namespace lexer {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Lexer :: Lexer (const String& fileName, const bool isTop) :
	source_ (fileName, isTop),
	scaner_ (source_),
	tokenType_ (Token :: UNKNOWN),
	token_ (INITIAL_TOKEN_CAPACITY) {
	}
	Lexer :: ~ Lexer() {
	}

	inline bool
	Lexer :: isTop() const {
		return source_.isTop();
	}

using manipulator :: endLine;

	inline void
	Lexer :: open()
	{
		if (!source_.open()) {
			Error* error = new Error (source_.getLocation(), Error :: INPUT);
			error->message() << "source " << source_ <<  "not found." << endLine;
			throw error;
		}
		if (source_.isEmpty()) {
			Error* error = new Error (source_.getLocation(), Error :: INPUT);
			error->message() << "source " << source_ <<  "is empty." << endLine;
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

using manipulator :: tab;
using manipulator :: space;
using manipulator :: endLine;

	inline Lexer :: Comments_&
	Lexer :: comments() {
		return scaner_.comments();
	}
	inline void
	Lexer :: scanComments() {
		scaner_.scanComments();
	}
	inline void
	Lexer :: scanWhitespace() {
		scaner_.scanWhitespace();
	}

	inline Token :: Type
	Lexer :: expectToken (const Token :: Type type)
	{
		if (tokenType_ == type) {
			return type;
		}
		Error* error = new Error (source_.getLocation(), Error :: PARSER);
		error->message() << tab << "token \"" << guessToken() << "\" was scaned ";
		error->message() << "at " << source_.getLocation() << "while" << endLine;
		error->message() << Token :: getString (type) << " token is expected." << endLine;
		throw error;
	}
	inline Token :: Type
	Lexer :: expectTokens
	(
		const Token :: Type type_1,
		const Token :: Type type_2
	)
	{
		if (tokenType_ == type_1) {
			return type_1;
		}
		if (tokenType_ == type_2) {
			return type_2;
		}
		Error* error = new Error (source_.getLocation(), Error :: PARSER);
		error->message() << tab << "token \"" << guessToken() << "\" was scaned ";
		error->message() << "at " << source_.getLocation() << "while" << endLine;
		error->message() << Token :: getString (type_1) << " or ";
		error->message() << Token :: getString (type_2) << " tokens are expected." << endLine;
		throw error;
	}

	inline Token :: Type
	Lexer :: getTokenType() const {
		return tokenType_;
	}
	inline const String&
	Lexer :: getToken() const
	{
		token_.copyFrom (source_.getTokenStart(), source_.getTokenStop());
		return token_;
	}
	inline const Location&
	Lexer :: getLocation() const {
		return source_.getLocation();
	}

	template
	<
		Token :: Type type_1
	>
	Token :: Type Lexer :: scan ()
	{
		tokenType_ = scaner_.scan
		<
			type_1
		>();
		if (tokenType_ != type_1) {
			Error* error = new Error (source_.getLocation(), Error :: PARSER);
			error->message() << tab << "token \"" << guessToken() << "\" was scaned ";
			error->message() << "at " << source_.getLocation() << "while" << endLine;
			error->message() << tab << "token \"" << Token :: getString (type_1) << "\" was expected." << endLine;
			throw error;
		}
		return getTokenType();
	}


	template
	<
		Token :: Type type_1,
		Token :: Type type_2
	>
	Token :: Type Lexer :: scan ()
	{
		tokenType_ = scaner_.scan
		<
			type_1,
			type_2
		>();
		switch (tokenType_) {
		case type_1 :
		case type_2 :
			break;
		default :
			Error* error = new Error (source_.getLocation(), Error :: PARSER);
			error->message() << tab << "token \"" << guessToken() << "\" was scaned ";
			error->message() << "at " << source_.getLocation() << "while" << endLine;
			error->message() << tab  << "tokens \"" << Token :: getString (type_1) << "\" or \"";
			error->message() << Token :: getString (type_2) << "\" was expected." << endLine;
			throw error;
		}
		return getTokenType();
	}

	template
	<
		Token :: Type type_1,
		Token :: Type type_2,
		Token :: Type type_3
	>
	Token :: Type Lexer :: scan ()
	{
		tokenType_ = scaner_.scan
		<
			type_1,
			type_2,
			type_3
		>();
		switch (tokenType_) {
		case type_1 :
		case type_2 :
		case type_3 :
			break;
		default :
			Error* error = new Error (source_.getLocation(), Error :: PARSER);
			error->message() << tab << "token \"" << guessToken() << "\" was scaned ";
			error->message() << "at " << source_.getLocation() << "while" << endLine;
			error->message() << tab << "tokens \"" << Token :: getString (type_1) << "\", \"";
			error->message() << Token :: getString (type_2) << "\" or \"";
			error->message() << Token :: getString (type_3) << "\" was expected." << endLine;
			throw error;
		}
		return getTokenType();
	}

	template
	<
		Token :: Type type_1,
		Token :: Type type_2,
		Token :: Type type_3,
		Token :: Type type_4
	>
	Token :: Type Lexer :: scan ()
	{
		tokenType_ = scaner_.scan
		<
			type_1,
			type_2,
			type_3,
			type_4
		>();
		switch (tokenType_) {
		case type_1 :
		case type_2 :
		case type_3 :
		case type_4 :
			break;
		default :
			Error* error = new Error (source_.getLocation(), Error :: PARSER);
			error->message() << tab << "token \"" << guessToken() << "\" was scaned ";
			error->message() << "at " << source_.getLocation() << "while" << endLine;
			error->message() << tab << "tokens \"" << Token :: getString (type_1) << "\", \"";
			error->message() << Token :: getString (type_2) << "\", \"";
			error->message() << Token :: getString (type_3) << "\" or \"";
			error->message() << Token :: getString (type_4) << "\" was expected." << endLine;
			throw error;
		}
		return getTokenType();
	}

	template
	<
		Token :: Type type_1,
		Token :: Type type_2,
		Token :: Type type_3,
		Token :: Type type_4,
		Token :: Type type_5
	>
	Token :: Type Lexer :: scan ()
	{
		tokenType_ = scaner_.scan
		<
			type_1,
			type_2,
			type_3,
			type_4,
			type_5
		>();
		switch (tokenType_) {
		case type_1 :
		case type_2 :
		case type_3 :
		case type_4 :
		case type_5 :
			break;
		default :
			Error* error = new Error (source_.getLocation(), Error :: PARSER);
			error->message() << tab << "token \"" << guessToken() << "\" was scaned ";
			error->message() << "at " << source_.getLocation() << "while" << endLine;
			error->message() << tab << "tokens \"" << Token :: getString (type_1) << "\", \"";
			error->message() << Token :: getString (type_2) << "\", \"";
			error->message() << Token :: getString (type_3) << "\", \"";
			error->message() << Token :: getString (type_4) << "\" or \"";
			error->message() << Token :: getString (type_5) << "\" was expected." << endLine;
			throw error;
		}
		return getTokenType();
	}

	template
	<
		Token :: Type type_1,
		Token :: Type type_2,
		Token :: Type type_3,
		Token :: Type type_4,
		Token :: Type type_5,
		Token :: Type type_6
	>
	Token :: Type Lexer :: scan ()
	{
		tokenType_ = scaner_.scan
		<
			type_1,
			type_2,
			type_3,
			type_4,
			type_5,
			type_6
		>();
		switch (tokenType_) {
		case type_1 :
		case type_2 :
		case type_3 :
		case type_4 :
		case type_5 :
		case type_6 :
			break;
		default :
			Error* error = new Error (source_.getLocation(), Error :: PARSER);
			error->message() << tab << "token \"" << guessToken() << "\" was scaned ";
			error->message() << "at " << source_.getLocation() << "while" << endLine;
			error->message() << tab << "tokens \"" << Token :: getString (type_1) << "\", \"";
			error->message() << Token :: getString (type_2) << "\", \"";
			error->message() << Token :: getString (type_3) << "\", \"";
			error->message() << Token :: getString (type_4) << "\", \"";
			error->message() << Token :: getString (type_5) << "\" or \"";
			error->message() << Token :: getString (type_6) << "\" was expected." << endLine;
			throw error;
		}
		return getTokenType();
	}

	template
	<
		Token :: Type type_1,
		Token :: Type type_2,
		Token :: Type type_3,
		Token :: Type type_4,
		Token :: Type type_5,
		Token :: Type type_6,
		Token :: Type type_7
	>
	Token :: Type Lexer :: scan ()
	{
		tokenType_ = scaner_.scan
		<
			type_1,
			type_2,
			type_3,
			type_4,
			type_5,
			type_6,
			type_7
		>();
		switch (tokenType_) {
		case type_1 :
		case type_2 :
		case type_3 :
		case type_4 :
		case type_5 :
		case type_6 :
		case type_7 :
			break;
		default :
			Error* error = new Error (source_.getLocation(), Error :: PARSER);
			error->message() << tab << "token \"" << guessToken() << "\" was scaned ";
			error->message() << "at " << source_.getLocation() << "while" << endLine;
			error->message() << tab << "tokens \"" << Token :: getString (type_1) << "\", \"";
			error->message() << Token :: getString (type_2) << "\", \"";
			error->message() << Token :: getString (type_3) << "\", \"";
			error->message() << Token :: getString (type_4) << "\", " << endLine << tab << "\"";
			error->message() << Token :: getString (type_5) << "\", \"";
			error->message() << Token :: getString (type_6) << "\" or \"";
			error->message() << Token :: getString (type_7) << "\" was expected." << endLine;
			throw error;
		}
		return getTokenType();
	}

	template
	<
		Token :: Type type_1,
		Token :: Type type_2,
		Token :: Type type_3,
		Token :: Type type_4,
		Token :: Type type_5,
		Token :: Type type_6,
		Token :: Type type_7,
		Token :: Type type_8
	>
	Token :: Type Lexer :: scan ()
	{
		tokenType_ = scaner_.scan
		<
			type_1,
			type_2,
			type_3,
			type_4,
			type_5,
			type_6,
			type_7,
			type_8
		>();
		switch (tokenType_) {
		case type_1 :
		case type_2 :
		case type_3 :
		case type_4 :
		case type_5 :
		case type_6 :
		case type_7 :
		case type_8 :
			break;
		default :
			Error* error = new Error (source_.getLocation(), Error :: PARSER);
			error->message() << tab << "token \"" << guessToken() << "\" was scaned ";
			error->message() << "at " << source_.getLocation() << "while" << endLine;
			error->message() << tab << "tokens \"" << Token :: getString (type_1) << "\", \"";
			error->message() << Token :: getString (type_2) << "\", \"";
			error->message() << Token :: getString (type_3) << "\", \"";
			error->message() << Token :: getString (type_4) << "\", " << endLine << tab << "\"";
			error->message() << Token :: getString (type_5) << "\", \"";
			error->message() << Token :: getString (type_6) << "\", \"";
			error->message() << Token :: getString (type_7) << "\" or \"";
			error->message() << Token :: getString (type_8) << "\" was expected." << endLine;
			throw error;
		}
		return getTokenType();
	}

	template
	<
		Token :: Type type_1,
		Token :: Type type_2,
		Token :: Type type_3,
		Token :: Type type_4,
		Token :: Type type_5,
		Token :: Type type_6,
		Token :: Type type_7,
		Token :: Type type_8,
		Token :: Type type_9
	>
	Token :: Type Lexer :: scan ()
	{
		tokenType_ = scaner_.scan
		<
			type_1,
			type_2,
			type_3,
			type_4,
			type_5,
			type_6,
			type_7,
			type_8,
			type_9
		>();
		switch (tokenType_) {
		case type_1 :
		case type_2 :
		case type_3 :
		case type_4 :
		case type_5 :
		case type_6 :
		case type_7 :
		case type_8 :
		case type_9 :
			break;
		default :
			Error* error = new Error (source_.getLocation(), Error :: PARSER);
			error->message() << tab << "token \"" << guessToken() << "\" was scaned ";
			error->message() << "at " << source_.getLocation() << "while" << endLine;
			error->message() << tab << "tokens \"" << Token :: getString (type_1) << "\", \"";
			error->message() << Token :: getString (type_2) << "\", \"";
			error->message() << Token :: getString (type_3) << "\", \"";
			error->message() << Token :: getString (type_4) << "\", \"";
			error->message() << Token :: getString (type_5) << "\", " << endLine << tab << "\"";
			error->message() << Token :: getString (type_6) << "\", \"";
			error->message() << Token :: getString (type_7) << "\", \"";
			error->message() << Token :: getString (type_8) << "\" or \"";
			error->message() << Token :: getString (type_9) << "\" was expected." << endLine;
			throw error;
		}
		return getTokenType();
	}

	template
	<
		Token :: Type type_1,
		Token :: Type type_2,
		Token :: Type type_3,
		Token :: Type type_4,
		Token :: Type type_5,
		Token :: Type type_6,
		Token :: Type type_7,
		Token :: Type type_8,
		Token :: Type type_9,
		Token :: Type type_10
	>
	Token :: Type Lexer :: scan ()
	{
		tokenType_ = scaner_.scan
		<
			type_1,
			type_2,
			type_3,
			type_4,
			type_5,
			type_6,
			type_7,
			type_8,
			type_9,
			type_10
		>();
		switch (tokenType_) {
		case type_1 :
		case type_2 :
		case type_3 :
		case type_4 :
		case type_5 :
		case type_6 :
		case type_7 :
		case type_8 :
		case type_9 :
		case type_10 :
			break;
		default :
			Error* error = new Error (source_.getLocation(), Error :: PARSER);
			error->message() << tab << "token \"" << guessToken() << "\" was scaned ";
			error->message() << "at " << source_.getLocation() << "while" << endLine;
			error->message() << tab << "tokens \"" << Token :: getString (type_1) << "\", \"";
			error->message() << Token :: getString (type_2) << "\", \"";
			error->message() << Token :: getString (type_3) << "\", \"";
			error->message() << Token :: getString (type_4) << "\", \"";
			error->message() << Token :: getString (type_5) << "\", " << endLine << tab << "\"";
			error->message() << Token :: getString (type_6) << "\", \"";
			error->message() << Token :: getString (type_7) << "\", \"";
			error->message() << Token :: getString (type_8) << "\", \"";
			error->message() << Token :: getString (type_9) << "\" or \"";
			error->message() << Token :: getString (type_10) << "\" was expected." << endLine;
			throw error;
		}
		return getTokenType();
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


