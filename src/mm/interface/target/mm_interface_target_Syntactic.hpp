/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_interface_target_Syntactic.hpp                        */
/* Description:     abstract interface to the syntactic rule                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_INTERFACE_TARGET_SYNTACTIC_HPP_
#define MM_INTERFACE_TARGET_SYNTACTIC_HPP_

#include "interface/object/mm_interface_object.hpp"

namespace mm {
namespace interface {
namespace target {

class Syntactic : public object :: Referable {
public :
	virtual void addTerm (const Term* const) = 0;
};

}
}
}

#endif /* MM_INTERFACE_TARGET_SYNTACTIC_HPP_ */
