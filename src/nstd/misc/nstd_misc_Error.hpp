/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_misc_Error.hpp                                      */
/* Description:     general class for error exceptions                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MISC_ERROR_HPP_
#define NSTD_MISC_ERROR_HPP_

#include "lexer/nstd_lexer_Location.hpp"

namespace nstd {
namespace misc {

template<class A, class S = lexer :: Source<> >
class Error :
	public std :: exception,
	public Object {
public :
	typedef A Allocator_;
	typedef S Source_;
	typedef String<Allocator_> Message_;
	typedef lexer :: Location<Source_> Location_;

	Error (const char* = "");
	Error (const Location_&, const char* = "");
	virtual ~Error() throw();

	Message_& message();
	void add (const Location_&, const char* = "");
	const char* what() const throw();
	void showMessage (Message_&) const;

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String<>&) const;

protected :
	Message_ program_;
	Message_ header_;

	Error (const Error&);

private :
	typedef
		container :: Vector
		<
			const Location_,
			container :: storage :: ByPointer,
			Allocator_
		>
		Locations_;
	typedef
		container :: Vector
		<
			Message_,
			container :: storage :: ByPointer,
			Allocator_
		>
		Messages_;

	Locations_ locations_;
	Messages_ messages_;

	enum {
		INITIAL_MESSAGE_CAPACITY = 1024 * 4,
		INITIAL_HEADER_CAPACITY = 256,
		INITIAL_LOCATIONS_CAPACITY = 16,
		INITIAL_MESSAGES_CAPACITY = 16
	};
};

}
}

#endif /*NSTD_MISC_ERROR_HPP_*/
