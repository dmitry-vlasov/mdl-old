/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_interface_stack_Line.cpp                              */
/* Description:     metamath stack line                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_INTERFACE_STACK_LINE_CPP_
#define MM_INTERFACE_STACK_LINE_CPP_

#include "interface/mm_interface.hpp"

namespace mm {
namespace interface {
namespace stack {

	/****************************
	 *		Public members
	 ****************************/

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Object implementation
	void
	Line :: commitSuicide() {
		delete this;
	}
	Size_t
	Line :: getVolume () const {
		return expression_.getVolume();
	}
	Size_t
	Line :: getSizeOf () const {
		return sizeof (Line);
	}
	void
	Line :: show (String& string) const
	{
		string << "expression:" << space;
		expression_.write (string); string << tab;
		string << "step:" << space;
		if (step_ != NULL) {
			string << *step_;
		} else {
			string << " NULL";
		}
		string << endLine;
	}
}
}
}

#endif /* MM_INTERFACE_STACK_LINE_CPP_ */
