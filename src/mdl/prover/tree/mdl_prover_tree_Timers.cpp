/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_tree_Timers.cpp                               */
/* Description:     timers for proving process                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_TREE_TIMERS_CPP_
#define MDL_PROVER_TREE_TIMERS_CPP_

namespace mdl {
namespace prover {
namespace tree {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Timers<A> :: Timers () :
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
	template<class A>
	Timers<A> :: ~ Timers() {
	}

	template<class A>
	bool
	Timers<A> :: refresh()
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
	template<class A>
	inline bool
	Timers<A> :: timeIsOver() const
	{
		prove_.mark();
		const Time timePassed = prove_.getSeconds();
		return (timePassed > limitSecond_);
	}

	template<class A>
	void
	Timers<A> :: start()
	{
		prove_.start();
		refresh_.start();
		limitSecond_ = limitFirst_;
		recounted_ = false;
		refreshed_ = false;
	}
	template<class A>
	inline void
	Timers<A> :: mark() {
		prove_.mark();
	}
	template<class A>
	inline void
	Timers<A> :: stop()
	{
		prove_.stop();
		refresh_.stop();
		limitSecond_ = limitFirst_;
	}
	template<class A>
	void
	Timers<A> :: recount()
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

	template<class A>
	inline void
	Timers<A> :: switchOff() {
		isOn_ = false;
	}
	template<class A>
	inline void
	Timers<A> :: switchOn() {
		isOn_ = true;
	}

	template<class A>
	void
	Timers<A> :: setLimit (const Time timeLimit)
	{
		limitFirst_ = timeLimit;
		limitSecond_ = timeLimit;
	}

	template<class A>
	inline Time
	Timers<A> :: limit() const {
		return limitSecond_;
	}

	template<class A>
	inline Timer&
	Timers<A> :: growUp() {
		return growUp_;
	}
	template<class A>
	inline Timer&
	Timers<A> :: growDown() {
		return growDown_;
	}

	template<class A>
	inline const Timer&
	Timers<A> :: prove() const {
		return prove_;
	}
	template<class A>
	inline const Timer&
	Timers<A> :: refresh() const {
		return refresh_;
	}
	template<class A>
	inline const Timer&
	Timers<A> :: growUp() const {
		return growUp_;
	}
	template<class A>
	inline const Timer&
	Timers<A> :: growDown() const {
		return growDown_;
	}

	template<class A>
	inline bool
	Timers<A> :: wasRefreshed() const
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
	template<class A>
	void
	Timers<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Timers<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += prove_.getVolume();
		volume += refresh_.getVolume();
		volume += growUp_.getVolume();
		volume += growDown_.getVolume();
		return volume;
	}
	template<class A>
	Size_t
	Timers<A> :: getSizeOf() const {
		return sizeof (Timers);
	}
	template<class A>
	void
	Timers<A> :: show (String& string) const
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

	template<class A>
	inline String&
	operator << (String& string, const Timers<A>& timers)
	{
		timers.show (string);
		return string;
	}
}
}
}

#endif /*MDL_PROVER_PROVER_TREE_TIMERS_CPP_*/
