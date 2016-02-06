/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_model_Node.hpp                             */
/* Description:     abstract interface for nodes in model trees              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface_Object.hpp"
#include "del/interface/del_interface_Cloneable.hpp"
#include "del/interface/model/del_interface_model.dpp"

namespace del {
namespace interface {
namespace model {

class Node : public Object {
public :
	Node();
	virtual ~ Node();
	virtual bool isEqual (const Node*, const Formula*) const = 0;
	virtual bool isEqual (const Node* [], const value :: Integer, const Formula*) const = 0;
	virtual bool fitsUntheory (const set :: Formula*) const = 0;
	virtual void showSuccessBranch (del :: model :: set :: Node*) const = 0;
	virtual const Term* evalInterpolant (const Signature*) const = 0;
	virtual Node* clone (Model*) const = 0;
	virtual bool isEqual (const Node*, const bool show = false) const = 0;

	// boolean flags
	bool isVisited() const;
	bool isTrue() const;
	bool isFalse() const;
	const Term* getInterpolant() const;

	void setVisited() const;
	void setTrue() const;
	void setFalse() const;
	void setInterpolant (const Term*) const;

	void clear() const;

	// nstd :: Object interface
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

protected :
	mutable Node* clone_;

private :
	mutable bool isVisited_;
	mutable bool isTrue_;
	mutable const Term* interpolant_;
};

}
}
}


