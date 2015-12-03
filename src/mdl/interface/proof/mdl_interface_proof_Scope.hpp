/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_proof_Scope.hpp                            */
/* Description:     abstract interface for scope in proof                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_PROOF_SCOPE_HPP_
#define MDL_INTERFACE_PROOF_SCOPE_HPP_

#include "mdl/interface/object/mdl_interface_object.hpp"

namespace mdl {
namespace interface {
namespace proof {

class Scope : virtual public object :: Object {
public :
	virtual mdl :: Assertion* getAssertion () = 0;
	virtual Proof* getProof() = 0;
	virtual Claim* getClaim() = 0;
	virtual Node* getHypothesis (const index :: Arity) = 0;
	virtual Node* getProposition (const index :: Arity) = 0;
	virtual object :: Typing* getVariables () = 0;
	virtual Notation* getNotation (const value :: Literal) = 0;
	virtual Step* getStep (const index :: Step) = 0;

	virtual const mdl :: Assertion* getAssertion () const = 0;
	virtual const Proof* getProof() const = 0;
	virtual const Claim* getClaim() const = 0;
	virtual const Node* getHypothesis (const index :: Arity) const = 0;
	virtual const Node* getProposition (const index :: Arity) const = 0;
	virtual const object :: Typing* getVariables () const = 0;
	virtual const Notation* getNotation (const value :: Literal) const = 0;
	virtual const Step* getStep (const index :: Step) const = 0;
};

}
}
}

#endif /*MDL_INTERFACE_PROOF_SCOPE_HPP_*/
