/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File name:       del_auxiliary_Timers.hpp                                 */
/* Description:     class for processing timers                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface_Object.hpp"
#include "del/auxiliary/del_auxiliary.dpp"

namespace del {
namespace auxiliary {

class Timers :
	public Object,
	public Scalar<Timers> {
public :
	Timers();
	virtual ~ Timers();

	static Timer& init();
	static Timer& release();
	static Timer& solving();
	static Timer& decomposing();
	static Timer& minimizing();
	//static Timer& refresh();
	static void checkOutOfTime();
	static bool progressShowed();

	bool showProgress
	(
		const value :: Integer currentCount,
		const value :: Integer totalCount,
		const char* message = "",
		const bool thorough = false
	) const;
	bool showProgress
	(
		const value :: Integer currentCount,
		const value :: Integer totalCount,
		const Timer& timer,
		const char* message = "",
		const bool thorough = false
	) const;
	static void startProgress();
	static void stopProgress();

	Timer& current();
	Timer& read();
	Timer& solve();
	Timer& execute();

	// decomposition stages
	Timer& minimize();
	Timer& normalize();
	Timer& primitivize();
	Timer& decompose();
	Timer& assemble();
	Timer& compile();

	Timer& verify();
	Timer& translate();
	Timer& calcDelta();
	Timer& write();
	Timer& total();

	const Timer& getCurrent() const;
	const Timer& read() const;
	const Timer& solve() const;
	const Timer& execute() const;

	// decomposition stages
	const Timer& minimize() const;
	const Timer& normalize() const;
	const Timer& primitivize() const;
	const Timer& decompose() const;
	const Timer& assemble() const;
	const Timer& compile() const;

	const Timer& verify() const;
	const Timer& check() const;
	const Timer& translate() const;
	const Timer& calcDelta() const;
	const Timer& write() const;
	const Timer& total() const;

	void stopAll();

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	static Timer init_;
	static Timer release_;
	static Timer solving_;
	static Timer decomposing_;
	static Timer minimizing_;
	static Timer refresh_;

	Timer read_;
	Timer solve_;
	Timer execute_;

	// decomposition stages
	Timer minimize_;
	Timer normalize_;
	Timer primitivize_;
	Timer decompose_;
	Timer assemble_;
	Timer compile_;

	Timer verify_;
	Timer translate_;
	Timer calcDelta_;
	Timer write_;
	Timer total_;

	static bool progressShowed_;
};

}
}

#include "del/auxiliary/del_auxiliary_Timers.ipp"


