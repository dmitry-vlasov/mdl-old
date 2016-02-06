/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_node_Proposition.cpp                      */
/* Description:     proposition as a proof node                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/form/mdl_form.hpp"

namespace mdl {
namespace form {
namespace proof {
namespace node {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Proposition :: Proposition
	(
		mdl :: Assertion* assertion,
		index :: Arity index,
		const array :: Expression* const expression
	) :
	Statement (assertion, index, expression) {
	}
	Proposition :: ~ Proposition() {
	}

	// mdl :: proof :: Node implementation
	Proposition :: Kind
	Proposition :: getKind() const {
		return PROP;
	}

	// object :: Object interface
	void
	Proposition :: commitSuicide() {
		delete this;
	}
	Size_t
	Proposition :: getVolume() const {
		return Statement :: getVolume ();
	}
	Size_t
	Proposition :: getSizeOf() const {
		return sizeof (Proposition);
	}
}
}
}
}


