/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_Identificator.hpp                          */
/* Description:     abstract interface for identificators                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/object/mdl_interface_object_Writable.hpp"

namespace mdl {
namespace interface {

class Identificator : virtual public object :: Writable {
public :
	virtual value :: Name getName() const = 0;
	virtual void setNext (Identificator*) = 0;
	virtual Identificator* getNext() = 0;
	virtual const Identificator* getNext() const = 0;
};

}
}


