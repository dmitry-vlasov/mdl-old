/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_auxiliary_Timers.hpp                                  */
/* Description:     processing timers class                                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AUXILIARY_TIMERS_HPP_
#define MM_AUXILIARY_TIMERS_HPP_

#include "interface/object/mm_interface_object_Object.hpp"
#include "auxiliary/mm_auxiliary.dpp"

namespace mm {
namespace auxiliary {

class Timers :
	public object :: Object,
	public Scalar<Timers> {
public :
	Timers();
	virtual ~ Timers();

	Timer& read ();
	Timer& check ();
	Timer& translate ();
	Timer& write ();
	Timer& total ();

	const Timer& read () const;
	const Timer& check () const;
	const Timer& translate () const;
	const Timer& write () const;
	const Timer& total () const;

	void stopAll();

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	Timer read_;
	Timer check_;
	Timer translate_;
	Timer write_;
	Timer total_;
};

}
}

#include "auxiliary/mm_auxiliary_Timers.ipp"

#endif /*MM_AUXILIARY_TIMERS_HPP_*/
