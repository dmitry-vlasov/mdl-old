/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_Exception.hpp                                 */
/* Description:     general prover exception class                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_EXCEPTION_HPP_
#define MDL_PROVER_EXCEPTION_HPP_

#include <ostream>
#include <exception>

namespace mdl {
namespace prover {

class Exception : public std :: exception {
public :
	Exception (const char* = "prover exception", const char* = NULL);

	const char* what() const throw();
	const char* getMessage() const throw();
	const char* getComments() const throw();

private :
	const char* message_;
	const char* comments_;
};
	std :: ostream&
	operator << (std :: ostream&, const Exception&);
}
}

#endif /*MDL_PROVER_EXCEPTION_HPP_*/
