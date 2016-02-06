/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_proof_References.hpp                       */
/* Description:     abstract interface for references to the proof tree nodes*/
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

class References : virtual public object :: Writable {
public :
	virtual void build (Scope*) = 0;
	virtual void add (Reference*) = 0;
	virtual index :: Arity find (const Node*) const = 0;
	virtual index :: Arity getArity() const = 0;
	virtual Reference* get (const index :: Arity) = 0;
	virtual const Reference* get (const index :: Arity) const = 0;
};

}
}
}



