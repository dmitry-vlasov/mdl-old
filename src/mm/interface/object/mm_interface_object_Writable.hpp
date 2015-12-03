/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_interface_object_Writable.hpp                         */
/* Description:     abstract interface for writable object                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_INTERFACE_OBJECT_WRITABLE_HPP_
#define MM_INTERFACE_OBJECT_WRITABLE_HPP_

#include "interface/object/mm_interface_object_Object.hpp"

namespace mm {
namespace interface {
namespace object {

class Writable : virtual public Object {
public :
	virtual void write (String&) const = 0;
	virtual void show (String&) const;
	virtual void write (Output&) const;
	virtual void write() const;
	virtual bool nothingToWrite() const;
};

}
}
}

#endif /*MM_INTERFACE_OBJECT_WRITABLE_HPP_*/
