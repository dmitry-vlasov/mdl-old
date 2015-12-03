/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_Term.hpp                                   */
/* Description:     abstract interfaces for del theory                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_TERM_HPP_
#define MDL_INTERFACE_TERM_HPP_

#include "del/interface/del_interface_Cloneable.hpp"
#include "del/interface/del_interface_Writable.hpp"

namespace del {
namespace interface {

class Term :
	public Writable,
	public Cloneable<Term> {
public :
	virtual void assemble() = 0;
	virtual bool normalize (Theory*, const Formula*) const = 0;
	virtual bool isOfSignature (const Signature*) const = 0;
	virtual bool contains (const Symbol&) const = 0;
	virtual void completeSignature (Signature*) const = 0;
	virtual void makeDeltaCopy (const Expansion*) = 0;
	virtual void makeDeltaCopy (const Signature*) = 0;

	virtual value :: Integer getSize() const = 0;
	virtual const Symbol& getSymbol() const = 0;
	virtual const Term* getSubterm (const value :: Integer = 0) const = 0;
	virtual bool isEqual (const Term*) const = 0;
	virtual const Term* simplify() = 0;
	virtual void replace (const Term*, const Term*) = 0;
	virtual void replaceSubterm (const value :: Integer, const Term*) = 0;
	virtual void removeSubterm (const value :: Integer) = 0;
	virtual value :: Integer getDepth() const = 0;
	virtual value :: Integer getLength() const = 0;

	// represent self as a unique primitive term
	virtual bool isPrimitivized() const = 0;
	virtual void setPrimitivized (const bool = true) const = 0;
	virtual Symbol primitivize (const char* suffix) const = 0;
	virtual Symbol getPrimitivization() const = 0;
	virtual bool hasTemporarySymbols() const = 0;
	enum Kind {
		VARIABLE_KIND,
		INTERSECT_KIND,
		EXISTS_KIND,
		TOP_KIND
	};
	virtual Kind getKind() const = 0;
	virtual Symbol defineSelf
	(
		Theory*,
		const Formula*,
		const char* suffix,
		const bool inNormalFormula = false
	) const = 0;

	enum Type {
		ATOMIC_TYPE,
		DEEP_TYPE
	};
	bool isAtomic() const {
		return (getDepth() == 0);
	}
	bool isDeep() const {
		return (getDepth() > 1);
	}
	Type getType() const
	{
		if (isAtomic()) {
			return ATOMIC_TYPE;
		} else {
			return DEEP_TYPE;
		}
	}
};

}
}

#endif /*MDL_INTERFACE_TERM_HPP_*/
