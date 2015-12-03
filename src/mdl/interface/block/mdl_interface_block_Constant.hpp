/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_block_Constant.hpp                         */
/* Description:     constant abstract interface                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_BLOCK_CONSTANT_HPP_
#define MDL_INTERFACE_BLOCK_CONSTANT_HPP_

#include "mdl/interface/object/mdl_interface_object.hpp"

namespace mdl {
namespace interface {
namespace block {

class Constant : public object :: Identifiable {
public :
	virtual index :: Literal getSize() const = 0;
	virtual value :: Literal getValue (const index :: Literal) const = 0;
};

}
}
}

#endif /*MDL_INTERFACE_BLOCK_CONSTANT_HPP_*/
