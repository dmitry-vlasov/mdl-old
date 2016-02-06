/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_object_Writable.cpp                        */
/* Description:     writable objects                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/auxiliary/del_auxiliary_Output.hpp"
#include "del/interface/del_interface_Writable.hpp"

namespace del {
namespace interface {

	/****************************
	 *		Public members
	 ****************************/

	void
	Writable :: show (String& string) const {
		replicate (string);
	}
	void
	Writable :: write (Output& output) const {
		output.write (this);
	}
	void
	Writable :: write (String& string) const {
		replicate (string);
	}
	void
	Writable :: write() const {
	}
}
}


