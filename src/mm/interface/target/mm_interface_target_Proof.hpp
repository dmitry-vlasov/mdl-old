/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_interface_target_Proof.hpp                            */
/* Description:     abstract interface to the mdl proof                      */
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

class Proof : public object :: Targetive {
public :
	virtual void setTheorem (const Theorem*) = 0;
	virtual void addStep (const Step* const) = 0;
	virtual void finalize() = 0;
};

}
}
}


