/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_statistics_Statistics.cpp                  */
/* Description:     statistics representation                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace auxiliary {
namespace statistics {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Statistics :: Statistics () :
	data_ () {
	}
	Statistics :: ~ Statistics() {
	}

	inline Sample&
	Statistics :: get (const Kind_ kind) {
		return data_ [kind];
	}
	inline const Sample&
	Statistics :: get (const Kind_ kind) const {
		return data_ [kind];
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// nstd :: Object implementation
	void
	Statistics :: commitSuicide() {
		delete this;
	}
	Size_t
	Statistics :: getVolume() const
	{
		Size_t volume = 0;
		for (int i = 0; i < DIMENSION; ++ i) {
			volume += data_ [i].getVolume();
		}
		return volume;
	}
	Size_t
	Statistics :: getSizeOf() const {
		return sizeof (Statistics);
	}
	void
	Statistics :: show (nstd :: String<>& string) const
	{
		for (value :: Integer i = 0; i < DIMENSION; ++ i) {
			string << "data line " << i << ": ";
			data_[i].showBrief (string);
			string << endLine;
		}
	}
}
}
}


