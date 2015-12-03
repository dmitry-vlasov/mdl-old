/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_lexer_Lexer.ipp                                      */
/* Description:     smm lexer class                                          */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_LEXER_LEXER_IPP_
#define SMM_LEXER_LEXER_IPP_

namespace smm {
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

	inline value :: Index
	Lexer :: scanIndex()
	{
		scan<Token :: INDEX>();
		return getToken().getIntegerValue<value :: Index>();
	}
	inline value :: Index
	Lexer :: scanLabel()
	{
		scan<Token :: LABEL>();
		return Table :: labels()->add (getToken());
	}
	value :: Index
	Lexer :: scanAssertion()
	{
		return
			Config :: noLabels() ?
			scanIndex() :
			scanLabel();
	}
	inline Token :: Type
	Lexer :: scan()
	{
		tokenType_ = scaner_.scan();
		return tokenType_;
	}

using manipulator :: endLine;
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
}
}

#endif /*SMM_LEXER_LEXER_IPP_*/
