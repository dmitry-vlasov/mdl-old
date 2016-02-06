/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_parameter_Description.cpp                  */
/* Description:     general description parameter template                   */
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
	Description :: Description (const Description& description) :
	isReal_ (description.isReal_),
	name_ (description.name_),
	defaultValue_ (description.defaultValue_),
	minimumValue_ (description.minimumValue_),
	maximumValue_ (description.maximumValue_),
	quantumValue_ (description.quantumValue_) {
	}
	inline
	Description :: Description
	(
		const value :: Real defaultValue,
		const value :: Real minimumValue,
		const value :: Real maximumValue,
		const value :: Real quantumValue,
		const char* name,
		const bool isReal
	) :
	isReal_ (isReal),
	name_ (name),
	defaultValue_ (defaultValue),
	minimumValue_ (minimumValue),
	maximumValue_ (maximumValue),
	quantumValue_ (quantumValue) {
	}
	Description :: ~ Description() {
	}

	inline bool
	Description :: isReal() const {
		return isReal_;
	}
	inline bool
	Description :: isInteger() const {
		return !isReal_;
	}

	inline value :: Real
	Description :: getMinimumValue() const {
		return minimumValue_;
	}
	inline value :: Real
	Description :: getMaximumValue() const {
		return maximumValue_;
	}
	inline value :: Real
	Description :: getQuantumValue() const {
		return quantumValue_;
	}
	inline value :: Real
	Description :: getDefaultValue() const {
		return defaultValue_;
	}
	inline const char*
	Description :: getName() const {
		return name_;
	}
	inline void
	Description :: operator = (const Description& description)
	{
		name_ = description.name_;
		defaultValue_ = description.defaultValue_;
		minimumValue_ = description.minimumValue_;
		maximumValue_ = description.maximumValue_;
		quantumValue_ = description.quantumValue_;
	}

using manipulator :: endLine;

	template<class S>
	void
	Description :: show (S& string) const
	{
		string << "parameter: " << name_<< endLine;
		string << "minimum = " << minimumValue_ << ", ";
		string << "default = " << defaultValue_ << ", ";
		string << "maximum = " << maximumValue_ << ", ";
		string << "quantum = " << quantumValue_ << ", ";
	}

using manipulator :: endLine;

	// nstd :: Object implementation
	void
	Description :: commitSuicide() {
		delete this;
	}
	Size_t
	Description :: getVolume() const
	{
		Size_t volume = 0;
		return volume;
	}
	Size_t
	Description :: getSizeOf() const {
		return sizeof (Description);
	}
	void
	Description :: show (nstd :: String<>& string) const {
		show<nstd :: String<>& > (string);
	}
}
}
}


