/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_Assertion.hpp                              */
/* Description:     abstract interface for assertion class                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface_Decompose.hpp"
#include "del/interface/del_interface_Decomposition.hpp"

namespace del {
namespace interface {

class Assertion : public Writable {
public :
	virtual void verify() const = 0;
	virtual Decompose* decompose() = 0;
	virtual Decomposition* decomposition() = 0;
};

}
}


