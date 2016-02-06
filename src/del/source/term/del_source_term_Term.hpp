/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_term_Term.hpp                                 */
/* Description:     base term class                                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface.hpp"
#include "del/source/del_source.dpp"

namespace del {
namespace source {
namespace term {

class Term : public del :: Term {
public :
	Term (const Location&);
	Term (const Location&, const del :: Term*);
	Term (const Location&, const vector :: Term&);
	Term (const vector :: Term&);
	Term (const del :: Term*[], const value :: Integer);
	Term (const del :: Term*);
	Term (const Term&);
	virtual ~ Term();

	static del :: Term* createRandom (const del :: Signature*);
	void addSubterm (const del :: Term*);
	static void replace (del :: Term*&, const del :: Term*, const del :: Term*);

	// del :: Term interface
	virtual void assemble();
	virtual bool normalize (del :: Theory*, const del :: Formula*) const;
	virtual bool isOfSignature (const del :: Signature*) const;
	virtual bool contains (const del :: Symbol&) const;
	virtual void makeDeltaCopy (const del :: Expansion*);
	virtual void makeDeltaCopy (const del :: Signature*);
	virtual void completeSignature (del :: Signature*) const;
	virtual value :: Integer getSize() const;
	virtual const del :: Symbol& getSymbol() const = 0;
	virtual const del :: Term* getSubterm (const value :: Integer = 0) const;
	virtual bool isEqual (const del :: Term*) const;
	virtual const del :: Term* simplify();
	virtual void replace (const del :: Term*, const del :: Term*);
	virtual void replaceSubterm (const value :: Integer, const del :: Term*);
	virtual void removeSubterm (const value :: Integer);
	virtual value :: Integer getDepth() const;
	virtual value :: Integer getLength() const;

	virtual bool isPrimitivized() const;
	virtual void setPrimitivized (const bool = true) const;
	virtual Symbol primitivize (const char* suffix) const = 0;
	virtual Symbol getPrimitivization() const;
	virtual bool hasTemporarySymbols() const;
	virtual Kind getKind() const = 0;
	virtual Symbol defineSelf
	(
		del :: Theory*,
		const del :: Formula*,
		const char* suffix,
		const bool inNormalFormula = false
	) const;

	// del :: Cloneable interface
	virtual del :: Term* clone() const = 0;

	// object :: Writable interface
	virtual void translate (String&) const = 0;
	virtual void replicate (String&) const = 0;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

protected :
	bool isSubset (const del :: Term*, const del :: Term*) const;
	static del :: Term* createRandom
	(
		const del :: Signature*,
		const value :: Integer size,
		const value :: Integer depth
	);
	static del :: Term* createRandomSizeOne (const del :: Signature*);
	static del :: Term* createRandomSizeTwo (const del :: Signature*);
	static del :: Term* createRandomSizeThree
	(
		const del :: Signature*,
		const value :: Integer depth
	);
	static del :: Term* createRandomSizeFourOrMore
	(
		const del :: Signature*,
		const value ::Integer size,
		const value :: Integer depth
	);

	const Location location_;
	vector :: Term terms_;
	mutable Symbol primitivization_;
};

}
}
}


