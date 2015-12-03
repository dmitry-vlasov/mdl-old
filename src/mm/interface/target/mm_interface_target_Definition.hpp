/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_interface_target_Definition.hpp                       */
/* Description:     abstract interface to the mdl definition                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_INTERFACE_TARGET_DEFINITION_HPP_
#define MM_INTERFACE_TARGET_DEFINITION_HPP_

#include "interface/target/mm_interface_target_Statement.hpp"

namespace mm {
namespace interface {
namespace target {

class Definition : virtual public Statement {
public :
	virtual void addDefiendum (const object :: Targetive* const) = 0;
	virtual void addDefiniens (const object :: Targetive* const) = 0;
};

}
}
}

#endif /* MM_INTERFACE_TARGET_DEFINITION_HPP_ */
