/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_Components.hpp                             */
/* Description:     abstract interface component storage                     */
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

class Components {
public :
	virtual index :: Assertion getSize() const = 0;
	virtual void addComponentLast (object :: Verifiable* component) = 0;
	virtual void addComponentNextTo
	(
		object :: Verifiable* component,
		const object :: Verifiable* sibling
	) = 0;
	virtual object :: Verifiable* getComponent (const index :: Assertion) = 0;
	virtual const object :: Verifiable* getComponent (const index :: Assertion) const = 0;
};

}
}


