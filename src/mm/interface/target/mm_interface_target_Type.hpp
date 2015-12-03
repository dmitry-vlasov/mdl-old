/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_interface_target_Type.hpp                             */
/* Description:     abstract interface to the mdl type                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_INTERFACE_TARGET_TYPE_HPP_
#define MM_INTERFACE_TARGET_TYPE_HPP_

#include "interface/object/mm_interface_object.hpp"

namespace mm {
namespace interface {
namespace target {

class Type : public object :: Referable {
public :
	virtual const Symbol& getSymbol() const = 0;
	virtual void setSuper (const Type* const) const = 0;
};

}
}
}

#endif /* MM_INTERFACE_TARGET_TYPE_HPP_ */
