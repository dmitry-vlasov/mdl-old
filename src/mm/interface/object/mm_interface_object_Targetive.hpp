/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_interface_object_Targetive.hpp                        */
/* Description:     abstract interface for mdl target object                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_INTERFACE_OBJECT_TARGETIVE_HPP_
#define MM_INTERFACE_OBJECT_TARGETIVE_HPP_

#include "interface/object/mm_interface_object_Writable.hpp"

namespace mm {
namespace interface {
namespace object {

class Targetive : virtual public Writable {
public :
	virtual void complete (target :: Block* const) const = 0;
};

}
}
}

#endif /*MM_INTERFACE_OBJECT_TARGETIVE_HPP_*/
