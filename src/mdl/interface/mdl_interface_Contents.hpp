/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_Contents.hpp                               */
/* Description:     abstract interface for theory contents class             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_CONTENTS_HPP_
#define MDL_INTERFACE_CONTENTS_HPP_

#include "mdl/interface/object/mdl_interface_object.hpp"
#include "mdl/interface/mdl_interface_Components.hpp"

namespace mdl {
namespace interface {

class Contents :
	virtual public object :: Identifiable,
	virtual public Components {
};

}
}

#endif /*MDL_INTERFACE_CONTENTS_HPP_*/
