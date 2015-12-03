/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_object_Writable.cpp                        */
/* Description:     writable objects                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_OBJECT_WRITABLE_CPP_
#define MDL_INTERFACE_OBJECT_WRITABLE_CPP_

#include "mdl/auxiliary/mdl_auxiliary_Output.hpp"
#include "mdl/interface/object/mdl_interface_object_Writable.hpp"

namespace mdl {
namespace interface {
namespace object {

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
	Writable :: write() const {
	}
	bool
	Writable :: lookup() const {
		return false;
	}
	Writable*
	Writable :: find() {
		return NULL;
	}
	const Writable*
	Writable :: find() const {
		return NULL;
	}
}
}
}

#endif /*MDL_INTERFACE_OBJECT_WRITABLE_CPP_*/
