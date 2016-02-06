/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_Signature.hpp                                 */
/* Description:     signature class                                          */
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

template<class A>
class Signature :
	public del :: Signature,
	public Scalar<Signature<A>, A> {
public :
	typedef A Allocator_;
	Signature ();
	Signature (const value :: Signature);
	Signature
	(
		const Location&,
		const del :: Comments* const,
		const value :: Signature
	);
	Signature (const Signature&);
	Signature (const del :: Signature*);
	virtual ~ Signature();

	static Signature* createRandom ();
	static Signature* createRandom (const value :: Integer, const value :: Integer);

	// del :: Signature interface
	virtual value :: Integer getSize() const;
	virtual bool isEqual (const del :: Signature*) const;
	virtual bool isSubset (const del :: Signature*) const;
	virtual void copy (const del :: Signature*);
	virtual void clear();
	virtual value :: Signature getName() const;
	virtual void setName (const value :: Signature);
	virtual value :: Integer cardinality() const;
	virtual const del :: Symbol& getSymbol (const value :: Integer = 0) const;
	virtual const del :: Symbol& getRandomSymbol() const;
	virtual const del :: Symbol& getRandomConcept() const;
	virtual const del :: Symbol& getRandomRelation() const;

	virtual void makeDeltaCopy (const del :: Expansion*);
	virtual bool containsSymbol (const del :: Symbol&) const;
	virtual void addSymbol (const del :: Symbol&);
	virtual void removeSymbol (const del :: Symbol&);
	virtual void intersect (const del :: Signature*);
	virtual void join (const del :: Signature*);
	virtual void subtract (const del :: Signature*);

	// del :: Cloneable interface
	virtual del :: Signature* clone() const;

	// Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// del :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	typedef
		set :: Set
		<
			del :: Symbol,
			storage :: ByValue,
			Allocator_
		>
		Symbols_;

	const Location location_;
	const del :: Comments* const comments_;
	value :: Signature name_;
	Symbols_ symbols_;

	enum {
		INITIAL_SYMBOLS_CAPACITY   = 256
	};
};

}
}


