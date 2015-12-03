/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_interface_target_Target.hpp                           */
/* Description:     abstract interface to the mdl target - top AST node      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_INTERFACE_TARGET_TARGET_HPP_
#define MM_INTERFACE_TARGET_TARGET_HPP_

#include "interface/object/mm_interface_object.hpp"

namespace mm {
namespace interface {
namespace target {

class Target : public object :: Targetive {
public :
	virtual void addBlock (const object :: Targetive* const) = 0;
	virtual const object :: Referable* getTheory() const = 0;
};

}
}
}

#endif /* MM_INTERFACE_TARGET_TARGET_HPP_ */
