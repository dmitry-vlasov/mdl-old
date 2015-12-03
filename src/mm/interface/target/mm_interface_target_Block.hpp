/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_interface_target_Block.hpp                            */
/* Description:     abstract interface to the contents of an mdl theory      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_INTERFACE_TARGET_BLOCK_HPP_
#define MM_INTERFACE_TARGET_BLOCK_HPP_

#include "interface/object/mm_interface_object.hpp"

namespace mm {
namespace interface {
namespace target {

class Block : public object :: Targetive {
public :
	virtual void addInclude (const object :: Targetive* const) = 0;
	virtual void addComponent (const object :: Targetive* const) = 0;
	virtual void addType (const Type* const) = 0;
	virtual const Type* getType (const Symbol&) const = 0;
};

}
}
}

#endif /*MM_INTERFACE_TARGET_BLOCK_HPP_*/
