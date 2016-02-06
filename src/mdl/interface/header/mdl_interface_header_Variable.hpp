/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_header_Variable.hpp                        */
/* Description:     abstract interface for variable declaration              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/object/mdl_interface_object.hpp"

namespace mdl {
namespace interface {
namespace header {

class Variable : virtual public object :: Buildable {
public :
	virtual value :: Literal getLiteral() const = 0;
	virtual void setIndex (const index :: Arity) = 0;
	virtual void setType (Type*) = 0;
	virtual void translateReference (String&) const = 0;

	virtual Symbol& getSymbol() = 0;
	virtual Type* getType () = 0;
	virtual const Symbol& getSymbol() const = 0;
	virtual const Type* getType () const = 0;
};

}
}
}


