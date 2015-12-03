/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_formula_subset_normal_Normal.hpp              */
/* Description:     base normal formula class                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_FORMULA_SUBSET_NORMAL_NORMAL_HPP_
#define DEL_SOURCE_FORMULA_SUBSET_NORMAL_NORMAL_HPP_

#include "del/source/formula/del_source_formula_Termal.hpp"

namespace del {
namespace source {
namespace formula {
namespace subset {
namespace normal {

class Normal : public formula :: Termal {
public :
	Normal
	(
		const Location,
		const del :: Term* const,
		const del :: Term* const,
		const del :: Formula* image = NULL,
		const bool isRoot = false,
		const bool isPrimary = false,
		const bool isDefinition = false
	);
	Normal (const del :: Formula*);
	Normal (const Normal&);
	virtual ~ Normal();

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
	virtual bool isNormal() const;
	virtual bool normalize (del :: Theory*) const;
	virtual Type getType() const;
	virtual bool hasInvalidKind() const;

	// del :: Cloneable interface
	virtual del :: Formula* clone() const = 0;

	// object :: Writable interface
	virtual void replicate (String&) const;
	//virtual void translate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

protected :
	virtual const char* suffix() const;
	bool nothingToDecompose (const del :: Signature*) const;

	bool decomposed_;
};

}
}
}
}
}

#endif /*DEL_SOURCE_FORMULA_SUBSET_NORMAL_NORMAL_HPP_*/
