/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_header_Variables.hpp                       */
/* Description:     abstract interface for variables declarations            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_HEADER_VARIABLES_HPP_
#define MDL_INTERFACE_HEADER_VARIABLES_HPP_

#include "mdl/interface/object/mdl_interface_object.hpp"

namespace mdl {
namespace interface {
namespace header {

class Variables : virtual public object :: Typing {
public :
	virtual index :: Arity getSize() const = 0;
	virtual bool contain (const Symbol&) const = 0;
	virtual Variable* getVariable (const index :: Arity) = 0;
	virtual const Variable* getVariable (const index :: Arity) const = 0;
};

}
}
}

#endif /*MDL_INTERFACE_HEADER_VARIABLES_HPP_*/
