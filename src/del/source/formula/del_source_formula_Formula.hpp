/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_formula_Formula.hpp                           */
/* Description:     general formula class                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_FORMULA_FORMULA_HPP_
#define DEL_SOURCE_FORMULA_FORMULA_HPP_

#include "del/interface/del_interface.hpp"

namespace del {
namespace source {
namespace formula {

class Formula : public del :: Formula {
public :
	Formula
	(
		const Location,
		const del :: Formula* image = NULL,
		const Kind = GENERAL_SUB_KIND,
		const bool isRoot = false,
		const bool isPrimary = false,
		const bool isDefinition = false
	);
	Formula (const del :: Formula*);
	Formula (const Formula&);
	virtual ~ Formula();

	static del :: Formula* createRandom (const del :: Signature*);

	// del :: Formula interface
	virtual bool isTrue (const del :: Model*) const = 0;
	virtual bool isTrue (const del :: Model*, const set :: Formula*) const = 0;
	virtual const del :: Term* evalInterpolant (const del :: Model*, const del :: Signature*) const = 0;
	virtual const del :: Signature* getSignature (const bool = false) const;
	virtual bool isConnected (const del :: Symbol&) const;
	virtual bool decompose (del :: Theory*, const del :: Signature*, const bool) = 0;

	virtual bool apply (del :: Model*) const = 0;
	virtual bool extendWithCopies (del :: Theory*, const del :: Signature*) const = 0;

	virtual bool isRoot() const;
	virtual bool isPrimary() const;
	virtual bool isDefinition() const;
	virtual bool isPrimitivized() const = 0;
	virtual void setRoot (const bool = true);
	virtual void setPrimary (const bool = true);
	virtual void setDefinition (const bool = true);
	virtual void setPrimitivized (const bool = true) = 0;

	virtual bool isNormal() const = 0;
	virtual bool normalize (del :: Theory*) const = 0;
	virtual void makeDeltaCopy (const del :: Expansion*) = 0;
	virtual void makeDeltaCopy (const del :: Signature*) = 0;
	virtual bool isEqual (const del :: Formula*) const;
	virtual const del :: Term* getTerm (const value :: Integer) const = 0;
	virtual void simplify() = 0;
	virtual bool primitivize (del :: Theory*, del :: Signature* = NULL, const bool addToTheory = true) const = 0;
	virtual void replace (const del :: Term*, const del :: Term*) = 0;
	virtual const del :: Formula* getImage() const;
	virtual void setImage (const del :: Formula*);

	virtual const Location& getLocation() const;

	virtual Kind getKind() const = 0;
	virtual Type getType() const = 0;
	virtual bool hasInvalidKind() const = 0;

	// del :: Cloneable interface
	virtual del :: Formula* clone() const = 0;

	// object :: Writable interface
	virtual void translate (String&) const = 0;
	virtual void replicate (String&) const = 0;
	virtual void show (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

protected :
	friend class source :: Theory;

	bool oneNonDeltaSymbol (const del :: Signature*) const;

	const Location location_;
	mutable del :: Signature* signature_;
	mutable Kind kind_;
	mutable const del :: Formula* image_;
	mutable bool isRoot_;
	mutable bool isPrimary_;
	mutable bool isDefinition_;
};

}
}
}

#endif /*DEL_SOURCE_FORMULA_FORMULA_HPP_*/
