/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_formula_subset_normal_Conjunction.hpp         */
/* Description:     simple formula of a_1 ⊓  ... ⊓ a_n ⊑ b type               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_FORMULA_SUBSET_NORMAL_CONJUNCTION_HPP_
#define DEL_SOURCE_FORMULA_SUBSET_NORMAL_CONJUNCTION_HPP_

#include "del/source/formula/subset/normal/del_source_formula_subset_normal_Normal.hpp"

namespace del {
namespace source {
namespace formula {
namespace subset {
namespace normal {

class Conjunction :
	public Normal,
	public Scalar<Conjunction> {
public :
	Conjunction
	(
		const Location,
		const del :: Term*,
		const del :: Term*,
		const del :: Formula* = NULL,
		const bool isRoot = false,
		const bool isPrimary = false,
		const bool isDefinition = false
	);
	Conjunction (const del :: Formula*);
	Conjunction (const Conjunction&);
	virtual ~ Conjunction();

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

private :
	enum {
		INITIAL_INDEX_SET_CAPACITY = 16
	};
	typedef
		set :: Set
		<
			value :: Integer,
			storage :: ByValue,
			allocator :: Stack
		>
		IndexSet_;

	bool splitConj (del :: Theory*, const del :: Signature*);

	del :: Signature* prepareDelta (const del :: Signature*, IndexSet_&) const;
	del :: Theory* prepareTheory (del :: Theory*, const del :: Signature*) const;
	del :: Formula* prepareFormula (del :: Theory*, const del :: Signature*) const;

	void findDeltaIndexes (del :: Theory*, const del :: Signature*, IndexSet_&);

	bool indexesAreDelta (del :: Theory*, const del :: Signature*, IndexSet_&);
	bool indexesAreDeltaNew (del :: Theory*, const del :: Signature*, IndexSet_&);
	bool indexesAreDeltaOld (del :: Theory*, const del :: Signature*, IndexSet_&);

	const del :: Term* findIndexSetInterpolant (del :: Theory*, const del :: Signature*, IndexSet_&);
	const del :: Term* findIndexSetInterpolantNew (del :: Theory*, const del :: Signature*, IndexSet_&);
	const del :: Term* findIndexSetInterpolantOld (del :: Theory*, const del :: Signature*, IndexSet_&);

	void removeIndexSet (const del :: Signature*, IndexSet_&);
};

}
}
}
}
}

#endif /*DEL_SOURCE_FORMULA_SUBSET_NORMAL_CONJUNCTION_HPP_*/
