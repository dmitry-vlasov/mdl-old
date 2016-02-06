/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_Signature.hpp                              */
/* Description:     abstract interfaces for del signature                    */
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

namespace del {
namespace interface {

class Signature :
	public Writable,
	public Cloneable<Signature> {
public :
	virtual value :: Integer getSize() const = 0;
	virtual bool isEqual (const Signature*) const = 0;
	virtual bool isSubset (const Signature*) const = 0;
	virtual void copy (const Signature*) = 0;
	virtual void clear() = 0;
	virtual value :: Signature getName() const = 0;
	virtual void setName (const value :: Signature) = 0;
	virtual value :: Integer cardinality() const = 0;
	virtual const Symbol& getSymbol (const value :: Integer = 0) const = 0;
	virtual const Symbol& getRandomSymbol() const = 0;
	virtual const Symbol& getRandomConcept() const = 0;
	virtual const Symbol& getRandomRelation() const = 0;

	virtual void makeDeltaCopy (const Expansion*) = 0;
	virtual bool containsSymbol (const Symbol&) const = 0;
	virtual void addSymbol (const Symbol&) = 0;
	virtual void removeSymbol (const Symbol&) = 0;
	virtual void intersect (const Signature*) = 0;
	virtual void join (const Signature*) = 0;
	virtual void subtract (const Signature*) = 0;
};

}
}


