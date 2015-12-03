/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_cut_interface_Includable.hpp                          */
/* Description:     abstract interface for includable object                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_CUT_INTERFACE_INCLUDABLE_HPP_
#define MM_CUT_INTERFACE_INCLUDABLE_HPP_

#include "mm/interface/mm_interface.hpp"

namespace mm {
namespace cut {
namespace interface {

class Includable : virtual public object :: Object {
public :
	virtual void writeInclusion (String&) const = 0;
	virtual const Includable* getPrevious() const = 0;
	virtual void setPrevious (const Includable*) const = 0;
};

}
}
}

#endif /* MM_CUT_INTERFACE_INCLUDABLE_HPP_ */
