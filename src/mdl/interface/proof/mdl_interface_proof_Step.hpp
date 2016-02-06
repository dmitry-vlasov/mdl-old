/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_proof_Step.hpp                             */
/* Description:     abstract interface for proof step                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/proof/mdl_interface_proof_Node.hpp"
#include "mdl/interface/proof/mdl_interface_proof_Line.hpp"

namespace mdl {
namespace interface {
namespace proof {

class Step :
	virtual public Node,
	virtual public Line {
public :
	enum Class {
		CLAIM     = Token :: CLAIM,
		QUESTION  = Token :: QUESTION,
		ASSERTION = Token :: THEOREM
	};
	virtual Class getClass() const = 0;
	virtual Question* questionSelf() = 0;
	virtual void addReference (Reference*) = 0;
	virtual void addDown (Step*) = 0;
	virtual index :: Arity getUpArity() const = 0;
	virtual index :: Arity getDownArity() const = 0;

	virtual Link* getLink() = 0;
	virtual Node* getUp (const index :: Arity) = 0;
	virtual Step* getDown (const index :: Arity) = 0;

	virtual const Link* getLink() const = 0;
	virtual const Node* getUp (const index :: Arity) const = 0;
	virtual const Step* getDown (const index :: Arity) const = 0;
};

}
}
}


