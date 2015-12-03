/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_header_term_Rule.hpp                       */
/* Description:     abstract interface for syntax grammar rule term          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_HEADER_TERM_RULE_HPP_
#define MDL_INTERFACE_HEADER_TERM_RULE_HPP_

#include "mdl/interface/header/term/mdl_interface_header_term_Term.hpp"

namespace mdl {
namespace interface {
namespace header {
namespace term {

class Rule : virtual public Term {
public :
	virtual index :: Assertion getTargetIndex() const = 0;
	virtual void setRule (mdl :: Rule*) = 0;
};

}
}
}
}

#endif /*MDL_INTERFACE_HEADER_TERM_RULE_HPP_*/
