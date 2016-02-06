/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_block_Super.hpp                            */
/* Description:     type-supertype relation abstract interface               */
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
namespace block {

class Super : public object :: Buildable {
public :
	virtual void translateReference (String&) const = 0;
	virtual void addSuperSuper (vector :: Super&) = 0;
	virtual mdl :: Type* getType() = 0;
	virtual const mdl :: Type* getType() const = 0;
};

}
}
}


