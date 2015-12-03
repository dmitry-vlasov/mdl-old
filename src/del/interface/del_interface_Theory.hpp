/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_Theory.hpp                                 */
/* Description:     abstract interface for theory class                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_INTERFACE_THEORY_HPP_
#define DEL_INTERFACE_THEORY_HPP_

#include "del/interface/del_interface_Cloneable.hpp"
#include "del/interface/del_interface_Writable.hpp"

namespace del {
namespace interface {

class Theory :
	public Writable,
	public Cloneable<Theory> {
public :
	virtual const Writable* translate() const = 0;
	virtual void extendWithCopies (const Signature*) = 0;

	virtual void repair() = 0;   // repairs formulas: makes them coherent with their type
	virtual void assemble (const Signature*) = 0;
	virtual const Signature* computeDelta (const value :: Integer) const = 0;

	virtual bool isEqual (const Theory*) const = 0;
	virtual bool isEquivalent (const Theory*, const bool showDifference) const = 0;
	virtual bool entails (const Theory*, const bool showDifference) const = 0;
	virtual bool entails (const Formula*, const bool showDifference) const = 0;

	virtual const Signature* getSignature (const bool = false) const = 0;
	virtual value :: Theory getName() const = 0;
	virtual void setName (const value :: Theory) = 0;
	virtual void primitivize (Signature* = NULL) = 0;
	virtual void normalize() = 0;
	virtual void minimize() = 0;
	virtual void decompose (const Signature*) = 0;
	virtual void makeDeltaCopy (const Expansion*) = 0;
	virtual void makeDeltaCopy (const Signature*) = 0;
	virtual void addFormula (const Formula* const) = 0;
	virtual void removeFormula (const Formula*) = 0;
	virtual bool containsFormula (const Formula*) const = 0;
	virtual void deleteFormula (const value :: Integer) = 0;
	virtual value :: Integer getSize() const = 0;
	virtual const Formula* getFormula (const value :: Integer) const = 0;
	virtual void replaceTerm (const Term*, const Term*) = 0;
	virtual void unite (const Theory*, const bool removeDuplicateFormulas = true) = 0;
	virtual bool isNormal() const = 0;
	virtual bool isMinimal() const = 0;
	virtual bool isPrimitive() const = 0;
	virtual bool isDecomposed() const = 0;
	virtual bool isAssembled() const = 0;
	virtual bool isForOutput() const = 0;
	virtual void showDifference (const Theory*) const = 0;
};

}
}

#endif /*DEL_INTERFACE_THEORY_HPP_*/
