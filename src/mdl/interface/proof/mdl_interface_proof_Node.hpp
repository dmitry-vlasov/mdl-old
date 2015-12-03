/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_proof_Node.hpp                             */
/* Description:     abstract interface for proof tree nodes                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_PROOF_NODE_HPP_
#define MDL_INTERFACE_PROOF_NODE_HPP_

#include "mdl/interface/object/mdl_interface_object.hpp"
#include "mdl/lexer/mdl_lexer_Token.hpp"
#include "mdl/interface/proof/mdl_interface_proof_Scoping.hpp"

namespace mdl {
namespace interface {
namespace proof {

class Node :
	virtual public object :: Expressive,
	virtual public object :: Writable,
	virtual public proof :: Scoping {
public :
	enum Kind {
		HYP  = Token :: HYP,
		PROP = Token :: PROP,
		STEP = Token :: STEP,
	};
	virtual Kind getKind() const = 0;
	virtual index :: Step getIndex() const = 0;
	virtual void replicateReference (String&) const = 0;
	virtual void translateReference (String&) const = 0;
};

}
}
}

#endif /*MDL_INTERFACE_PROOF_NODE_HPP_*/
