/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_interface_source_Constants.hpp                        */
/* Description:     abstract interface for metamath constants                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "interface/object/mm_interface_object.hpp"

namespace mm {
namespace interface {
namespace source {

class Constants : public object :: Translatable {
public :
	virtual bool isConstant (const value :: Literal) const = 0;
	virtual const Constants* getPrevious () const = 0;
	virtual void addTo (vector :: Literal&) const = 0;
};

}
}
}


