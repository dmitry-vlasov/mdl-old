/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_object_Verifiable.cpp                      */
/* Description:     abstract interface for verifiable objects                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/object/mdl_interface_object_Buildable.hpp"

namespace mdl {
namespace interface {
namespace object {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Verifiable :: Verifiable() :
	contents_ (NULL) {
	}
	Verifiable :: ~ Verifiable() {
	}

	void
	Verifiable :: check() {
	}
	void
	Verifiable :: compress() {
	}
	void
	Verifiable :: reprove() {
	}
	void
	Verifiable :: prove() {
	}
	bool
	Verifiable :: isVerified() const {
		return true;
	}
	void
	Verifiable :: mine (String&) const {
	}
	void
	Verifiable :: setContents (Contents* contents) {
		contents_ = contents;
	}
}
}
}


