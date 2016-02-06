/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_formula_equiv_Equivalence.hpp                 */
/* Description:     base class for equivalence formula                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/source/formula/del_source_formula.dpp"
#include "del/source/formula/del_source_formula_Formula.hpp"

namespace del {
namespace source {
namespace formula {
namespace equiv {

class Equivalence : public Formula {
public :
	Equivalence
	(
		const Location,
		const del :: Formula* image = NULL,
		const Kind = GENERAL_SUB_KIND,
		const bool isRoot = false,
		const bool isPrimary = false,
		const bool isDefinition = false
	);
	Equivalence (const Equivalence&);
	virtual ~ Equivalence();

	// del :: Formula interface
	virtual bool isTrivial() const;
	virtual bool isTrue (const del :: Model*) const;
	virtual bool isTrue (const del :: Model*, const set :: Formula*) const;
	virtual const del :: Term* evalInterpolant (const del :: Model*, const del :: Signature*) const;
	virtual const del :: Signature* getSignature (const bool = false) const;
	virtual bool decompose (del :: Theory*, const del :: Signature*, const bool);

	virtual bool apply (del :: Model*) const;
	virtual bool extendWithCopies (del :: Theory*, const del :: Signature*) const;

	virtual bool isNormal() const;
	virtual bool isPrimitivized() const;
	virtual void setPrimitivized (const bool = true);
	virtual bool normalize (del :: Theory*) const;
	virtual void makeDeltaCopy (const del :: Expansion*);
	virtual void makeDeltaCopy (const del :: Signature*);
	virtual bool isEqual (const del :: Formula*) const;
	virtual const del :: Term* getTerm (const value :: Integer) const;
	virtual void simplify();
	virtual bool primitivize (del :: Theory*, del :: Signature* = NULL, const bool addToTheory = true) const;
	virtual void replace (const del :: Term*, const del :: Term*);

	virtual Kind getKind() const = 0;
	virtual Type getType() const;
	virtual bool hasInvalidKind() const;

	// del :: Cloneable interface
	virtual del :: Formula* clone() const = 0;

	// del :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// del :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

protected :
	virtual const char* suffix() const;

	del :: Formula* inclusion_1_;
	del :: Formula* inclusion_2_;
};

}
}
}
}


