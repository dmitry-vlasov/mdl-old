/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_equation_Interval.cpp                               */
/* Description:     Interval of numeric values                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {
namespace equation {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Interval :: Interval () :
	low_ (false),
	high_(true) {
	}
	Interval :: Interval (const Real value, bool high) :
	low_ (false),
	high_ (true)
	{
		if (high) {
			high_ = value;
		} else {
			low_ = value;
		}
	}
	inline
	Interval :: Interval (const Real low, const Real high) :
	low_ (low),
	high_ (high) {
	}
	inline
	Interval :: Interval (const Interval& interval) :
	low_ (interval.low_),
	high_ (interval.high_) {
	}
	inline
	Interval :: ~ Interval() {
	}

	inline bool
	Interval :: contains (const Real value) const {
		return (low_ <= value) && (value <= high_);
	}

	ValueInf
	Interval :: getLow() const {
		return low_;
	}
	ValueInf
	Interval :: getHigh() const {
		return high_;
	}
	void
	Interval :: operator = (const Interval& interval)
	{
		low_ = interval.low_;
		high_ = interval.high_;
	}

	inline void
	Interval :: setLow (const Real value) {
		low_ = value;
	}
	inline void
	Interval :: setHigh (const Real value) {
		high_ = value;
	}

	/****************************
	 *		Private members
	 ****************************/
}
}


