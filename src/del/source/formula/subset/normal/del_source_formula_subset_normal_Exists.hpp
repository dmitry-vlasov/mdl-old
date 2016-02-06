/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_formula_subset_normal_Exists.hpp              */
/* Description:     simple formula of a ⊑ ∃r.b or ∃r.a ⊑ b type              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/source/formula/subset/normal/del_source_formula_subset_normal_Normal.hpp"

namespace del {
namespace source {
namespace formula {
namespace subset {
namespace normal {

class Exists : public Normal {
public :
	Exists
	(
		const Location,
		const del :: Term* const,
		const del :: Term* const,
		const del :: Formula* image = NULL,
		const bool isRoot = false,
		const bool isPrimary = false,
		const bool isDefinition = false
	);
	Exists (const del :: Formula*);
	Exists (const Exists&);
	virtual ~ Exists();

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

protected :
	bool splitExists (del :: Theory*, const del :: Signature*, const del :: Term*&);

private :

	del :: Signature* prepareDelta (const del :: Signature*, const del :: Term*) const;
	del :: Theory* prepareTheory (del :: Theory*, const del :: Signature*, const del :: Term*) const;
	del :: Formula* prepareFormula (del :: Theory*, const del :: Signature*, const del :: Term*) const;

	bool splitExistsNew (del :: Theory*, const del :: Signature*, const del :: Term*&);
	bool splitExistsMed (del :: Theory*, const del :: Signature*, const del :: Term*&);
	bool splitExistsOld (del :: Theory*, const del :: Signature*, const del :: Term*&);

	/*const value :: Relation r_;
	const value :: Variable a_;
	const value :: Variable b_;*/
};

}
}
}
}
}


