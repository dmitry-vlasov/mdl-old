/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_block_Rule.hpp                             */
/* Description:     syntax grammar rule abstract interface                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_BLOCK_RULE_HPP_
#define MDL_INTERFACE_BLOCK_RULE_HPP_

#include "mdl/interface/object/mdl_interface_object.hpp"

namespace mdl {
namespace interface {
namespace block {

class Rule : virtual public object :: Identifiable {
public :
	virtual void setType (Type*) = 0;

	virtual Type* getType() = 0;
	virtual Variables* getVariables() = 0;
	virtual term :: Rule* getTerm() = 0;

	virtual const Type* getType() const = 0;
	virtual const Variables* getVariables() const = 0;
	virtual const term :: Rule* getTerm() const = 0;
};

}
}
}

#endif /*MDL_INTERFACE_BLOCK_RULE_HPP_*/
