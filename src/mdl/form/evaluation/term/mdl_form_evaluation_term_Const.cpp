/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_term_Const.cpp                       */
/* Description:     constant evaluation function                             */
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
	Const :: Const (const value :: Real constant) :
	location_ (),
	constant_ (constant) {
	}
	inline
	Const :: Const
	(
		const Location& location,
		const value :: Real constant,
		mdl :: Theory*
	) :
	location_ (location),
	constant_ (constant) {
	}
	Const :: ~ Const() {
	}

	// evaluation :: Term implementation
	value :: Real
	Const :: eval (const HeapNode_* node) const {
		return constant_;
	}

using manipulator :: endLine;

	// object :: Writable implementation
	void
	Const :: replicate (String& string) const
	{
		string << Indent (depth_ + 2) << Token :: const_ << Token :: openSqBracket_;
		string << constant_ << Token :: closeSqBracket_;
		string << Token :: openBracket_ << Token :: closeBracket_;
	}

	// object :: Object implementation
	void
	Const :: commitSuicide() {
		delete this;
	}
	Size_t
	Const :: getVolume() const {
		return 0;
	}
	Size_t
	Const :: getSizeOf() const {
		return sizeof (Const);
	}
}
}
}
}


