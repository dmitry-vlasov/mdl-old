/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_interface_target_Proposition.hpp                      */
/* Description:     abstract interface to the mdl proposition                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_INTERFACE_TARGET_PROPOSITION_HPP_
#define MM_INTERFACE_TARGET_PROPOSITION_HPP_

#include "interface/object/mm_interface_object.hpp"

namespace mm {
namespace interface {
namespace target {

class Proposition : public object :: Targetive {
private :
	virtual void writeBody(String&) const = 0;
};

}
}
}

#endif /* MM_INTERFACE_TARGET_PROPOSITION_HPP_ */
