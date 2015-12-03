/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_parameter_Parameter.cpp                    */
/* Description:     general parameter class template                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_PARAMETER_PARAMETER_CPP_
#define MDL_AUXILIARY_PARAMETER_PARAMETER_CPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/auxiliary/mdl_auxiliary.hpp"

namespace mdl {
namespace auxiliary {
namespace parameter {

	/****************************
	 *		Public members
	 ****************************/


	inline
	Parameter :: Parameter (const Description* description) :
	description_ (description),
	value_ (description->getDefaultValue()) {
	}
	inline
	Parameter :: Parameter (const Parameter& parameter) :
	description_ (parameter.description_),
	value_ (parameter.value_) {
	}
	Parameter :: ~ Parameter() {
	}


	inline const Description*
	Parameter :: getDescription() const {
		return description_;
	}
	inline value :: Real
	Parameter :: getValue() const {
		return value_;
	}
	inline void
	Parameter :: setValue (const value :: Real value) {
		value_ = value;
	}
	inline void
	Parameter :: setRealValue (const value :: Real value) {
		value_ = value;
	}
	inline void
	Parameter :: setIntegerValue (const value :: Integer value) {
		value_ = value;
	}

	inline void
	Parameter :: setDefaultValue() {
		value_ = description_->getDefaultValue();
	}
	inline void
	Parameter :: setMaximumValue() {
		value_ = description_->getMaximumValue();
	}
	inline void
	Parameter :: setMinimumValue() {
		value_ = description_->getMinimumValue();
	}
	inline void
	Parameter :: setHighValue() {
		value_ = (description_->getMaximumValue() + description_->getDefaultValue()) / 2;
	}
	inline void
	Parameter :: setLowValue() {
		value_ = (description_->getMinimumValue() + description_->getDefaultValue()) / 2;
	}

	inline void
	Parameter :: operator = (const Parameter& parameter)
	{
		description_ = parameter.description_;
		value_ = parameter.value_;
	}
	inline void
	Parameter :: copy (const Parameter& parameter)
	{
		description_ = parameter.description_;
		value_ = parameter.value_;
	}

using manipulator :: endLine;

	template<class S>
	void
	Parameter :: show (S& string) const
	{
		string << *description_ << endLine;
		string << "value = " << value_ << endLine;
	}

	// nstd :: Object implementation
	void
	Parameter :: commitSuicide() {
		delete this;
	}
	Size_t
	Parameter :: getVolume() const
	{
		Size_t volume = 0;
		return volume;
	}
	Size_t
	Parameter :: getSizeOf() const {
		return sizeof (Parameter);
	}
	void
	Parameter :: show (nstd :: String<>& string) const {
		show<nstd :: String<>& > (string);
	}
}
}
}

#endif /*MDL_AUXILIARY_PARAMETER_PARAMETER_CPP_*/
