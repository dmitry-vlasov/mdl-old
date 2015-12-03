/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_object_Cloneable.hpp                       */
/* Description:     abstract interface for cloneable objects                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_OBJECT_CLONEABLE_HPP_
#define MDL_INTERFACE_OBJECT_CLONEABLE_HPP_

#include "mdl/interface/mdl_interface.dpp"

namespace mdl {
namespace interface {
namespace object {

template<class T>
class Cloneable : virtual public Object {
public :
	virtual T* clone() const = 0;
};

}
}
}

#endif /*MDL_INTERFACE_OBJECT_CLONEABLE_HPP_*/
