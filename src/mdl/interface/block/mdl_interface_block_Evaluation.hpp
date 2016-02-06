/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_block_Evaluation.hpp                       */
/* Description:     abstract interface for evaluation of assertions          */
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
namespace block {

class Evaluation : virtual public object :: Identifiable {
public :
	virtual void setToDefault() = 0;
	virtual index :: Arity getSize() const = 0;
	virtual evaluation :: Function* getFunction (const index :: Arity) = 0;
	virtual const evaluation :: Function* getFunction (const index :: Arity) const = 0;
};

}
}
}



