/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_block_Definition.hpp                       */
/* Description:     definition abstract interface                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/block/mdl_interface_block_Assertion.hpp"

namespace mdl {
namespace interface {
namespace block {

class Definition : virtual public Assertion {
public :
	virtual term :: Definition* getDefiendum() = 0;
	virtual term :: Definition* getDefiniens() = 0;
	virtual const term :: Definition* getDefiendum() const = 0;
	virtual const term :: Definition* getDefiniens() const = 0;
};

}
}
}


