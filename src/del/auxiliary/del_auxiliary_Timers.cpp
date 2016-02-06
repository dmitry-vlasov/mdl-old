/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File name:       del_auxiliary_Timers.cpp                                 */
/* Description:     class for processing timers                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/auxiliary/del_auxiliary.hpp"

namespace del {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	void
	Timers :: checkOutOfTime()
	{
		if (solving_.isOn()) {
			if (solving_.getSeconds() > Config :: getMaxSolveTime()) {
				throw exception :: OutOfTime();
			}
		} else if (decomposing_.isOn()){
			if (decomposing_.getSeconds() > Config :: getMaxDecomposeTime()) {
				throw exception :: OutOfTime();
			}
		} else if (minimizing_.isOn()){
			if (minimizing_.getSeconds() > Config :: getMaxMinimizeTime()) {
				throw exception :: OutOfTime();
			}
		}
	}

	bool
	Timers :: showProgress
	(
		const value :: Integer currentCount,
		const value :: Integer totalCount,
		const char* message,
		const bool thorough
	) const
	{
		const Timer& currentTimer = getCurrent();
		return showProgress (currentCount, totalCount, currentTimer, message, thorough);
	}
	bool
	Timers :: showProgress
	(
		const value :: Integer currentCount,
		const value :: Integer totalCount,
		const Timer& timer,
		const char* message,
		const bool thorough
	) const
	{
		if (Config :: verbosity() <= 1) {
			return false;
		}
		if (refresh_.getMilliseconds() < Config :: getRefreshClock()) {
			return false;
		}
		refresh_.start();
		progressShowed_ = true;
		const int percent = (currentCount * 100) / totalCount;
		std :: cout << std :: endl;
		std :: cout << chars :: TAB << chars :: TAB << "-- done: " << percent << "%," << chars :: TAB;

		const bool cumulativeShowStatus = timer.getShowCumulativeTime();
		timer.setShowCumulativeTime (false);
		std :: cout << timer << " passed ";
		if (thorough) {
			std :: cout << "(" << currentCount << " of " << totalCount << ") ";
		}
		if (message != "") {
			std :: cout << message << " ";
		}
		timer.setShowCumulativeTime (cumulativeShowStatus);
		return true;
	}
	inline void
	Timers :: startProgress()
	{
		refresh_.start();
		progressShowed_ = false;
	}
	inline void
	Timers :: stopProgress() {
		refresh_.stop();
	}

	Timer&
	Timers :: current()
	{
		if (minimize_.isOn()) {
			return minimize_;
		} else if (normalize_.isOn()) {
			return normalize_;
		} else if (primitivize_.isOn()) {
			return primitivize_;
		} else if (decompose_.isOn()) {
			return decompose_;
		} else if (assemble_.isOn()) {
			return assemble_;
		} else if (compile_.isOn()) {
			return compile_;
		} else {
			return execute_;
		}
	}
	const Timer&
	Timers :: getCurrent() const
	{
		if (minimize_.isOn()) {
			return minimize_;
		} else if (normalize_.isOn()) {
			return normalize_;
		} else if (primitivize_.isOn()) {
			return primitivize_;
		} else if (decompose_.isOn()) {
			return decompose_;
		} else if (assemble_.isOn()) {
			return assemble_;
		} else if (compile_.isOn()) {
			return compile_;
		} else {
			return execute_;
		}
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Object interface
	void
	Timers :: commitSuicide() {
		delete this;
	}
	Size_t
	Timers :: getVolume() const {
		return 0;
	}
	Size_t
	Timers :: getSizeOf() const {
		return sizeof (Timers);
	}
	void
	Timers :: show (String& string) const
	{
		string << "timings:" << endLine;
		string << "-------------------------" << endLine;
		if (init_.isUsed()) {
			string << tab << "init:      " << init_ << endLine;
		}
		if (read_.isUsed()) {
			string << tab << "read:      " << read_ << endLine;
		}
		if (solve_.isUsed()) {
			string << tab << "solve:     " << solve_ << endLine;
		}
		if (Config :: showTimings()) {
			if (execute_.isUsed()) {
				string << tab << "execute:   " << execute_ << endLine;
			}
			if (minimize_.isUsed()) {
				string << tab << tab << "minimize:  " << minimize_ << endLine;
			}
			if (normalize_.isUsed()) {
				string << tab << tab << "normalize: " << normalize_ << endLine;
			}
			if (primitivize_.isUsed()) {
				string << tab << tab << "primitivize: " << primitivize_ << endLine;
			}
			if (decompose_.isUsed()) {
				string << tab << tab << "decompose: " << decompose_ << endLine;
			}
			if (assemble_.isUsed()) {
				string << tab << tab << "assemble: " << assemble_ << endLine;
			}
			if (compile_.isUsed()) {
				string << tab << tab << "compile:   " << compile_ << endLine;
			}
		} else {
			if (execute_.isUsed()) {
				string << tab << "decompose: " << execute_ << endLine;
			}
		}
		if (verify_.isUsed()) {
			string << tab << "verifying: " << verify_ << endLine;
		}
		if (translate_.isUsed()) {
			string << tab << "translate: " << translate_ << endLine;
		}
		if (write_.isUsed()) {
			string << tab << "write:     " << write_ << endLine;
		}
		if (release_.isUsed()) {
			string << tab << "release:     " << release_ << endLine;
		}
		string << "cumulative timings:" << endLine;
		string << "-------------------------" << endLine;
		if (solving_.isUsed()) {
			solving_.setShowCumulativeTime();
			string << tab << "solving:       " << solving_ << endLine;
		}
		if (decomposing_.isUsed()) {
			decomposing_.setShowCumulativeTime();
			string << tab << "decomposing:   " << decomposing_ << endLine;
		}
		if (minimizing_.isUsed()) {
			minimizing_.setShowCumulativeTime();
			string << tab << "minimizing:   " << minimizing_ << endLine;
		}
	}

	/**********************************
	 *		Private static members
	 **********************************/

	Timer Timers :: init_;
	Timer Timers :: release_;
	Timer Timers :: solving_;
	Timer Timers :: decomposing_;
	Timer Timers :: minimizing_;
	Timer Timers :: refresh_;
	bool  Timers :: progressShowed_ = false;
}
}


