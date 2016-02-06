/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_term_SubCplx.cpp                     */
/* Description:     substitution complexity evaluation function              */
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
	SubCplx :: SubCplx () :
	location_ () {
	}
	inline
	SubCplx :: SubCplx
	(
		const Location& location,
		mdl :: Theory* theory
	) :
	location_ (location) {
	}
	SubCplx :: ~ SubCplx() {
	}

	// evaluation :: Term implementation
	value :: Real
	SubCplx :: eval (const HeapNode_* node) const
	{
		const value :: Real subComplexity = node->getSubComplexity();
		const value :: Real normalizedSubComplexity =
			Math :: statistics()->get(Statistics :: SUBSTITUTION_COMPLEXITY).normalize (subComplexity);
		return normalizedSubComplexity;
	}

using manipulator :: endLine;

	// object :: Writable implementation
	void
	SubCplx :: replicate (String& string) const
	{
		string << Indent (depth_ + 2) << Token :: subCplx_;
		string << Token :: openBracket_ << Token :: closeBracket_;
	}

	// object :: Object implementation
	void
	SubCplx :: commitSuicide() {
		delete this;
	}
	Size_t
	SubCplx :: getVolume() const {
		return 0;
	}
	Size_t
	SubCplx :: getSizeOf() const {
		return sizeof (SubCplx);
	}
}
}
}
}


