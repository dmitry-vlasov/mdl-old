/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_formula_subset_normal_Primitive.hpp           */
/* Description:     primitive (root) formula of a ⊑ b type                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_FORMULA_SUBSET_NORMAL_PRIMITIVE_HPP_
#define DEL_SOURCE_FORMULA_SUBSET_NORMAL_PRIMITIVE_HPP_

#include "del/source/formula/subset/normal/del_source_formula_subset_normal_Simple.hpp"

namespace del {
namespace source {
namespace formula {
namespace subset {
namespace normal {

class Primitive : public Simple {
public :
	Primitive
	(
		const Location,
		const del :: Term* const,
		const del :: Term* const,
		const del :: Formula* image = NULL,
		const bool isRoot = false,
		const bool isPrimary = false,
		const bool isDefinition = false
	);
	Primitive (const del :: Formula*);
	Primitive (const Primitive&);
	virtual ~ Primitive();

	// del :: Formula interface
	virtual bool isTrue (const del :: Model*) const;
	virtual bool isTrue (const del :: Model*, const set :: Formula*) const;
	virtual const del :: Term* evalInterpolant (const del :: Model*, const del :: Signature*) const;
	virtual Kind getKind() const;
	virtual bool primitivize (del :: Theory*, del :: Signature*) const;

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
};

}
}
}
}
}

#endif /*DEL_SOURCE_FORMULA_SUBSET_NORMAL_PRIMITIVE_HPP_*/
