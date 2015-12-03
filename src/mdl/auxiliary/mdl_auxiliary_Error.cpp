/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_Error.cpp                                  */
/* Description:     error exception class                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_ERROR_CPP_
#define MDL_AUXILIARY_ERROR_CPP_

#include "mdl/auxiliary/mdl_auxiliary_Error.hpp"

namespace mdl {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	Error :: Error (const Location& location, const Type_ type, const char* const message):
	Ancestor_ (location, message),
	type_ (type),
	next_ (NULL)
	{
		program_ << Config :: programName();
		switch (type_) {
		case LEXER       : header_ << "lexer";       break;
		case PARSER      : header_ << "parser";      break;
		case SEMANTIC    : header_ << "semantic";    break;
		case UNIFICATION : header_ << "unification"; break;
		case DISJOINTEDS : header_ << "disjointeds"; break;
		case TRANSLATOR  : header_ << "translation"; break;
		case PROVER      : header_ << "prover";      break;
		case INPUT       : header_ << "input";       break;
		case OUTPUT      : header_ << "output";      break;
		default : break;
		}
	}
	Error :: Error (const Type_ type, const char* const message):
	Ancestor_ (message),
	type_ (type),
	next_ (NULL)
	{
 		program_ << Config :: programName();
		switch (type_) {
		case LEXER       : header_ << "lexer";       break;
		case PARSER      : header_ << "parser";      break;
		case SEMANTIC    : header_ << "semantic";    break;
		case UNIFICATION : header_ << "unification"; break;
		case DISJOINTEDS : header_ << "disjointeds"; break;
		case TRANSLATOR  : header_ << "translation"; break;
		case PROVER      : header_ << "prover";      break;
		case INPUT       : header_ << "input";       break;
		case OUTPUT      : header_ << "output";      break;
		default : break;
		}
	}
	Error :: ~ Error() throw() {
		deleteAggregateObject (next_);
	}

	inline Error :: Type_
	Error :: getType() const {
		return type_;
	}

	// nstd :: Error implementation
	inline Error :: Message_&
	Error :: message() {
		return Ancestor_ :: message();
	}
	inline void
	Error :: add (const Location_& location , const char* message) {
		Ancestor_ :: add (location, message);
	}
	inline const char*
	Error :: what() const throw() {
		return Ancestor_ :: what();
	}
	void
	Error :: showMessage (Message_& string) const
	{
		Ancestor_ :: showMessage (string);
		if (next_ != NULL) {
			next_->showMessage (string);
		}
	}
	inline void
	Error :: setNext (Error* next) {
		next_ = next;
	}

	// nstd :: Object implementation
	void
	Error :: commitSuicide() {
		delete this;
	}
	Size_t
	Error :: getVolume() const
	{
		Size_t volume = 0;
		volume += Ancestor_ :: getVolume();
		volume += getAggregateVolume (next_);
		return volume;
	}
	Size_t
	Error :: getSizeOf() const {
		return Ancestor_ :: getSizeOf();
	}
	void
	Error :: show (nstd :: String<>& string) const
	{
		Ancestor_ :: show (string);
		if (next_ != NULL) {
			next_->showMessage (string);
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	inline
	Error :: Error (const Error& error) :
	Ancestor_ (error),
	type_ (error.type_),
	next_ (error.next_) {
	}
}
}

#endif /* MDL_AUXILIARY_ERROR_CPP_ */
