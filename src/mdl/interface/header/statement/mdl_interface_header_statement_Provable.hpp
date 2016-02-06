/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_header_statement_Provable.hpp              */
/* Description:     abstract interface for provable statement                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/header/statement/mdl_interface_header_statement_Proposition.hpp"

namespace mdl {
namespace interface {
namespace header {
namespace statement {

class Provable : virtual public Proposition {
public :
	virtual proof :: Provable* getProof() = 0;
	virtual const proof :: Provable* getProof() const = 0;
};

}
}
}
}


