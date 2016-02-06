/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_formula_subset_normal_LeftExists.hpp          */
/* Description:     simple formula of ∃r.a ⊑ b type                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/source/formula/subset/normal/del_source_formula_subset_normal_Exists.hpp"

namespace del {
namespace source {
namespace formula {
namespace subset {
namespace normal {

class LeftExists :
	public Exists,
	public Scalar<LeftExists> {
public :
	LeftExists
	(
		const Location,
		const del :: Term* const,
		const del :: Term* const,
		const del :: Formula* image = NULL,
		const bool isRoot = false,
		const bool isPrimary = false,
		const bool isDefinition = false
	);
	LeftExists (const del :: Formula*);
	LeftExists (const LeftExists&);
	virtual ~ LeftExists();

	// del :: Formula interface
	virtual bool decompose (del :: Theory*, const del :: Signature*, const bool);
	virtual bool apply (del :: Model*) const;
	virtual bool extendWithCopies (del :: Theory*, const del :: Signature*) const;
	virtual Kind getKind() const;

	// del :: Cloneable interface
	virtual del :: Formula* clone() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
};

}
}
}
}
}


