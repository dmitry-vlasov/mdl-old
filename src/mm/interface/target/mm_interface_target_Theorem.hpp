/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_interface_target_Theorem.hpp                          */
/* Description:     abstract interface to the mdl theorem                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_INTERFACE_TARGET_THEOREM_HPP_
#define MM_INTERFACE_TARGET_THEOREM_HPP_

#include "interface/target/mm_interface_target_Statement.hpp"

namespace mm {
namespace interface {
namespace target {

class Theorem : virtual public Statement {
public :
	virtual void addProof (const Proof* const) = 0;
};

}
}
}

#endif /* MM_INTERFACE_TARGET_THEOREM_HPP_ */
