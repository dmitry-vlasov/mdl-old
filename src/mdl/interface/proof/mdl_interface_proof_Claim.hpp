/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_proof_Claim.hpp                            */
/* Description:     abstract interface for claim in proof                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_PROOF_CLAIM_HPP_
#define MDL_INTERFACE_PROOF_CLAIM_HPP_

#include "mdl/interface/proof/mdl_interface_proof_Step.hpp"
#include "mdl/interface/proof/mdl_interface_proof_Provable.hpp"

namespace mdl {
namespace interface {
namespace proof {

class Claim : virtual public Step, virtual public Provable {
public :
	virtual void addStep (Step*) = 0;
	virtual void addVariable (const Symbol&) = 0;
	virtual Proof* getProof() = 0;
	virtual const Proof* getProof() const = 0;
};

}
}
}

#endif /*MDL_INTERFACE_PROOF_CLAIM_HPP_*/
