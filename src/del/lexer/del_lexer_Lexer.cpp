/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_lexer_Lexer.cpp                                      */
/* Description:     lexer class                                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/lexer/del_lexer.hpp"

namespace del {
namespace lexer {

	/****************************
	 *		Public members
	 ****************************/

using manipulator :: tab;
using manipulator :: space;
using manipulator :: endLine;

	const String&
	Lexer :: scanPath()
	{
		scan<Token :: PATH>();
		return getToken();
	}
	const String&
	Lexer :: scanString()
	{
		scan<Token :: NAME>();
		return getToken();
	}
	value :: Relation
	Lexer :: scanRelationName()
	{
		scan<Token :: NAME>();
		return Table :: relations()->add (getToken());
	}
	value :: Theory
	Lexer :: scanTheoryName (const bool inDeclaration)
	{
		scan<Token :: NAME>();
		const String& name = getToken();
		if (inDeclaration) {
			if (Table :: theories()->contains (name)) {
				Error* error = new Error (source_.getLocation(), Error :: PARSER);
				error->message() << tab << "theory \"" << name << "\" is already declared" << endLine;
				throw error;
			}
			return Table :: theories()->add (name);
		} else {
			const value :: Theory
				theory = Table :: theories()->add (name);
			if (Math :: theories()->get (theory) == NULL) {
				Error* error = new Error (source_.getLocation(), Error :: PARSER);
				error->message() << tab << "theory \"" << name << "\" is not declared" << endLine;
				throw error;
			}
			return theory;
		}
	}
	value :: Variable
	Lexer :: scanVariableName()
	{
		scan<Token :: NAME>();
		return Table :: variables()->add (getToken());
	}
	value :: Signature
	Lexer :: scanSignatureName (const bool inDeclaration)
	{
		scan<Token :: NAME>();
		const String& name = getToken();
		if (inDeclaration) {
			if (Table :: signatures()->contains (name)) {
				Error* error = new Error (source_.getLocation(), Error :: PARSER);
				error->message() << tab << "signature \"" << name << "\" is already declared" << endLine;
				throw error;
			}
			return Table :: signatures()->add (name);
		} else {
			const value :: Signature
				signature = Table :: signatures()->add (name);
			if (Math :: signatures()->get (signature) == NULL) {
				Error* error = new Error (source_.getLocation(), Error :: PARSER);
				error->message() << tab << "signature \"" << name << "\" is not declared" << endLine;
				throw error;
			}
			return signature;
		}
	}

	// object :: Object implementation
	void
	Lexer :: commitSuicide() {
		delete this;
	}
	Size_t
	Lexer :: getVolume() const
	{
		Size_t volume = 0;
		volume += source_.getVolume();
		volume += scaner_.getVolume();
		volume += token_.getVolume();
		return volume;
	}
	Size_t
	Lexer :: getSizeOf() const {
		return sizeof (Lexer);
	}
	void
	Lexer :: show (String&) const {
	}

	/************************************
	 *		Static private attributes
	 ************************************/
}
}


