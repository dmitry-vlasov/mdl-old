/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_header_statement_Definition.hpp            */
/* Description:     abstract interface for definition statement              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_HEADER_STATEMENT_DEFINITION_HPP_
#define MDL_INTERFACE_HEADER_STATEMENT_DEFINITION_HPP_

#include "mdl/interface/header/statement/mdl_interface_header_statement_Proposition.hpp"

namespace mdl {
namespace interface {
namespace header {
namespace statement {

class Definition : virtual public Proposition {
public :
	virtual void setDefiendum (term :: Definition*) = 0;
	virtual void setDefiniens (term :: Definition*) = 0;
};

}
}
}
}

#endif /*MDL_INTERFACE_HEADER_STATEMENT_DEFINITION_HPP_*/
