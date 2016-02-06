/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_term_Exists.hpp                               */
/* Description:     exists term class                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface.hpp"
#include "del/source/term/del_source_term_Term.hpp"

namespace del {
namespace source {
namespace term {

class Exists :
	public Term,
	public Scalar<Exists> {
public :
	Exists
	(
		const Location&,
		const value :: Relation,
		const vector :: Term&
	);
	Exists
	(
		const Location&,
		const value :: Relation,
		const del :: Term*
	);
	Exists
	(
		const value :: Relation,
		const del :: Term*
	);
	Exists
	(
		const del :: Symbol,
		const del :: Term*
	);
	Exists (const Exists&);
	virtual ~ Exists();

	// del :: Term interface
	virtual bool isOfSignature (const del :: Signature*) const;
	virtual bool contains (const Symbol&) const;
	virtual void completeSignature (del :: Signature*) const;
	virtual void makeDeltaCopy (const del :: Expansion*);
	virtual void makeDeltaCopy (const del :: Signature*);
	virtual const del :: Symbol& getSymbol() const;
	virtual bool isEqual (const del :: Term*) const;
	virtual const del :: Term* simplify();
	virtual void replace (const del :: Term*, const del :: Term*);
	virtual value :: Integer getDepth() const;
	virtual value :: Integer getLength() const;

	virtual Symbol primitivize (const char* suffix) const;
	virtual bool hasTemporarySymbols() const;
	virtual Kind getKind() const;

	// del :: Cloneable interface
	virtual del :: Term* clone() const;

	// object :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	const Location location_;
	Symbol symbol_;
};

}
}
}


