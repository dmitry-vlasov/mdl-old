/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_object_Expressive.hpp                      */
/* Description:     abstract interface for expressive objects                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_OBJECT_EXPRESSIVE_HPP_
#define MDL_INTERFACE_OBJECT_EXPRESSIVE_HPP_

#include "mdl/interface/mdl_interface.dpp"
#include "mdl/expression/mdl_expression.hpp"

namespace mdl {
namespace interface {
namespace object {

class Expressive {
public :
	virtual Type* getType() = 0;
	virtual array :: Expression* getExpression() = 0;
	virtual const Type* getType() const = 0;
	virtual const array :: Expression* getExpression() const = 0;
};

}
}
}

#endif /*MDL_INTERFACE_OBJECT_EXPRESSIVE_HPP_*/
