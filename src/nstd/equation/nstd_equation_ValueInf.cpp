/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File Name:       nstd_equation_ValueInf.cpp                               */
/* Description:     possibly infinite value                                  */
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
	ValueInf :: ValueInf (const bool sign) :
	value_ (0),
	inf_ (true),
	sign_ (sign) {
	}
	inline
	ValueInf :: ValueInf (const Real value) :
	value_ (value),
	inf_ (false),
	sign_ (value > 0) {
	}
	inline
	ValueInf :: ValueInf (const ValueInf& valueInf) :
	value_ (valueInf.value_),
	inf_ (valueInf.inf_),
	sign_ (valueInf.sign_) {
	}
	inline
	ValueInf :: ~ ValueInf() {
	}

	inline Real
	ValueInf :: getValue() const {
		return value_;
	}
	inline bool
	ValueInf :: isInfinite() const {
		return inf_;
	}
	inline bool
	ValueInf :: isPositive() const {
		return sign_;
	}

	inline void
	ValueInf :: operator = (const ValueInf& valueInf)
	{
		value_ = valueInf.value_;
		inf_ = valueInf.inf_;
	}
	inline void
	ValueInf :: operator = (const Real value)
	{
		value_ = value;
		inf_ = false;
	}

	bool
	ValueInf :: operator < (const Real value) const
	{
		if (inf_) {
			return !sign_;
		} else {
			return value_ < value;
		}
	}
	bool
	ValueInf :: operator <= (const Real value) const
	{
		if (inf_) {
			return !sign_;
		} else {
			return value_ <= value;
		}
	}
	bool
	ValueInf :: operator > (const Real value) const
	{
		if (inf_) {
			return sign_;
		} else {
			return value_ > value;
		}
	}
	bool
	ValueInf :: operator >= (const Real value) const
	{
		if (inf_) {
			return sign_;
		} else {
			return value_ >= value;
		}
	}
	bool
	ValueInf :: operator == (const Real value) const
	{
		if (inf_) {
			return false;
		} else {
			return fabs (value_ - value) < 1E-12;
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	/********************************
	 *		Overloaded operators
	 ********************************/

	inline bool
	operator < (const Real value_1, const ValueInf& value_2) {
		return (value_2 > value_1);
	}
	inline bool
	operator <= (const Real value_1, const ValueInf& value_2) {
		return (value_2 >= value_1);
	}
	inline bool
	operator > (const Real value_1, const ValueInf& value_2) {
		return (value_2 < value_1);
	}
	inline bool
	operator >= (const Real value_1, const ValueInf& value_2) {
		return (value_2 <= value_1);
	}
	inline bool
	operator == (const Real value_1, const ValueInf& value_2) {
		return (value_2 == value_1);
	}
}
}


