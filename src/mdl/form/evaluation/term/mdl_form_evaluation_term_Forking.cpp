/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_term_Forking.cpp                     */
/* Description:     node forking evaluation function                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace form {
namespace evaluation {
namespace term {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Forking :: Forking () :
	location_ () {
	}
	inline
	Forking :: Forking
	(
		const Location& location,
		mdl :: Theory* theory
	) :
	location_ (location) {
	}
	Forking :: ~ Forking() {
	}

	// evaluation :: Term implementation
	value :: Real
	Forking :: eval (const HeapNode_* node) const
	{
		const value :: Real normalizedForking =
			Math :: statistics()->get(Statistics :: NODE_FORKING).normalize (node->getForking());
		return normalizedForking;
	}

using manipulator :: endLine;

	// object :: Writable implementation
	void
	Forking :: replicate (String& string) const
	{
		string << Indent (depth_ + 2) << Token :: forking_;
		string << Token :: openBracket_ << Token :: closeBracket_;
	}

	// object :: Object implementation
	void
	Forking :: commitSuicide() {
		delete this;
	}
	Size_t
	Forking :: getVolume() const {
		return 0;
	}
	Size_t
	Forking :: getSizeOf() const {
		return sizeof (Forking);
	}
}
}
}
}


