/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_formula_equiv_Definition.cpp                  */
/* Description:     definition formula class                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_FORMULA_EQUIV_DEFINITION_CPP_
#define DEL_SOURCE_FORMULA_EQUIV_DEFINITION_CPP_

#include "del/lexer/del_lexer.hpp"

namespace del {
namespace source {
namespace formula {
namespace equiv {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Definition :: Definition
	(
		const Location location,
		const del :: Term* const term_1,
		const del :: Term* const term_2,
		const del :: Formula* image
	) :
	Equivalence
	(
		location,
		((image == NULL) ? this : image),
		GENERAL_SUB_KIND,
		false,
		false
	)
	{
		inclusion_1_ = new Subset
		(
			location,
			term_1,
			term_2,
			image,
			GENERAL_SUB_KIND,
			false,
			false,
			true
		);
		inclusion_2_ = new Subset
		(
			location,
			term_2->clone(),
			term_1->clone(),
			image,
			GENERAL_SUB_KIND,
			false,
			false,
			true
		);
	}
	inline
	Definition :: Definition (const Definition& definition) :
	Equivalence (definition) {
	}
	Definition :: ~ Definition() {
	}

	const del :: Term*
	Definition :: getDefiendum() const
	{
		if (inclusion_1_->getTerm (0)->getKind() == del :: Term :: VARIABLE_KIND) {
			return inclusion_1_->getTerm (0);
		} else {
			return inclusion_1_->getTerm (1);
		}
	}
	const del :: Term*
	Definition :: getDefiniens() const
	{
		if (inclusion_1_->getTerm (0)->getKind() == del :: Term :: VARIABLE_KIND) {
			return inclusion_1_->getTerm (1);
		} else {
			return inclusion_1_->getTerm (0);
		}
	}

	// del :: Formula implementation
	bool
	Definition :: normalize (del :: Theory* theory) const {
		return Equivalence :: normalize (theory);
	}
	Definition :: Kind
	Definition :: getKind() const {
		return DEFINITION_EQ_KIND;
	}

	// del :: Cloneable implementation
	del :: Formula*
	Definition :: clone() const {
		return new Definition (*this);
	}

	// object :: Object implementation
	void
	Definition :: commitSuicide() {
		delete this;
	}
	Size_t
	Definition :: getVolume() const {
		return Equivalence :: getVolume();
	}
	Size_t
	Definition :: getSizeOf() const {
		return sizeof (Definition);
	}

	/****************************
	 *		Protected members
	 ****************************/

	const char*
	Definition :: suffix() const {
		return "d";
	}
}
}
}
}

#endif /*DEL_SOURCE_FORMULA_EQUIV_DEFINITION_CPP_*/
