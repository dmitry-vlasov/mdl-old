/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_model_Positive.hpp                         */
/* Description:     abstract interface for positive nodes in model trees     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_INTERFACE_MODEL_POSITIVE_HPP_
#define DEL_INTERFACE_MODEL_POSITIVE_HPP_

#include "del/interface/del_interface_Object.hpp"
#include "del/interface/del_interface_Cloneable.hpp"
#include "del/interface/model/del_interface_model_Node.hpp"

namespace del {
namespace interface {
namespace model {

class Positive : public Node {
public :
	virtual Symbol getVariable() const = 0;
	virtual pair :: Symbol getPair() const = 0;
};

}
}
}

#endif /*DEL_INTERFACE_MODEL_POSITIVE_NODE_HPP_*/
