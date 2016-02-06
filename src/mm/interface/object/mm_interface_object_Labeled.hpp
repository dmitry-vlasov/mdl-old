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

#pragma once

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


