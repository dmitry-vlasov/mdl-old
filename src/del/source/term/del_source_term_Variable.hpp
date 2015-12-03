/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_term_Variable.hpp                             */
/* Description:     variable term class                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_TERM_VARIABLE_HPP_
#define DEL_SOURCE_TERM_VARIABLE_HPP_

#include "del/interface/del_interface.hpp"
#include "del/source/term/del_source_term_Term.hpp"

namespace del {
namespace source {
namespace term {

class Variable :
	public del :: Term,
	public Scalar<Variable> {
public :
	Variable (const Symbol);
	Variable (const value :: Variable, const bool = false);
	Variable
	(
		const Location&,
		const value :: Variable,
		const bool = false
	);
	Variable (const Variable&);
	virtual ~ Variable();

	// del :: Term interface
	virtual void assemble();
	virtual bool normalize (del :: Theory*, const del :: Formula*) const;
	virtual bool isOfSignature (const del :: Signature*) const;
	virtual bool contains (const Symbol&) const;
	virtual void completeSignature (del :: Signature*) const;
	virtual void makeDeltaCopy (const del :: Expansion*);
	virtual void makeDeltaCopy (const del :: Signature*);
	virtual value :: Integer getSize() const;
	virtual const del :: Symbol& getSymbol() const;
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
	virtual Symbol primitivize (const char* suffix) const;
	virtual Symbol getPrimitivization() const;
	virtual bool hasTemporarySymbols() const;
	virtual Kind getKind() const;
	virtual Symbol defineSelf
	(
		del :: Theory*,
		const del :: Formula*,
		const char*,
		const bool = false
	) const;

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
	del :: Symbol symbol_;
};

}
}
}

#endif /*DEL_SOURCE_TERM_VARIABLE_HPP_*/
