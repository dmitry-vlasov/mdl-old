/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_formula_equiv_Identity.cpp                    */
/* Description:     identity formula class                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_FORMULA_EQUIV_IDENTITY_CPP_
#define DEL_SOURCE_FORMULA_EQUIV_IDENTITY_CPP_

#include "del/lexer/del_lexer.hpp"

namespace del {
namespace source {
namespace formula {
namespace equiv {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Identity :: Identity
	(
		const Location location,
		const del :: Term* const term_1,
		const del :: Term* const term_2,
		const del :: Formula* image,
		const bool isRoot,
		const bool isPrimary,
		const bool isDefinition
	) :
	Equivalence
	(
		location,
		((image == NULL) ? this : image),
		GENERAL_SUB_KIND,
		isRoot,
		isPrimary,
		isDefinition
	)
	{
		inclusion_1_ = new Subset
		(
			location,
			term_1,
			term_2,
			image,
			GENERAL_SUB_KIND,
			isRoot,
			isPrimary,
			isDefinition
		);
		inclusion_2_ = new Subset
		(
			location,
			term_2->clone(),
			term_1->clone(),
			image,
			GENERAL_SUB_KIND,
			isRoot,
			isPrimary,
			isDefinition
		);
	}
	inline
	Identity :: Identity (const Identity& identity) :
	Equivalence (identity) {
	}
	Identity :: ~ Identity() {
	}

	del :: Formula*
	Identity :: create
	(
		const del :: Term* const term_1,
		const del :: Term* const term_2,
		const del :: Formula* image ,
		const bool isRoot,
		const bool isPrimary,
		const bool isDefinition
	) {
		return new Identity (Location(), term_1, term_2, image, isRoot, isPrimary, isDefinition);
	}

	// del :: Formula implementation
	const del :: Term*
	Identity :: evalInterpolant (const del :: Model*, const del :: Signature*) const {
		throw new Error();
	}
	bool
	Identity :: decompose (del :: Theory*, const del :: Signature*, const bool) {
		throw new Error();
	}
	bool
	Identity :: isNormal() const {
		return false;
	}
	bool
	Identity :: normalize (del :: Theory* theory) const {
		return Equivalence :: normalize (theory);
	}
	del :: Formula :: Kind
	Identity :: getKind() const {
		return IDENTITY_EQ_KIND;
	}

	// del :: Cloneable implementation
	del :: Formula*
	Identity :: clone() const {
		return new Identity (*this);
	}

	// object :: Object implementation
	void
	Identity :: commitSuicide() {
		delete this;
	}
	Size_t
	Identity :: getVolume() const {
		return Equivalence :: getVolume();
	}
	Size_t
	Identity :: getSizeOf() const {
		return sizeof (Identity);
	}

	/****************************
	 *		Protected members
	 ****************************/

	const char*
	Identity :: suffix() const {
		return ""; // return "i";
	}
}
}
}
}

#endif /*DEL_SOURCE_FORMULA_EQUIV_IDENTITY_CPP_*/
