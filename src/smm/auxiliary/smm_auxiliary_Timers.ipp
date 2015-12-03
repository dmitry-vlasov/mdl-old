/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_auxiliary_Timers.ipp                                 */
/* Description:     processing timers class                                  */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_AUXILIARY_TIMERS_IPP_
#define SMM_AUXILIARY_TIMERS_IPP_

namespace smm {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Timers :: Timers() :
	read_ (),
	verify_ (),
	total_ () {
	}
	Timers :: ~ Timers() {
	}

	inline Timer&
	Timers :: read () {
		return read_;
	}
	inline Timer&
	Timers :: verify () {
		return verify_;
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
	Timers :: verify () const {
		return verify_;
	}
	inline const Timer&
	Timers :: total () const {
		return total_;
	}

	inline void
	Timers :: stopAll()
	{
		read_.stop();
		verify_.stop();
		total_.stop();
	}
}
}

#endif /*SMM_AUXILIARY_TIMERS_IPP_*/
