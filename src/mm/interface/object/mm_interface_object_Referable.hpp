/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_interface_object_Referable.hpp                        */
/* Description:     abstract interface for referable object                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_INTERFACE_OBJECT_REFERABLE_HPP_
#define MM_INTERFACE_OBJECT_REFERABLE_HPP_

#include "interface/mm_interface.dpp"
#include "interface/object/mm_interface_object_Targetive.hpp"

namespace mm {
namespace interface {
namespace object {

class Referable : virtual public Targetive {
public :
	virtual void writeReference (String&) const = 0;
	virtual void writeIdentificator (String&) const = 0;
};

}
}
}

#endif /*MM_INTERFACE_OBJECT_REFERABLE_HPP_*/
