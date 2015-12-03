/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_model_queue_Range.cpp                      */
/* Description:     abstract interface for range element                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_INTERFACE_MODEL_QUEUE_RANGE_CPP_
#define DEL_INTERFACE_MODEL_QUEUE_RANGE_CPP_

#include "del/interface/model/queue/del_interface_model_queue_Element.hpp"

namespace del {
namespace interface {
namespace model {
namespace queue {

	/****************************
	 *		Public members
	 ****************************/

	bool
	Range :: operator < (const Range& range) const
	{
		if (getRelation() < range.getRelation()) {
			return true;
		}
		if (getRelation() > range.getRelation()) {
			return false;
		}

		if (getSize() < range.getSize()) {
			return true;
		}
		if (getSize() > range.getSize()) {
			return false;
		}

		for (value :: Integer i = 0; i < getSize(); ++ i) {
			if (getConcept (i) < range.getConcept(i)) {
				return true;
			}
			if (getConcept (i) > range.getConcept(i)) {
				return false;
			}
		}
		return false;
	}
	inline bool
	Range :: operator > (const Range& range) const {
		return range.operator < (*this);
	}
	bool
	Range :: operator == (const Range& range) const
	{
		if (getSize() != range.getSize()) {
			return false;
		}
		if (getRelation() != range.getRelation()) {
			return false;
		}
		for (value :: Integer i = 0; i < getSize(); ++ i) {
			if (getConcept (i) != range.getConcept (i)) {
				return false;
			}
		}
		return true;
	}
}
}
}
}

#endif /*DEL_INTERFACE_MODEL_QUEUE_RANGE_CPP_*/
