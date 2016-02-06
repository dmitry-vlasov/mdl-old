/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_model_Negative.hpp                         */
/* Description:     abstract interface for negative nodes in model trees     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface_Object.hpp"
#include "del/interface/del_interface_Cloneable.hpp"
#include "del/interface/model/del_interface_model_Node.hpp"

namespace del {
namespace interface {
namespace model {

class Negative : public Node {
public :
	virtual const del :: Formula* getFormula() const = 0;
};

}
}
}


