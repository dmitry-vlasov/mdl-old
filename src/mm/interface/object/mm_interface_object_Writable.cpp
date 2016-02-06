/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_interface_object_Writable.cpp                         */
/* Description:     abstract interface for writable object                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "interface/object/mm_interface_object_Writable.hpp"

namespace mm {
namespace interface {
namespace object {

	/****************************
	 *		Public members
	 ****************************/

	void
	Writable :: show (String& string) const {
		write (string);
	}
	void
	Writable :: write (Output& output) const {
		output.write (this);
	}
	void
	Writable :: write() const {
	}
	bool
	Writable :: nothingToWrite() const {
		return false;
	}
}
}
}


