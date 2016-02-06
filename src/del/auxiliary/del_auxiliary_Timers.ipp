/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File name:       del_auxiliary_Timers.ipp                                 */
/* Description:     class for processing timers                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace del {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Timers :: Timers() :
	read_ (),
	solve_ (),
	execute_ (),
	minimize_ (),
	normalize_ (),
	primitivize_ (),
	decompose_ (),
	assemble_ (),
	compile_ (),
	verify_ (),
	translate_ (),
	write_ (),
	total_ ()
	{
		minimize_.setShowCumulativeTime();
		normalize_.setShowCumulativeTime();
		primitivize_.setShowCumulativeTime();
		decompose_.setShowCumulativeTime();
		compile_.setShowCumulativeTime();
	}
	Timers :: ~ Timers() {
	}

	inline Timer&
	Timers :: init() {
		return init_;
	}
	inline Timer&
	Timers :: release() {
		return release_;
	}
	inline Timer&
	Timers :: solving() {
		return solving_;
	}
	inline Timer&
	Timers :: decomposing() {
		return decomposing_;
	}
	inline Timer&
	Timers :: minimizing() {
		return minimizing_;
	}
	inline bool
	Timers :: progressShowed()
	{
		if (progressShowed_) {
			progressShowed_ = false;
			return true;
		} else {
			return false;
		}
	}
	/*inline Timer&
	Timers :: refresh() {
		return refresh_;
	}*/

	inline Timer&
	Timers :: read() {
		return read_;
	}
	inline Timer&
	Timers :: solve() {
		return solve_;
	}
	inline Timer&
	Timers :: execute() {
		return execute_;
	}
	inline Timer&
	Timers :: minimize() {
		return minimize_;
	}
	inline Timer&
	Timers :: normalize() {
		return normalize_;
	}
	inline Timer&
	Timers :: primitivize() {
		return primitivize_;
	}
	inline Timer&
	Timers :: decompose() {
		return decompose_;
	}
	inline Timer&
	Timers :: assemble() {
		return assemble_;
	}
	inline Timer&
	Timers :: compile() {
		return compile_;
	}
	inline Timer&
	Timers :: verify() {
		return verify_;
	}
	inline Timer&
	Timers :: translate() {
		return translate_;
	}
	inline Timer&
	Timers :: calcDelta() {
		return calcDelta_;
	}
	inline Timer&
	Timers :: write() {
		return write_;
	}
	inline Timer&
	Timers :: total() {
		return total_;
	}

	inline const Timer&
	Timers :: read() const {
		return read_;
	}
	inline const Timer&
	Timers :: solve() const {
		return solve_;
	}
	inline const Timer&
	Timers :: execute() const {
		return execute_;
	}
	inline const Timer&
	Timers :: minimize() const {
		return minimize_;
	}
	inline const Timer&
	Timers :: normalize() const {
		return normalize_;
	}
	inline const Timer&
	Timers :: primitivize() const {
		return primitivize_;
	}
	inline const Timer&
	Timers :: decompose() const {
		return decompose_;
	}
	inline const Timer&
	Timers :: assemble() const {
		return assemble_;
	}
	inline const Timer&
	Timers :: compile() const {
		return compile_;
	}
	inline const Timer&
	Timers :: verify() const {
		return verify_;
	}
	inline const Timer&
	Timers :: translate() const {
		return translate_;
	}
	inline const Timer&
	Timers :: calcDelta() const {
		return calcDelta_;
	}
	inline const Timer&
	Timers :: write() const {
		return write_;
	}
	inline const Timer&
	Timers :: total () const {
		return total_;
	}

	inline void
	Timers :: stopAll()
	{
		init_.stop();
		read_.stop();
		solve_.stop();
		execute_.stop();
		minimize_.stop();
		normalize_.stop();
		primitivize_.stop();
		decompose_.stop();
		assemble_.stop();
		compile_.stop();
		verify_.stop();
		translate_.stop();
		calcDelta_.stop();
		write_.stop();
		release_.stop();
		total_.stop();
	}
}
}


