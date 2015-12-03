/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_proof_Scoping.hpp                          */
/* Description:     abstract interface for object with scope                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_PROOF_SCOPING_HPP_
#define MDL_INTERFACE_PROOF_SCOPING_HPP_

#include "mdl/interface/mdl_interface.dpp"

namespace mdl {
namespace interface {
namespace proof {

class Scoping {
public :
	virtual proof :: Scope* buildScope (proof :: Scope*) = 0;
	virtual void setScope (proof :: Scope*) = 0;
	virtual proof :: Scope* getScope() = 0;
	virtual const proof :: Scope* getScope() const = 0;
};

}
}
}

#endif /*MDL_INTERFACE_PROOF_SCOPING_HPP_*/
