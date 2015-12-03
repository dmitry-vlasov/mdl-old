/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_block_Theorem.hpp                          */
/* Description:     theorem abstract interface                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_BLOCK_THEOREM_HPP_
#define MDL_INTERFACE_BLOCK_THEOREM_HPP_

#include "mdl/interface/block/mdl_interface_block_Assertion.hpp"

namespace mdl {
namespace interface {
namespace block {

class Theorem :
	virtual public Assertion,
	virtual public object :: Provable {
};

}
}
}

#endif /*MDL_INTERFACE_BLOCK_THEOREM_HPP_*/
