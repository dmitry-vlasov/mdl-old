/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_formula_Termal.hpp                            */
/* Description:     formula with a pair of terms                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_FORMULA_TERMAL_HPP_
#define DEL_SOURCE_FORMULA_TERMAL_HPP_

#include "del/source/formula/del_source_formula_Formula.hpp"

namespace del {
namespace source {
namespace formula {

class Termal : public Formula {
public :
	Termal
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
	Termal (const del :: Formula*);
	Termal (const Termal&);
	virtual ~ Termal();

	// del :: Formula interface
	virtual bool isTrue (const del :: Model*) const = 0;
	virtual bool isTrue (const del :: Model*, const set :: Formula*) const = 0;
	virtual const del :: Term* evalInterpolant (const del :: Model*, const del :: Signature*) const = 0;
	virtual const del :: Signature* getSignature (const bool = false) const;
	virtual bool decompose (del :: Theory*, const del :: Signature*, const bool) = 0;

	virtual bool apply (del :: Model*) const = 0;
	virtual bool extendWithCopies (del :: Theory*, const del :: Signature*) const = 0;

	virtual bool isNormal() const = 0;
	virtual bool isPrimitivized() const;
	virtual void setPrimitivized (const bool = true);
	virtual bool normalize (del :: Theory*) const = 0;
	virtual void makeDeltaCopy (const del :: Expansion*);
	virtual void makeDeltaCopy (const del :: Signature*);
	virtual bool isEqual (const del :: Formula*) const;
	virtual const del :: Term* getTerm (const value :: Integer) const;
	virtual void simplify();
	virtual bool primitivize (del :: Theory*, del :: Signature* = NULL, const bool addToTheory = true) const;
	virtual void replace (const del :: Term*, const del :: Term*);

	virtual Kind getKind() const;
	virtual Type getType() const = 0;

	// del :: Cloneable interface
	virtual del :: Formula* clone() const = 0;

	// object :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const = 0;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

protected :
	friend class source :: Theory;

	const del :: Term* term_1_;
	const del :: Term* term_2_;

private :
	bool isSimpleR() const;
	bool isConjR() const;
	bool isRightR() const;
	bool isLeftR() const;

	Symbol prepareTerm
	(
		const del :: Term* complexTerm,
		del :: Theory* theory,
		del :: Signature* delta
	) const;
};

}
}
}

#endif /*DEL_SOURCE_FORMULA_TERMAL_HPP_*/
