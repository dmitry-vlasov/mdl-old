/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_Timers.hpp                                 */
/* Description:     class for processing timers                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/object/mdl_interface_object_Object.hpp"
#include "mdl/auxiliary/mdl_auxiliary.dpp"

namespace mdl {
namespace auxiliary {

class Timers :
	public object :: Object,
	public Scalar<Timers> {
public :
	Timers();
	virtual ~ Timers();

	static Timer& init();
	static Timer& release();
	static Timer& misc();

	Timer& read();
	Timer& build();
	Timer& check();
	Timer& compress();
	Timer& reprove();
	Timer& learn();
	Timer& tune();
	Timer& benchmark();
	Timer& prove();
	Timer& translate();
	Timer& write();
	Timer& total();

	Timer& buildingNodes();
	Timer& buildingEvidences();
	Timer& buildingProofs();

	const Timer& read() const;
	const Timer& build() const;
	const Timer& check() const;
	const Timer& compress() const;
	const Timer& reprove() const;
	const Timer& learn() const;
	const Timer& tune() const;
	const Timer& benchmark() const;
	const Timer& prove() const;
	const Timer& translate() const;
	const Timer& write() const;
	const Timer& total() const;

	const Timer& buildingNodes() const;
	const Timer& buildingEvidences() const;
	const Timer& buildingProofs() const;

	void stopAll();
	void clear();

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	static Timer init_;
	static Timer release_;
	static Timer misc_;

	Timer read_;
	Timer build_;
	Timer check_;
	Timer compress_;
	Timer reprove_;
	Timer learn_;
	Timer tune_;
	Timer benchmark_;
	Timer prove_;
	Timer translate_;
	Timer write_;
	Timer total_;

	// prover timers
	Timer buildingNodes_;
	Timer buildingEvidences_;
	Timer buildingProofs_;
};

}
}


