/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_auxiliary_Timers.hpp                                 */
/* Description:     processing timers class                                  */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "smm/interface/object/smm_interface_object_Object.hpp"
#include "smm/auxiliary/smm_auxiliary.dpp"

namespace smm {
namespace auxiliary {

class Timers : public object :: Object, public Scalar<Timers> {
public :
	Timers();
	virtual ~ Timers();

	Timer& read ();
	Timer& verify ();
	Timer& total ();

	const Timer& read () const;
	const Timer& verify () const;
	const Timer& total () const;

	void stopAll();

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	Timer read_;
	Timer verify_;
	Timer total_;
};

}
}

#include "smm/auxiliary/smm_auxiliary_Timers.ipp"


