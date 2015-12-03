/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_interface_target_Disjoined.hpp                        */
/* Description:     abstract interface to the mdl disjoined restriction      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_INTERFACE_TARGET_DISJOINED_HPP_
#define MM_INTERFACE_TARGET_DISJOINED_HPP_

#include "interface/object/mm_interface_object.hpp"

namespace mm {
namespace interface {
namespace target {

class Disjoined : public object :: Targetive {
public :
	virtual bool isEmpty () const = 0;
};

}
}
}

#endif /* MM_INTERFACE_TARGET_DISJOINED_HPP_ */
