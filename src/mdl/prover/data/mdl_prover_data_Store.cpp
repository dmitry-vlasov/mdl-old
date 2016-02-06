/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_data_Store.cpp                                */
/* Description:     store of the tree statistics data                        */
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
namespace data {

	/****************************
	 *		Public members
	 ****************************/

	Store :: Store () :
	dataVector_ (INITIAL_DATA_VECTOR_CAPACITY) {
	}
	Store :: ~ Store() {
	}

	void
	Store :: add (Data* data) {
		dataVector_.add (data);
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;
using manipulator :: iterate;

	void
	Store :: showVolume (String& string, const int indent) const
	{
		if (dataVector_.getSize() == 0) {
			return;
		}
		Data average;
		for (int i = 0; i < dataVector_.getSize(); ++ i){
			const Data* data = dataVector_.getValue (i);
			average += *data;
		}
		average /= dataVector_.getSize();
		average.showVolume (string, indent);
	}
	void
	Store :: showTiming (String& string, const int indent) const
	{
		if (dataVector_.getSize() == 0) {
			return;
		}
		Data average;
		for (int i = 0; i < dataVector_.getSize(); ++ i){
			const Data* data = dataVector_.getValue (i);
			average += *data;
		}
		average /= dataVector_.getSize();
		average.showTiming (string, indent);
	}

	// object :: Object interface
	void
	Store :: commitSuicide() {
		delete this;
	}
	Size_t
	Store :: getVolume() const
	{
		Size_t volume = 0;
		volume += dataVector_.getVolume();
		return volume;
	}
	Size_t
	Store :: getSizeOf() const {
		return sizeof (Tree);
	}
	void
	Store :: show (String& string) const
	{
		showVolume (string);
		showTiming (string);
	}
}
}
}


