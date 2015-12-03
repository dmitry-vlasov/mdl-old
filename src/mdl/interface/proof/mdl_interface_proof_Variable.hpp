/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_proof_Variable.hpp                         */
/* Description:     abstract interface for variable declaration in proof     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_PROOF_VARIABLE_HPP_
#define MDL_INTERFACE_PROOF_VARIABLE_HPP_

#include "mdl/interface/object/mdl_interface_object.hpp"
#include "mdl/interface/proof/mdl_interface_proof_Line.hpp"

namespace mdl {
namespace interface {
namespace proof {

class Variable :
	virtual public Line,
	virtual public mdl :: object :: Typing {
};

}
}
}

#endif /*MDL_INTERFACE_PROOF_VARIABLE_HPP_*/
