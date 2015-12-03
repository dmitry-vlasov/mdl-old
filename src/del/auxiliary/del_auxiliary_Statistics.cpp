/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File name:       del_auxiliary_Statistics.cpp                             */
/* Description:     class for program data statistics counters               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_AUXILIARY_STATISTICS_CPP_
#define DEL_AUXILIARY_STATISTICS_CPP_

#include "del/del_Del.hpp"

namespace del {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Statistics :: Statistics () :
	dataVector_ (INITIAL_DATA_VECTOR_CAPACITY),
	data_ (NULL) {
	}
	Statistics :: ~ Statistics() {
	}

	Statistics :: Data*
	Statistics :: data() {
		return data_;
	}
	void
	Statistics :: push() {
		data_ = dataVector_.push();
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Object implementation
	void
	Statistics :: commitSuicide() {
		delete this;
	}
	Size_t
	Statistics :: getVolume() const {
		return dataVector_.getVolume();
	}
	Size_t
	Statistics :: getSizeOf() const {
		return sizeof (Statistics);
	}
	void
	Statistics :: show (String& string) const
	{
		for (value :: Integer i = 0; i < dataVector_.getSize(); ++ i) {
			const Data* data = dataVector_.getValue (i);
			string << *data;
		}
	}

	/****************************
	 *		Private members
	 ****************************/
}
}

#endif /*DEL_AUXILIARY_STATISTICS_CPP_*/
