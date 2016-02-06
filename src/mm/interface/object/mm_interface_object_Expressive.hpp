/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_interface_object_Expressive.hpp                       */
/* Description:     abstract interface for object with expression            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "expression/mm_expression.hpp"

namespace mm {
namespace interface {
namespace object {

class Expressive {
public :
	virtual bool isEqual (const Expression* const) const = 0;
	virtual void assignTo (const Expression* const) = 0;
};

}
}
}


