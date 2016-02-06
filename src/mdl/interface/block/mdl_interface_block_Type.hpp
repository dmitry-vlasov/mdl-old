/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_block_Type.hpp                             */
/* Description:     type abstract interface                                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/object/mdl_interface_object.hpp"
#include "mdl/expression/mdl_expression.hpp"

namespace mdl {
namespace interface {
namespace block {

class Type : public object :: Identifiable {
public :
	virtual void mine (String&, const index :: Type) const = 0;
	virtual index :: Type getSuperCount() const = 0;
	virtual index :: Type getInferCount() const = 0;
	virtual bool isSuper (const Type*) const = 0;
	virtual bool isInfer (const Type*) const = 0;

	virtual void addRule (Rule*) = 0;
	virtual void addSubtype (Type*) = 0;

	virtual tree :: Rule* getRuleTree() = 0;
	virtual Super* getSuper (const index :: Type) = 0;
	virtual Super* getSuper (const Type*) = 0;
	virtual Type*  getInfer (const index :: Type) = 0;

	virtual const tree :: Rule* getRuleTree() const = 0;
	virtual const Super* getSuper (const index :: Type) const = 0;
	virtual const Super* getSuper (const Type*) const = 0;
	virtual const Type*  getInfer (const index :: Type) const = 0;
};

}
}
}


