/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_interface_target_Statement.hpp                        */
/* Description:     abstract interface to the mdl statement                  */
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
namespace target {

class Statement : virtual public object :: Referable {
public :
	virtual void addHypothesis (const object :: Targetive* const) = 0;
	virtual void addProposition (const object :: Targetive* const) = 0;
};

}
}
}


