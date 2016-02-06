/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_proof_Reference.hpp                        */
/* Description:     abstract interface for reference to the proof tree node  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/object/mdl_interface_object.hpp"

namespace mdl {
namespace interface {
namespace proof {

class Reference : virtual public object :: Writable {
public :
	virtual value :: Kind getKind() const = 0;
	virtual index :: Step getIndex() const = 0;
	virtual void build (Scope*) = 0;
	virtual Node* getNode() = 0;
	virtual const Node* getNode() const = 0;
};

}
}
}



