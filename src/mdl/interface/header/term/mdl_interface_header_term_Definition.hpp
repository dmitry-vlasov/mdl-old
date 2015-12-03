/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_header_term_Definition.hpp                 */
/* Description:     abstract interface for definition term                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_HEADER_TERM_DEFINITION_HPP_
#define MDL_INTERFACE_HEADER_TERM_DEFINITION_HPP_

#include "mdl/interface/header/term/mdl_interface_header_term_Term.hpp"

namespace mdl {
namespace interface {
namespace header {
namespace term {

class Definition : virtual public Term {
public :
	virtual void setDefinition (mdl :: Definition*) = 0;
};

}
}
}
}

#endif /*MDL_INTERFACE_HEADER_TERM_DEFINITION_HPP_*/
