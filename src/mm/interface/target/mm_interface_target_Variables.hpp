/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_interface_target_Variables.hpp                        */
/* Description:     abstract interface to the mdl variables declaration      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_INTERFACE_TARGET_VARIABLES_HPP_
#define MM_INTERFACE_TARGET_VARIABLES_HPP_

#include "interface/target/mm_interface_target_Typing.hpp"

namespace mm {
namespace interface {
namespace target {

class Variables : public Typing {
public :
	virtual void addVariable (const Typing* const) = 0;
};

}
}
}

#endif /* MM_INTERFACE_TARGET_VARIABLES_HPP_ */
