/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_object_Typing.hpp                          */
/* Description:     abstract interface for typing objects                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/object/mdl_interface_object_Buildable.hpp"

namespace mdl {
namespace interface {
namespace object {

class Typing : virtual public Buildable {
public :
	virtual void translateVariables (String&) const { };
	virtual void translateFloatings (String&, const index :: Arity = 0) const { };

	virtual void setNext (Typing*) { };
	virtual void setType (const value :: Literal, Type*) { };

	virtual Type* getType (const value :: Literal) = 0;
	virtual header :: Variable* getDeclaration (const value :: Literal) = 0;
	virtual Typing* getPrevious() = 0;

	virtual const Type* getType (const value :: Literal) const = 0;
	virtual const header :: Variable* getDeclaration (const value :: Literal) const = 0;
	virtual const Typing* getPrevious() const = 0;
};

}
}
}


