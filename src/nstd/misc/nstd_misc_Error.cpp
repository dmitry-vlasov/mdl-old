/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_misc_Error.cpp                                      */
/* Description:     general class for error exceptions                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {
namespace misc {

	/****************************
	 *		Public members
	 ****************************/

	template<class A, class S>
	inline
	Error<A, S> :: Error (const char* message) :
	program_ (INITIAL_HEADER_CAPACITY),
	header_ (INITIAL_HEADER_CAPACITY),
	locations_ (INITIAL_LOCATIONS_CAPACITY),
	messages_ (INITIAL_MESSAGES_CAPACITY) {
		add (Location_(), message);
	}
	template<class A, class S>
	inline
	Error<A, S> :: Error (const Location_& location, const char* message) :
	program_ (INITIAL_HEADER_CAPACITY),
	header_ (INITIAL_HEADER_CAPACITY),
	locations_ (INITIAL_LOCATIONS_CAPACITY),
	messages_ (INITIAL_MESSAGES_CAPACITY) {
		add (location, message);
	}
	template<class A, class S>
	Error<A, S> :: ~Error() throw() {
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;

	template<class A, class S>
	inline typename Error<A, S> :: Message_&
	Error<A, S> :: message () {
		return *(messages_.getLastValue());
	}
	template<class A, class S>
	void
	Error<A, S> :: add (const Location_& location, const char* message)
	{
		locations_.add (new Location_ (location));
		messages_.add  (new Message_ (message));
	}
	template<class A, class S>
	inline const char*
	Error<A, S> :: what() const throw()
	{
		Message_ message (INITIAL_MESSAGE_CAPACITY);
		showMessage (message);
		return message.c_str();
	}
	template<class A, class S>
	void
	Error<A, S> :: showMessage (Message_& message) const
	{
		message << header_ << space;
		message << program_ << space;
		message << "error" << endLine;

		for (typename Locations_ :: Index_ i = 0; i < locations_.getSize(); ++i ) {
			if (!messages_ [i]->isEmpty()) {
				message << *messages_ [i] << endLine;
			}
			message << *locations_ [i] << endLine;
		}
	}

	// nstd :: Object implementation
	template<class A, class S>
	void
	Error<A, S> :: commitSuicide() {
		delete this;
	}
	template<class A, class S>
	Size_t
	Error<A, S> :: getVolume() const
	{
		Size_t volume = 0;
		volume += program_.getVolume();
		volume += header_.getVolume();
		volume += locations_.getVolume();
		volume += messages_.getVolume();
		return  volume;
	}
	template<class A, class S>
	Size_t
	Error<A, S> :: getSizeOf() const {
		return sizeof (Error);
	}
	template<class A, class S>
	void
	Error<A, S> :: show (String<>& string) const
	{
		Message_ message (INITIAL_MESSAGE_CAPACITY);
		showMessage (message);
		string << message;
	}

	/****************************
	 *		Protected members
	 ****************************/

	template<class A, class S>
	inline
	Error<A, S> :: Error (const Error& error) :
	program_ (error.program_),
	header_ (error.header_),
	locations_ (error.locations_),
	messages_ (error.messages_) {
	}
}
}


