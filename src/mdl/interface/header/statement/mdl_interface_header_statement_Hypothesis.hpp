/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_header_statement_Hypothesis.hpp            */
/* Description:     abstract interface for hypothesis statement              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_HEADER_STATEMENT_HYPOTHESIS_HPP_
#define MDL_INTERFACE_HEADER_STATEMENT_HYPOTHESIS_HPP_

#include "mdl/interface/header/statement/mdl_interface_header_statement_Statement.hpp"

namespace mdl {
namespace interface {
namespace header {
namespace statement {

class Hypothesis : virtual public Statement {
};

}
}
}
}

#endif /*MDL_INTERFACE_HEADER_STATEMENT_HYPOTHESIS_HPP_*/
