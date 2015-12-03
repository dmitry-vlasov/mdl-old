/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_term_Intersect.hpp                            */
/* Description:     exists term class                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_TERM_INTERSECT_HPP_
#define DEL_SOURCE_TERM_INTERSECT_HPP_

#include "del/interface/del_interface.hpp"
#include "del/source/term/del_source_term_Term.hpp"

namespace del {
namespace source {
namespace term {

class Intersect :
	public Term,
	public Scalar<Intersect> {
public :
	Intersect (const Location&);
	Intersect
	(
		const Location&,
		const vector :: Term&
	);
	Intersect (const vector :: Term&);
	Intersect (const del :: Term*[], const value :: Integer);
	Intersect (const Intersect&);
	virtual ~ Intersect();

	void addTerm (const del :: Term*);

	// del :: Term interface
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
	bool isPlain() const;
	bool isNonTop() const;
	void becomePlain();
	void removeTop();
	void removeRedundant();
	bool contains (const vector :: Term&, const del :: Term*) const;
	void clearTerms();
};

}
}
}

#endif /*DEL_SOURCE_TERM_INTERSECT_HPP_*/
