/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_object_Buildable.hpp                       */
/* Description:     abstract interface for buildable objects                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_OBJECT_BUILDABLE_HPP_
#define MDL_INTERFACE_OBJECT_BUILDABLE_HPP_

#include "mdl/interface/object/mdl_interface_object_Writable.hpp"

namespace mdl {
namespace interface {
namespace object {

class Buildable : virtual public Writable {
public :
	virtual void build() { };
};

}
}
}

#endif /*MDL_INTERFACE_OBJECT_BUILDABLE_HPP_*/
