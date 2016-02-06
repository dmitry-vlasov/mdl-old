/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_formula_subset_normal_Primitive.cpp           */
/* Description:     primitive (root) formula of a ⊑ b type                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/lexer/del_lexer.hpp"
#include "del/source/del_source.hpp"

namespace del {
namespace source {
namespace formula {
namespace subset {
namespace normal {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Primitive :: Primitive
	(
		const Location location,
		const del :: Term* term_1,
		const del :: Term* term_2,
		const del :: Formula* image,
		const bool isRoot,
		const bool isPrimary,
		const bool isDefinition
	) :
	Simple
	(
		location,
		term_1,
		term_2,
		((image == NULL) ? this : image),
		isRoot,
		isPrimary,
		isDefinition
	) {
	}
	inline
	Primitive :: Primitive (const del :: Formula* primitive) :
	Simple (primitive) {
	}
	inline
	Primitive :: Primitive (const Primitive& primitive) :
	Simple (primitive) {
	}
	Primitive :: ~ Primitive() {
	}

	// del :: Formula implementation
	bool
	Primitive :: isTrue (const del :: Model* model) const
	{
		const Symbol a = getTerm (0)->getSymbol();
		const Symbol b = getTerm (1)->getSymbol();
		return model->isTrueSubseteq (a, b);
	}
	bool
	Primitive :: isTrue (const del :: Model* model, const set :: Formula* untheory) const
	{
		const Symbol a = getTerm (0)->getSymbol();
		const Symbol b = getTerm (1)->getSymbol();
		return model->isTrueSubseteq (a, b, untheory);
	}
	const del :: Term*
	Primitive :: evalInterpolant (const del :: Model* model, const del :: Signature* delta) const
	{
		const Symbol a = getTerm (0)->getSymbol();
		const Symbol b = getTerm (1)->getSymbol();
		return model->evalInterpolant (a, b, delta);
	}
	del :: Formula :: Kind
	Primitive :: getKind() const {
		return SIMPLE_SUB_KIND;
	}
	bool
	Primitive :: primitivize (del :: Theory*, del :: Signature*) const {
		return false;
	}

	// del :: Cloneable implementation
	del :: Formula*
	Primitive :: clone() const
	{
		if (hasInvalidKind()) {
			return Normal :: create
			(
				term_1_->clone(),
				term_2_->clone(),
				image_,
				isRoot_,
				isPrimary_,
				isDefinition_
			);
		} else {
			return new Simple (*this);
		}
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Primitive :: replicate (String& string) const
	{
		string << location_.getIndent();
		term_1_->replicate (string);
		string << space << Token :: subset_ << 'p' << space;
		term_2_->replicate (string);
	}
	void
	Primitive :: translate (String& string) const {
		replicate (string);
	}

	// object :: Object implementation
	void
	Primitive :: commitSuicide() {
		delete this;
	}
	Size_t
	Primitive :: getVolume() const {
		return Simple :: getVolume();
	}
	Size_t
	Primitive :: getSizeOf() const {
		return sizeof (Primitive);
	}

	/****************************
	 *		Protected members
	 ****************************/

	const char*
	Primitive :: suffix() const {
		return "p";
	}
}
}
}
}
}


