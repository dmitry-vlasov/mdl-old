/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File name:       del_auxiliary_Error.cpp                                  */
/* Description:     error exception class                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/auxiliary/del_auxiliary_Config.hpp"
#include "del/auxiliary/del_auxiliary_Error.hpp"

namespace del {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	Error :: Error (const Location& location, const Type_ type, const char* const message):
	Ancestor_ (location, message),
	type_ (type)
	{
		program_ << Config :: programName();
		switch (type_) {
		case LEXER : header_ << "lexer"; break;
		case PARSER : header_ << "parser"; break;
		case SEMANTIC : header_ << "semantic"; break;
		case INPUT : header_ << "input"; break;
		case OUTPUT : header_ << "output"; break;
		default : break;
		}
	}
	Error :: Error (const Type_ type, const char* const message):
	Ancestor_ (message),
	type_ (type)
	{
		program_ << Config :: programName();
		switch (type_) {
		case LEXER : header_ << "lexer"; break;
		case PARSER : header_ << "parser"; break;
		case SEMANTIC : header_ << "semantic"; break;
		case INPUT : header_ << "input"; break;
		case OUTPUT : header_ << "output"; break;
		default : break;
		}
	}
	Error :: ~ Error() throw() {
	}

	inline Error :: Type_
	Error :: getType() const {
		return type_;
	}

	// nstd :: Error implementation
	Error :: Message_&
	Error :: message() {
		return Ancestor_ :: message();
	}
	void
	Error :: add (const Location_& location , const char* message) {
		Ancestor_ :: add (location, message);
	}
	const char*
	Error :: what() const throw() {
		return Ancestor_ :: what();
	}
	void
	Error :: showMessage (Message_& string) const {
		Ancestor_ :: showMessage (string);
	}

	// nstd :: Object implementation
	void
	Error :: commitSuicide() {
		delete this;
	}
	Size_t
	Error :: getVolume() const {
		return Ancestor_ :: getVolume();
	}
	Size_t
	Error :: getSizeOf() const {
		return Ancestor_ :: getSizeOf();
	}
	void
	Error :: show (nstd :: String<>& string) const {
		Ancestor_ :: show (string);
	}

	/****************************
	 *		Private members
	 ****************************/

	inline
	Error :: Error (const Error& error) :
	Ancestor_ (error),
	type_ (error.type_) {
	}
}
}


