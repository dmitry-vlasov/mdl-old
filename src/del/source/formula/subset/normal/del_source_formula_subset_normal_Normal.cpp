/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_formula_subset_mal_Normal.cpp                 */
/* Description:     base normal formula class                                */
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
	Normal :: Normal
	(
		const Location location,
		const del :: Term* const term_1,
		const del :: Term* const term_2,
		const del :: Formula* image,
		const bool isRoot,
		const bool isPrimary,
		const bool isDefinition
	) :
	formula :: Termal
	(
		location,
		term_1,
		term_2,
		image,
		GENERAL_SUB_KIND,
		isRoot,
		isPrimary,
		isDefinition
	),
	decomposed_ (false) {
	}
	inline
	Normal :: Normal (const del :: Formula* normal) :
	formula :: Termal (normal) {
	}
	inline
	Normal :: Normal (const Normal& normal) :
	formula :: Termal (normal) {
	}
	Normal :: ~ Normal() {
	}

	del :: Formula*
	Normal :: create
	(
		const del :: Term* const term_1,
		const del :: Term* const term_2,
		const del :: Formula* image,
		const bool isRoot,
		const bool isPrimary,
		const bool isDefinition
	)
	{
		const del :: Formula :: Kind
			kind = del :: Formula :: getKind (term_1, term_2);
		switch (kind) {
		case del :: Formula :: SIMPLE_SUB_KIND :
			return new Simple (Location(), term_1, term_2, image, isRoot, isPrimary, isDefinition);
		case del :: Formula :: CONJ_SUB_KIND :
			return new Conjunction (Location(), term_1, term_2, image, isRoot, isPrimary, isDefinition);
		case del :: Formula :: RIGHT_SUB_KIND :
			return new RightExists (Location(), term_1, term_2, image, isRoot, isPrimary, isDefinition);
		case del :: Formula :: LEFT_SUB_KIND :
			return new LeftExists (Location(), term_1, term_2, image, isRoot, isPrimary, isDefinition);
		case del :: Formula :: GENERAL_SUB_KIND :
			return new formula :: Subset (Location(), term_1, term_2, image, GENERAL_SUB_KIND, isRoot, isPrimary, isDefinition);
		default :
			Error* error = new Error (Error :: SEMANTIC);
			error->message() << "non-normal formula" << endLine;
			throw error;
		}
	}

	// del :: Formula implementation
	bool
	Normal :: isTrivial() const {
		return false;
	}
	bool
	Normal :: isTrue (const del :: Model*) const {
		throw new Error();
	}
	bool
	Normal :: isTrue (const del :: Model*, const set :: Formula*) const {
		throw new Error();
	}
	const Term*
	Normal :: evalInterpolant (const del :: Model*, const del :: Signature*) const {
		throw new Error();
	}
	bool
	Normal :: isNormal() const {
		return true;
	}
	bool
	Normal :: normalize (del :: Theory*) const {
		return false;
	}
	Normal :: Type
	Normal :: getType() const {
		return SUBSET_TYPE;
	}
	bool
	Normal :: hasInvalidKind() const
	{
		const del :: Formula :: Kind kind_1 = getKind();
		const del :: Formula :: Kind kind_2 = Termal :: getKind();
		return (kind_1 != kind_2);
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Normal :: replicate (String& string) const
	{
		string << location_.getIndent();
		term_1_->replicate (string);
		string << space << Token :: subset_;
		string << suffix() << space;
		term_2_->replicate (string);
		/*switch (getKind()) {
		case del :: Formula :: SIMPLE_R_KIND :
			string << space << " -- SIMPLE_R_KIND" << space; break;
		case del :: Formula :: CONJ_R_KIND :
			string << space << " -- CONJ_R_KIND" << space; break;
		case del :: Formula :: LEFT_R_KIND :
			string << space << " -- LEFT_R_KIND" << space; break;
		case del :: Formula :: RIGHT_R_KIND :
			string << space << " -- RIGHT_R_KIND" << space; break;
		default :
			string << space << " -- COMPLEX_KIND" << space; break;
		}*/
	}
	/*void
	Normal :: translate (String& string) const {
		replicate (string);
	}*/

	// object :: Object implementation
	void
	Normal :: commitSuicide() {
		delete this;
	}
	Size_t
	Normal :: getVolume() const {
		return formula :: Termal :: getVolume();
	}
	Size_t
	Normal :: getSizeOf() const {
		return sizeof (Normal);
	}

	/****************************
	 *		Protected members
	 ****************************/

	const char*
	Normal :: suffix() const {
		return "n";
	}
	bool
	Normal :: nothingToDecompose (const del :: Signature* delta) const {
		return oneNonDeltaSymbol (delta);
	}

	/****************************
	 *		Private members
	 ****************************/

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

}
}
}
}
}


