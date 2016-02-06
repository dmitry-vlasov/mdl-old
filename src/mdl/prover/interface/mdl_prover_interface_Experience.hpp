/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_interface_Expirience.hpp                      */
/* Description:     abstract interface for expirience in proofs              */
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
namespace prover {
namespace interface {

class Experience : public object :: Object {
public :
	typedef Node<allocator :: Boxed> Node_;

	virtual void learn() = 0;
	virtual void addPositive (const mdl :: proof :: Step* const) = 0;
	virtual void addNegative (const mdl :: proof :: Step* const) = 0;
	virtual value :: Real eval (const Node_*) const = 0;

	virtual value :: Real eval (const Node_*, const statement :: Experience*) const = 0;
};

}
}
}



