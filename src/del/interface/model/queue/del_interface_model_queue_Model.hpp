/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_model_queue_Model.hpp                      */
/* Description:     abstract interface for model class                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_INTERFACE_MODEL_QUEUE_MODEL_HPP_
#define DEL_INTERFACE_MODEL_QUEUE_MODEL_HPP_

#include "del/interface/del_interface_Object.hpp"
#include "del/interface/del_interface_Cloneable.hpp"
#include "del/interface/model/queue/del_interface_model_queue.dpp"

namespace del {
namespace interface {
namespace model {
namespace queue {

class Model : public Object {
public :
	// build M such that M |- T
	virtual void build (const Theory* T, model :: Model* = NULL) = 0;

	// check if T |- a ⊑ b
	virtual bool isTrueSubseteq (const Symbol a, const Symbol b) const = 0;
};

}
}
}
}

#endif /*DEL_INTERFACE_MODEL_QUEUE_MODEL_HPP_*/
