/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_formula_equiv_Primitive.cpp                   */
/* Description:     definition formula class                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_FORMULA_EQUIV_PRIMITIVE_CPP_
#define DEL_SOURCE_FORMULA_EQUIV_PRIMITIVE_CPP_

#include "del/lexer/del_lexer.hpp"

namespace del {
namespace source {
namespace formula {
namespace equiv {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Primitive :: Primitive
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
		inclusion_1_ = new formula :: subset :: normal :: Primitive
		(
			location,
			term_1,
			term_2,
			image,
			isRoot,
			isPrimary,
			isDefinition
		);
		inclusion_2_ = new formula :: subset :: normal :: Primitive
		(
			location,
			term_2->clone(),
			term_1->clone(),
			image,
			isRoot,
			isPrimary,
			isDefinition
		);
	}
	inline
	Primitive :: Primitive (const Primitive& definition) :
	Equivalence (definition) {
	}
	Primitive :: ~ Primitive() {
	}

	// del :: Formula implementation
	bool
	Primitive :: isTrue (const del :: Model*) const {
		throw new Error();
	}
	bool
	Primitive :: isTrue (const del :: Model*, const set :: Formula*) const {
		throw new Error();
	}
	bool
	Primitive :: normalize (del :: Theory* theory) const {
		return false;
	}
	Primitive :: Kind
	Primitive :: getKind() const {
		return PRIMITIVE_EQ_KIND;
	}

	// del :: Cloneable implementation
	del :: Formula*
	Primitive :: clone() const {
		return new Primitive (*this);
	}

	// object :: Object implementation
	void
	Primitive :: commitSuicide() {
		delete this;
	}
	Size_t
	Primitive :: getVolume() const {
		return Equivalence :: getVolume();
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

#endif /*DEL_SOURCE_FORMULA_EQUIV_PRIMITIVE_CPP_*/
