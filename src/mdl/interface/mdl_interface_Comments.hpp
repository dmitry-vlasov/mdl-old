/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_Comments.hpp                               */
/* Description:     abstract interface for Rusell comments                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_COMMENTS_HPP_
#define MDL_INTERFACE_COMMENTS_HPP_

#include "mdl/interface/object/mdl_interface_object.hpp"

namespace mdl {
namespace interface {

class Comments : virtual public object :: Writable {
};

}
}

#endif /*MDL_INTERFACE_COMMENTS_HPP_*/
