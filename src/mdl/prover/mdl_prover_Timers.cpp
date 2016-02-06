/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_Timers.cpp                                    */
/* Description:     timers for proving process                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace prover {

	/****************************
	 *		Public members
	 ****************************/


	inline
	Timers :: Timers () :
	isOn_ (true),
	limitFirst_ (Config :: getTimeLimit()),
	limitSecond_ (Config :: getTimeLimit()),
	prove_ (true),
	refresh_(),
	growUp_(),
	growDown_(),
	recounted_ (false),
	refreshed_ (false)
	{
		growUp_.setShowCumulativeTime();
		growDown_.setShowCumulativeTime();
		refresh_.start();
	}
	Timers :: ~ Timers() {
	}


	bool
	Timers :: refresh()
	{
		if (!isOn_) {
			return false;
		}
		if (refresh_.getSeconds() > Config :: getRefreshTime()) {
			refresh_.start();
			refreshed_ = true;
			return true;
		} else {
			return false;
		}
	}
	inline bool
	Timers :: timeIsOver() const
	{
		prove_.mark();
		const Time timePassed = prove_.getSeconds();
		return (timePassed > limitSecond_);
	}

	void
	Timers :: start()
	{
		prove_.start();
		refresh_.start();
		limitSecond_ = limitFirst_;
		recounted_ = false;
		refreshed_ = false;
	}
	inline void
	Timers :: mark() {
		prove_.mark();
	}
	inline void
	Timers :: stop()
	{
		prove_.stop();
		refresh_.stop();
		limitSecond_ = limitFirst_;
	}
	void
	Timers :: recount()
	{
		if (recounted_) {
			return;
		}
		recounted_ = true;

		prove_.mark();
		const Time t_0 = prove_.getSeconds();

		if (Config :: searchMode() == Config :: MINIMAL_SEARCH) {
			limitSecond_ = t_0;
		}
		if (Config :: searchMode() == Config :: OPTIMAL_SEARCH) {
			const Time T_0 = limitFirst_;
			const Time t_1 = t_0 * (1 - t_0 / T_0);
			limitSecond_ = t_0 + t_1;
		}
	}

	inline void
	Timers :: switchOff() {
		isOn_ = false;
	}
	inline void
	Timers :: switchOn() {
		isOn_ = true;
	}

	void
	Timers :: setLimit (const Time timeLimit)
	{
		limitFirst_ = timeLimit;
		limitSecond_ = timeLimit;
	}

	inline Time
	Timers :: limit() const {
		return limitSecond_;
	}

	inline Timer&
	Timers :: growUp() {
		return growUp_;
	}
	inline Timer&
	Timers :: growDown() {
		return growDown_;
	}

	inline const Timer&
	Timers :: prove() const {
		return prove_;
	}
	inline const Timer&
	Timers :: refresh() const {
		return refresh_;
	}
	inline const Timer&
	Timers :: growUp() const {
		return growUp_;
	}
	inline const Timer&
	Timers :: growDown() const {
		return growDown_;
	}

	inline bool
	Timers :: wasRefreshed() const
	{
		if (!isOn_) {
			return false;
		} else {
			return refreshed_;
		}
	}

using manipulator :: endLine;
using manipulator :: iterate;
using manipulator :: mode;

	// object :: Object implementation
	void
	Timers :: commitSuicide() {
		delete this;
	}
	Size_t
	Timers :: getVolume() const
	{
		Size_t volume = 0;
		volume += prove_.getVolume();
		volume += refresh_.getVolume();
		volume += growUp_.getVolume();
		volume += growDown_.getVolume();
		return volume;
	}
	Size_t
	Timers :: getSizeOf() const {
		return sizeof (Timers);
	}
	void
	Timers :: show (String& string) const
	{
		const Mode mode (string);
		//string << "running: ";
		string << prove_;
		if (mode.getValue (Mode :: END_LINE)) {
			string << endLine;
		} else {
			string << ", ";
		}
	}

	/********************************
	 *		Overloaded operators
	 ********************************/

	inline String&
	operator << (String& string, const Timers& timers)
	{
		timers.show (string);
		return string;
	}
}
}


