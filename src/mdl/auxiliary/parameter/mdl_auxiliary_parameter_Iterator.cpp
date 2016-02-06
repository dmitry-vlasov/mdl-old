/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_parameter_Iterator.cpp                     */
/* Description:     general parameter vector iterator                        */
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
	Iterator :: Iterator (const mdl :: parameter :: vector :: Description* descriptionVector) :
	descriptionVector_ (descriptionVector),
	dimension_ (descriptionVector_->getSize()),
	parameters_ (dimension_)
	{
		for (value :: Integer i = 0; i < dimension_; ++ i) {
			const Description*
				description = descriptionVector_->getValue (i);
			const value :: Real
				minValue = description->getMinimumValue();
			parameters_.add (minValue);
		}
	}
	Iterator :: ~ Iterator() {
	}

	inline bool
	Iterator :: operator ++ () {
		return increment();
	}
	inline value :: Real
	Iterator :: getValue (const value :: Integer i) const {
		return parameters_.getValue (i);
	}
	inline vector :: value :: Real&
	Iterator :: parameters() {
		return parameters_;
	}

using manipulator :: endLine;

	template<class S>
	void
	Iterator :: show (S& string) const
	{
		string << "parameters: " << parameters_<< endLine;
	}

using manipulator :: endLine;

	// nstd :: Object implementation
	void
	Iterator :: commitSuicide() {
		delete this;
	}
	Size_t
	Iterator :: getVolume() const
	{
		Size_t volume = 0;
		volume += parameters_.getVolume();
		return volume;
	}
	Size_t
	Iterator :: getSizeOf() const {
		return sizeof (Iterator);
	}
	void
	Iterator :: show (nstd :: String<>& string) const {
		show<nstd :: String<>& > (string);
	}

	/****************************
	 *		Private members
	 ****************************/

	bool
	Iterator :: increment (const value :: Integer d)
	{
		if (d == dimension_) {
			return true;
		}
		value :: Real&
			value = parameters_.getReference (d);
		const Description*
			description = descriptionVector_->getValue (d);

		const value :: Real
			newValue = value + description->getQuantumValue();

		if (newValue < description->getMaximumValue()) {
			value = newValue;
			return false;
		} else {
			value = description->getMinimumValue();
			return increment (d + 1);
		}
	}
}
}
}


