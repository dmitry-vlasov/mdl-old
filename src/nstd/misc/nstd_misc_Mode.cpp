/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_misc_Mode.cpp                                       */
/* Description:     class for the show modes                                 */
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

	inline
	Mode :: Mode () :
	bits_() {
	}
	template<class A>
	inline
	Mode :: Mode (const String<A>&) :
	bits_ (String<A> :: getMode()) {
	}
	inline
	Mode :: Mode (const Mode& mode) :
	bits_ (mode.bits_) {
	}

	inline bool
	Mode :: isPlain() const {
		return (bits_.get() == 0);
	}
	inline bool
	Mode :: getValue (const char index) const {
		return bits_.getValue (index);
	}
	inline void
	Mode :: setValue (const char index, const bool value) {
		bits_.setValue (index, value);
	}

	inline void
	Mode :: operator = (const Mode& mode) {
		bits_ = mode.bits_;
	}
	inline bool
	Mode :: operator == (const Mode& mode) const {
		return (bits_ == mode.bits_);
	}
	inline bool
	Mode :: operator != (const Mode& mode) const {
		return !(operator == (mode));
	}

	inline Size_t
	Mode :: getVolume() const {
		return bits_.getVolume();
	}
	inline Size_t
	Mode :: getSizeOf() const {
		return sizeof (Mode);
	}
	template<class A>
	inline void
	Mode :: show (String<A>& string) const {
		bits_.show (string);
	}

	/****************************
	 *		Overloaded operators
	 ****************************/

	template<class A>
	inline String<A>&
	operator << (String<A>& string, const Mode& mode) {
		return string << manipulator :: mode << mode.bits_.get();
	}
	inline Mode&
	operator << (Mode& mode, const char m)
	{
		mode.setValue (m);
		return mode;
	}
	template<class A>
	inline Mode&
	operator << (Mode& mode, const String<A>& string)
	{
		const Size_t m = String<A> :: getMode();
		mode.bits_.set (m);
		return mode;
	}
}
}


