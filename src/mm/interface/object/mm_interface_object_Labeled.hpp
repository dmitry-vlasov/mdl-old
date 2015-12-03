/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_interface_object_Labeled.hpp                          */
/* Description:     abstract interface for labeled object                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_INTERFACE_OBJECT_LABELED_HPP_
#define MM_INTERFACE_OBJECT_LABELED_HPP_

#include "types/mm_types.hpp"

namespace mm {
namespace interface {
namespace object {

class Labeled {
public :
	virtual value :: Label getLabel() const = 0;
};

}
}
}

#endif /* MM_INTERFACE_OBJECT_LABELED_HPP_ */
