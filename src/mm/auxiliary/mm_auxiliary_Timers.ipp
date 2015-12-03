/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_auxiliary_Timers.ipp                                  */
/* Description:     processing timers class                                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AUXILIARY_TIMERS_IPP_
#define MM_AUXILIARY_TIMERS_IPP_

namespace mm {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Timers :: Timers() :
	read_ (),
	check_ (),
	translate_ (),
	write_ (),
	total_ () {
	}
	Timers :: ~ Timers() {
	}

	inline Timer&
	Timers :: read () {
		return read_;
	}
	inline Timer&
	Timers :: check () {
		return check_;
	}
	inline Timer&
	Timers :: translate () {
		return translate_;
	}
	inline Timer&
	Timers :: write () {
		return write_;
	}
	inline Timer&
	Timers :: total () {
		return total_;
	}

	inline const Timer&
	Timers :: read () const {
		return read_;
	}
	inline const Timer&
	Timers :: check () const {
		return check_;
	}
	inline const Timer&
	Timers :: translate () const {
		return translate_;
	}
	inline const Timer&
	Timers :: write () const {
		return write_;
	}
	inline const Timer&
	Timers :: total () const {
		return total_;
	}

	inline void
	Timers :: stopAll()
	{
		read_.stop();
		check_.stop();
		translate_.stop();
		write_.stop();
		total_.stop();
	}
}
}

#endif /*MM_AUXILIARY_TIMERS_IPP_*/
