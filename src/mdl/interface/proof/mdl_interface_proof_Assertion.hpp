/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_proof_Assertion.hpp                        */
/* Description:     abstract interface for a simple step in proof            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_PROOF_ASSERTION_HPP_
#define MDL_INTERFACE_PROOF_ASSERTION_HPP_

#include "mdl/interface/proof/mdl_interface_proof_Step.hpp"

namespace mdl {
namespace interface {
namespace proof {

class Assertion : virtual public Step {
public :
	virtual array :: Substitution* getSubstitution() = 0;
	virtual const array :: Substitution* getSubstitution() const = 0;
	virtual void collectExperience() = 0;
};

}
}
}

#endif /*MDL_INTERFACE_PROOF_ASSERTION_HPP_*/
