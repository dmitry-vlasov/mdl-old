/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_Theory.hpp                                    */
/* Description:     contents of a theory                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface.hpp"

namespace del {
namespace source {

class Theory :
	public del :: Theory,
	public Scalar<Theory> {
public :
	Theory();
	Theory
	(
		const value :: Theory name,
		const bool isForOutput = false
	);
	Theory
	(
		const Location&,
		const del :: Comments* const,
		const value :: Theory name,
		const bool isForOutput = false
	);
	Theory (const Theory&);
	Theory (const Theory&, const value :: Integer);
	virtual ~ Theory();

	static Theory* createRandom (const del :: Signature*);
	static Theory* createRandom
	(
		const del :: Signature*,
		const value :: Integer size
	);

	// del :: Theory interface
	virtual const Writable* translate() const;
	virtual void extendWithCopies (const del :: Signature*);
	virtual void repair();
	virtual void assemble (const del :: Signature*);
	virtual const del :: Signature* computeDelta (const value :: Integer) const;

	virtual bool isEqual (const del :: Theory*) const;
	virtual bool isEquivalent (const del :: Theory*, const bool showDifference) const;
	virtual bool entails (const del :: Theory*, const bool showDifference) const;
	virtual bool entails (const del :: Formula*, const bool showDifference) const;

	virtual const del :: Signature* getSignature (const bool = false) const;
	virtual value :: Theory getName() const;
	virtual void setName (const value :: Theory);

	virtual void primitivize (del :: Signature* = NULL);
	virtual void normalize();
	virtual void minimize();
	virtual void decompose (const del :: Signature*);

	virtual void makeDeltaCopy (const del :: Expansion*);
	virtual void makeDeltaCopy (const del :: Signature*);
	virtual void addFormula (const del :: Formula* const);
	virtual void removeFormula (const del :: Formula*);
	virtual bool containsFormula (const del :: Formula*) const;
	virtual void deleteFormula (const value :: Integer);
	virtual value :: Integer getSize() const;
	virtual const del :: Formula* getFormula (const value :: Integer) const;
	virtual void replaceTerm (const del :: Term*, const del :: Term*);
	virtual void unite (const del :: Theory*, const bool removeDuplicateFormulas = true);
	virtual bool isNormal() const;
	virtual bool isMinimal() const;
	virtual bool isPrimitive() const;
	virtual bool isDecomposed() const;
	virtual bool isAssembled() const;
	virtual bool isForOutput() const;
	virtual void showDifference (const del :: Theory*) const;

	// del :: Cloneable interface
	virtual del :: Theory* clone() const;

	// del :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;
	virtual void show (String&) const;

	// del :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	friend class Decompose;

	// primitivization routines
	void primitivizeFormulas (del :: Signature*);

	// normalization routines
	void normalizeFormulas();
	void transformFormulas();

	// decomposition routines
	void primaryDecomposition (const del :: Signature*);
	void secondaryDecomposition (const del :: Signature*);

	// assembling routines
	bool assembleConjunctions (const bool inDefinitions);
	bool assembleConjunctions (const bool inDefinitions, del :: Formula*, del :: Formula*);
	bool assembleEqualities (const bool inDefinitions);
	bool assembleEqualities (const bool inDefinitions, del :: Formula*, del :: Formula*);
	void denormalizeFormulas();
	void removeRedundant (const bool findDuplicate = true, const bool findConjTautology = true);
	void assembleTheoryFirst();
	bool assembleTheorySecond (const del :: Signature*, const bool);

	bool contains (const del :: Formula*) const;
	value :: Integer computeCohesion (const Symbol) const;

	void slowMinimization (const bool debug = false);
	void fastMinimization();
	void primitivizationAtMinimization (del :: Theory*);
	void normalizationAtMinimization (del :: Theory*);
	del :: Model* buildAModelAtMinimization (del :: Theory*);
	set :: Formula* redundancyAtMinimization (del :: Theory*, del :: Model*);
	void removeRedundantFormulas (set :: Formula* redundant);


	void fastPartialMinimization (const bool debug = false);
	void testMinimization (const value :: Integer factor);

	void findConjunctiveIndexes (const value :: Integer, value :: Integer [], value :: Integer&);
	void useConjunctiveIndexes (const value :: Integer, const value :: Integer [], const value :: Integer);
	bool isEquivalence (const del :: Formula*, const del :: Formula*);
	bool createEquivalence (const value :: Integer, const value :: Integer);

	void reverseFormulas();

	// translation routines
	const Writable* translateToManFormat() const;
	const Writable* translateToFuncFormat() const;

	enum {
		INITIAL_FORMULAE_CAPACITY = 1024
	};

	const Location location_;
	const del :: Comments* comments_;
	value :: Theory name_;
	vector :: Formula formulae_;
	mutable const del :: Signature* signature_;
	bool isNormal_;
	bool isMinimal_;
	bool isPrimitive_;
	bool isDecomposed_;
	bool isAssembled_;
	bool isForOutput_;
};

}
}


