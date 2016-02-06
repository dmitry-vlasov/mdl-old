/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_cut_lexer_Lexer.ipp                                   */
/* Description:     mm source file cutting lexer                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mm {
namespace cut {
namespace lexer {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Lexer :: Lexer (const String& fileName) :
	source_ (fileName),
	whitespaceScaner_ (source_),
	tokenType_ (Token :: UNKNOWN),
	token_ (INITIAL_TOKEN_CAPACITY) {
	}
	Lexer :: ~ Lexer() {
	}

	inline void
	Lexer :: open()
	{
		if (!source_.open()) {
			throw new Error (Error :: INPUT, "file not found or empty.\n");
		}
	}
	inline void
	Lexer :: close() {
		source_.close();
	}

using manipulator :: tab;
using manipulator :: endLine;
using manipulator :: space;

	template<Token :: Type type_1>
	Token :: Type
	Lexer :: scan()
	{
		tokenType_ = scanToken<type_1>();
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
	Lexer :: scan()
	{
		tokenType_ = scanToken<type_1, type_2>();
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

using manipulator :: endLine;
using manipulator :: tab;

	inline Token :: Type
	Lexer :: getTokenType() const {
		return tokenType_;
	}
	inline const String&
	Lexer :: getToken() const {
		token_.copyFrom (source_.getTokenStart(), source_.getTokenStop());
		return token_;
	}
	inline const String&
	Lexer :: guessToken (const bool unclear, const int tail)
	{
		if (source_.getTokenStart() == source_.getTokenStop() || unclear) {
			while (!source_.getChar().isWhitespace()) {
				++ source_;
			}
			for (int i = 0; i < tail; ++ i) {
				++ source_;
			}
			source_.stopToken();
		}
		token_.copyFrom (source_.getTokenStart(), source_.getTokenStop());
		return token_;
	}
	inline const Location&
	Lexer :: getLocation() const {
		return source_.getLocation();
	}

	/****************************
	 *		Public members
	 ****************************/

	template<>
	Token :: Type
	Lexer :: scanToken<Token :: CONTENT, Token :: EOF_>()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		while (true) {
			if (source_.getChar().isEOF()) {
				return finalize (Token :: EOF_);
			}
			if (divisorBegins()) {
				break;
			}
			++ source_;
		}
		return finalize (Token :: CONTENT);
	}
	template<>
	Token :: Type
	Lexer :: scanToken<Token :: HEADER>()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		while (true) {
			if (source_.getChar().isEOF()) {
				return finalize (Token :: EOF_);
			}
			if (source_.getChar().getValue() == chars :: NEW_LINE) {
				break;
			}
			++ source_;
		}
		return finalize (Token :: HEADER);
	}
	template<>
	Token :: Type
	Lexer :: scanToken<Token :: CHAPTER_END>()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case '#' :
			return finalize (consume (Token :: chapterEnd_));
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Lexer :: scanToken<Token :: SECTION_END>()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case '=' :
			return finalize (consume (Token :: sectionEnd_));
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Lexer :: scanToken
	<
		Token :: CHAPTER_BEGIN,
		Token :: SECTION_BEGIN
	>()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue (3)) {
		case '#' :
			return finalize (consume (Token :: chapterBegin_));
		case '=' :
			return finalize (consume (Token :: sectionBegin_));
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
}
}
}


