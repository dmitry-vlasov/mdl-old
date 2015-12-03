/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_formula_subset_Subset.hpp                     */
/* Description:     subset formula class                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_FORMULA_SUBSET_SUBSET_HPP_
#define DEL_SOURCE_FORMULA_SUBSET_SUBSET_HPP_

#include "del/source/formula/del_source_formula_Termal.hpp"

namespace del {
namespace source {
namespace formula {
namespace subset {

class Subset :
	public Termal,
	public Scalar<Subset> {
public :
	Subset
	(
		const del :: Term* const,
		const del :: Term* const,
		const del :: Formula* = NULL,
		const Kind = GENERAL_SUB_KIND,
		const bool isRoot = false,
		const bool isPrimary = false,
		const bool isDefinition = false
	);
	Subset
	(
		const Location,
		const del :: Term* const,
		const del :: Term* const,
		const del :: Formula* = NULL,
		const Kind = GENERAL_SUB_KIND,
		const bool isRoot = false,
		const bool isPrimary = false,
		const bool isDefinition = false
	);
	Subset (const del :: Formula*);
	Subset (const Subset&);
	virtual ~ Subset();

	static del :: Formula* createTautology (const del :: Symbol&);
	static del :: Formula* create
	(
		const del :: Term* const,
		const del :: Term* const,
		const del :: Formula* = NULL,
		const bool isRoot = false,
		const bool isPrimary = false,
		const bool isDefinition = false
	);

	// del :: Formula interface
	virtual bool isTrivial() const;
	virtual bool isTrue (const del :: Model*) const;
	virtual bool isTrue (const del :: Model*, const set :: Formula*) const;
	virtual const del :: Term* evalInterpolant (const del :: Model*, const del :: Signature*) const;
	virtual bool decompose (del :: Theory*, const del :: Signature*, const bool);

	virtual bool apply (Model*) const;
	virtual bool extendWithCopies (del :: Theory*, const del :: Signature*) const;

	virtual bool isNormal() const;
	virtual bool normalize (del :: Theory*) const;
	virtual Type getType() const;
	virtual bool hasInvalidKind() const;

	// del :: Cloneable interface
	virtual del :: Formula* clone() const;

	// object :: Writable interface
	virtual void replicate (String&) const;
	virtual void translate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

protected :
	virtual const char* suffix() const;

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

	// normalization routines
	bool normalizeIntersection (del :: Theory*) const;
	bool normalizeInclusion (del :: Theory*) const;

	// theory decomposition routines: split and fictivize
	bool splitFormula (del :: Theory*, const del :: Signature*);
	bool splitConj (del :: Theory*, const del :: Signature*);
	void findDeltaIndexes (del :: Theory*, const del :: Signature*, IndexSet_&);
	bool indexesAreDelta (del :: Theory*, const del :: Signature*, IndexSet_&);
	const del :: Term* findIndexSetInterpolant (del :: Theory*, const del :: Signature*, IndexSet_&);
	bool splitExists (del :: Theory*, const del :: Signature*, const del :: Term*);
	void insertInterpolant (del :: Theory*, const del :: Term*) const;
	void removeIndexSet (const del :: Signature*, IndexSet_&);
};

}
}
}
}

#endif /*DEL_SOURCE_FORMULA_SUBSET_SUBSET_HPP_*/
