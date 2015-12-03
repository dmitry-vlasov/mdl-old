/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_Exception.cpp                                 */
/* Description:     general prover exception class                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_EXCEPTION_CPP_
#define MDL_PROVER_EXCEPTION_CPP_

namespace mdl {
namespace prover {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Exception :: Exception (const char* message, const char* comments) :
	message_ (message),
	comments_ (comments) {
	}
	inline const char*
	Exception :: what() const throw() {
		return message_;
	}
	inline const char*
	Exception :: getMessage() const throw() {
		return message_;
	}
	inline const char*
	Exception :: getComments() const throw() {
		return comments_;
	}

	/*******************************
	 *		Overloaded operator
	 *******************************/

	std :: ostream&
	operator << (std :: ostream& stream, const Exception& exception)
	{
		stream << exception.getMessage();
		if (exception.getComments() != NULL) {
			stream << " : " << exception.getComments() << std :: endl;
		} else {
			stream << std :: endl;
		}
		return stream;
	}
}
}

#endif /*MDL_PROVER_EXCEPTION_CPP_*/
