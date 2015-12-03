/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_header_statement_Statement.hpp             */
/* Description:     abstract interface for statement                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_HEADER_STATEMENT_STATEMENT_HPP_
#define MDL_INTERFACE_HEADER_STATEMENT_STATEMENT_HPP_

#include "mdl/interface/header/mdl_interface_header_Line.hpp"

namespace mdl {
namespace interface {
namespace header {
namespace statement {

class Statement : virtual public Line {
public :
	virtual index :: Arity getIndex() const = 0;
	virtual void setAssertion (mdl :: Assertion*) = 0;

	virtual mdl :: Assertion* getAssertion() = 0;
	virtual proof :: Node* getProofNode() = 0;
	virtual const mdl :: Assertion* getAssertion() const = 0;
	virtual const proof :: Node* getProofNode() const = 0;
};

}
}
}
}

#endif /*MDL_INTERFACE_HEADER_STATEMENT_STATEMENT_HPP_*/
