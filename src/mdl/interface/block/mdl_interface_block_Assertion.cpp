/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_block_Assertion.cpp                        */
/* Description:     assertion abstract interface                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_BLOCK_ASSERTION_CPP_
#define MDL_INTERFACE_BLOCK_ASSERTION_CPP_

namespace mdl {
namespace interface {
namespace block {

	/****************************
	 *		Public members
	 ****************************/

	/*********************************
	 *		Overloaded operators
	 *********************************/

	/*inline bool
	operator < (const Assertion& assertion_1, const Assertion& assertion_2)
	{
		if (assertion_1.getRate() < assertion_2.getRate()) {
			return true;
		} else if (assertion_1.getRate() < assertion_2.getRate()) {
			return &assertion_1 < &assertion_2;
		} else {
			return false;
		}
	}
	inline bool
	operator <= (const Assertion& assertion_1, const Assertion& assertion_2) {
		return (assertion_1.getRate() <= assertion_2.getRate());
	}
	inline bool
	operator > (const Assertion& assertion_1, const Assertion& assertion_2) {
		return operator < (assertion_2, assertion_1);
	}
	inline bool
	operator >= (const Assertion& assertion_1, const Assertion& assertion_2) {
		return operator <= (assertion_2, assertion_1);
	}
	inline bool
	operator == (const Assertion& assertion_1, const Assertion& assertion_2) {
		return (&assertion_1 == &assertion_2);
	}*/
}
}
}

#endif /*MDL_INTERFACE_BLOCK_ASSERTION_CPP_*/
