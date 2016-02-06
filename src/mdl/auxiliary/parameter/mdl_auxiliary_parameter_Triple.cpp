/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_parameter_Triple.cpp                       */
/* Description:     triple of parameters                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/auxiliary/mdl_auxiliary.hpp"

namespace mdl {
namespace auxiliary {
namespace parameter {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Triple :: Triple (const Description* description) :
	description_ (description),
	valueHigh_ (description->getMaximumValue()),
	valueMid_ (description->getDefaultValue()),
	valueLow_ (description->getMinimumValue()) {
		initValues();
	}
	inline
	Triple :: Triple (const Description* description, const value :: Real value) :
	description_ (description),
	valueHigh_ (description->getMaximumValue()),
	valueMid_ (value),
	valueLow_ (description->getMinimumValue()) {
		initValues();
	}
	inline
	Triple :: Triple (const Triple& triple) :
	description_ (triple.description_),
	valueHigh_ (triple.valueHigh_),
	valueMid_ (triple.valueMid_),
	valueLow_ (triple.valueLow_) {
	}
	Triple :: ~ Triple() {
	}

	inline value :: Real
	Triple :: getValueHigh() const {
		return valueHigh_;
	}
	inline value :: Real
	Triple :: getValueMid() const {
		return valueMid_;
	}
	inline value :: Real
	Triple :: getValueLow() const {
		return valueLow_;
	}
	bool
	Triple :: isFlat() const
	{
		const bool deltaLow = (valueMid_ - valueLow_);
		const bool deltaHigh = (valueHigh_ - valueMid_);
		return
			(deltaLow <= description_->getQuantumValue()) &&
			(deltaHigh <= description_->getQuantumValue());
	}

	void
	Triple :: iterateHighCase()
	{
		const value :: Real deltaLow = (valueMid_ - valueLow_);
		const value :: Real deltaHigh = (valueHigh_ - valueMid_);
		const value :: Real deltaAvg = (deltaLow + deltaHigh) / 2;

		const value :: Real newValueHigh= valueMid_ + deltaAvg;
		const value :: Real newValueMid = valueHigh_;
		const value :: Real newValueLow = valueMid_;

		valueHigh_ = newValueHigh;
		valueMid_ = newValueMid;
		valueLow_ = newValueLow;

		if (valueHigh_ > description_->getMaximumValue()) {
			const value :: Real delta = (description_->getMaximumValue() - valueMid_);
			valueHigh_ = valueMid_ + delta / 2;
		}
	}
	void
	Triple :: iterateMidCase()
	{
		const value :: Real deltaLow = (valueMid_ - valueLow_);
		const value :: Real deltaHigh = (valueHigh_ - valueMid_);

		const value :: Real newValueHigh = valueMid_ + deltaHigh / 2;
		const value :: Real newValueMid = valueMid_;
		const value :: Real newValueLow = valueMid_ - deltaLow / 2;

		valueHigh_ = newValueHigh;
		valueMid_ = newValueMid;
		valueLow_ = newValueLow;
	}
	void
	Triple :: iterateLowCase()
	{
		const value :: Real deltaLow = (valueMid_ - valueLow_);
		const value :: Real deltaHigh = (valueHigh_ - valueMid_);
		const value :: Real deltaAvg = (deltaLow + deltaHigh) / 2;

		const value :: Real newValueHigh = valueMid_;
		const value :: Real newValueMid = valueLow_;
		const value :: Real newValueLow = valueMid_ - deltaAvg;

		valueHigh_ = newValueHigh;
		valueMid_ = newValueMid;
		valueLow_ = newValueLow;

		if (valueLow_ < description_->getMinimumValue()) {
			const value :: Real delta = (valueMid_ - description_->getMinimumValue());
			valueLow_ = valueMid_ - delta / 2;
		}
	}

using manipulator :: endLine;

	// object :: Object implementation
	void
	Triple :: commitSuicide() {
		delete this;
	}
	Size_t
	Triple :: getVolume() const
	{
		Size_t volume = 0;
		return volume;
	}
	Size_t
	Triple :: getSizeOf() const {
		return sizeof (Triple);
	}
	void
	Triple :: show (String& string) const
	{
		string << *description_ << endLine;
		string << "value high = " << valueHigh_ << endLine;
		string << "value mid = " << valueMid_ << endLine;
		string << "value low = " << valueLow_ << endLine;
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Triple :: initValues()
	{
		const value :: Real deltaLow = (valueMid_ - valueLow_);
		const value :: Real deltaHigh = (valueHigh_ - valueMid_);
		valueHigh_ = valueHigh_ - deltaHigh / 2;
		valueLow_  = valueLow_ + deltaLow / 2;
	}
}
}
}


