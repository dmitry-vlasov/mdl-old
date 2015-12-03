/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_proof_Link.hpp                             */
/* Description:     abstract interface for links in proof                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_PROOF_LINK_HPP_
#define MDL_INTERFACE_PROOF_LINK_HPP_

#include "mdl/interface/object/mdl_interface_object.hpp"

namespace mdl {
namespace interface {
namespace proof {

class Link : virtual public object :: Buildable {
public :
	virtual void buildScope (Scope*) = 0;
	virtual index :: Arity getPropositionIndex() const = 0;

	virtual mdl :: Assertion* getAssertion() = 0;
	virtual Proposition* getProposition() = 0;
	virtual References* getReferences() = 0;

	virtual const mdl :: Assertion* getAssertion() const = 0;
	virtual const Proposition* getProposition() const = 0;
	virtual const References* getReferences() const = 0;

	virtual void translateReferences (String&) const = 0;
	virtual void translateAssertion (String&) const = 0;
};

}
}
}

#endif /*MDL_INTERFACE_PROOF_LINK_HPP_*/
