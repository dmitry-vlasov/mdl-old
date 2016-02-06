/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_Formula.hpp                                */
/* Description:     abstract interfaces for del theory                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface_Cloneable.hpp"
#include "del/interface/del_interface_Writable.hpp"
#include "del/interface/del_interface_Term.hpp"

namespace del {
namespace interface {

class Formula :
	public Writable,
	public Cloneable<Formula> {
public :
	//virtual void assemble() = 0;
	virtual bool isTrivial() const = 0;
	virtual bool isTrue (const Model*) const = 0;
	virtual bool isTrue (const Model*, const set :: Formula*) const = 0;
	virtual const Term* evalInterpolant (const Model*, const Signature*) const = 0;
	virtual const Signature* getSignature (const bool = false) const = 0;
	virtual bool isConnected (const Symbol&) const = 0;
	virtual bool decompose (Theory*, const Signature*, const bool) = 0;

	virtual bool apply (Model*) const = 0;
	virtual bool extendWithCopies (Theory*, const Signature*) const = 0;

	// state
	virtual bool isRoot() const = 0;
	virtual bool isPrimary() const = 0;
	virtual bool isDefinition() const = 0;
	virtual bool isPrimitivized() const = 0;
	virtual void setRoot (const bool = true) = 0;
	virtual void setPrimary (const bool = true) = 0;
	virtual void setDefinition (const bool = true) = 0;
	virtual void setPrimitivized (const bool = true) = 0;

	// main normalization procedures
	virtual bool isNormal() const = 0;
	virtual bool normalize (Theory*) const = 0;
	virtual void makeDeltaCopy (const Expansion*) = 0;
	virtual void makeDeltaCopy (const Signature*) = 0;

	virtual bool isEqual (const Formula*) const = 0;
	virtual const Term* getTerm (const value :: Integer) const = 0;
	virtual void simplify() = 0;
	virtual bool primitivize (Theory*, Signature* = NULL, const bool addToTheory = true) const = 0;
	virtual void replace (const Term*, const Term*) = 0;
	virtual const Formula* getImage() const = 0;
	virtual void setImage (const Formula*) = 0;

	virtual const Location& getLocation() const = 0;

	enum Kind {
		// Subset kinds:
		GENERAL_SUB_KIND, // c ⊑ d, general case
		SIMPLE_SUB_KIND,  // a ⊑ b, where a and b are primitive terms
		CONJ_SUB_KIND,    // a_1 ⊓ ··· ⊓ a_n ⊑ b, where a_1,...,a_n and b are primitive terms
		RIGHT_SUB_KIND,   // a ⊑ ∃r.b, where a and b are primitive terms
		LEFT_SUB_KIND,    // ∃r.a ⊑ b, where a and b are primitive terms

		// Equality kinds:
		IDENTITY_EQ_KIND,   // c ≡ d
		DEFINITION_EQ_KIND, // a ≡ d by definition, where a is a primitive term
		PRIMITIVE_EQ_KIND   // a ≡ b, where a and b are primitive terms
	};
	enum Type {
		SUBSET_TYPE,  // c ⊑ d - subset
		EQUALITY_TYPE // c ≡ d - equality
	};
	virtual Kind getKind() const = 0;
	virtual Type getType() const = 0;
	virtual bool hasInvalidKind() const = 0;

	bool isPreNormal() const;
	static Kind getKind (const Term*, const Term*);
	static const char* showKind (const Kind);
	static const char* showType (const Type);
};

}
}


