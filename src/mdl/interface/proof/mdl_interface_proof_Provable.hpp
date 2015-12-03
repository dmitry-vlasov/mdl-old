/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_proof_Provable.hpp                         */
/* Description:     abstract interface for provable proof tree nodes         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_PROOF_PROVABLE_HPP_
#define MDL_INTERFACE_PROOF_PROVABLE_HPP_

#include "mdl/interface/mdl_interface.dpp"

namespace mdl {
namespace interface {
namespace proof {

class Provable : virtual public Node {
public :
	virtual void setProof (Node*) = 0;
};

}
}
}

#endif /*MDL_INTERFACE_PROOF_PROVABLE_HPP_*/
