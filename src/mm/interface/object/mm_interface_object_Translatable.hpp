/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_interface_object_Translatable.hpp                     */
/* Description:     abstract interface for translatable mm object            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_INTERFACE_OBJECT_TRANSLATABLE_HPP_
#define MM_INTERFACE_OBJECT_TRANSLATABLE_HPP_

#include "interface/object/mm_interface_object_Writable.hpp"

namespace mm {
namespace interface {
namespace object {

class Translatable : virtual public Writable {
public :
	virtual const Targetive* translate() const = 0;
	virtual bool isBlock() const = 0;
	virtual bool isDisjoined() const = 0;
	virtual bool isFloating() const = 0;
	virtual bool isEssential() const = 0;
};

}
}
}

#endif /*MM_INTERFACE_OBJECT_TRANSLATABLE_HPP_*/
