/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_interface_target_Term.hpp                             */
/* Description:     abstract interface to the mdl term                       */
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

class Term : public object :: Targetive {
public :
	virtual const Symbol& getType() const = 0;
	virtual const Symbol& getFirstSymbol() const = 0;

private :
	virtual void writeHeader (String&) const = 0;
	virtual void writeType (String&) const = 0;
	virtual void writeBody (String&) const = 0;
};

}
}
}


