/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_model_queue_Predicate.hpp                  */
/* Description:     abstract interface for predicates in model trees         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_INTERFACE_MODEL_QUEUE_PREDICATE_HPP_
#define DEL_INTERFACE_MODEL_QUEUE_PREDICATE_HPP_

#include "del/interface/del_interface_Object.hpp"
#include "del/interface/model/queue/del_interface_model_queue.dpp"

namespace del {
namespace interface {
namespace model {
namespace queue {

class Predicate : public Object {
public :
	virtual value :: Integer getSize() const = 0;
	virtual value :: Variable getConcept (const value :: Integer) const = 0;
	virtual bool addConcept (const value :: Variable) = 0;
	virtual bool isTrue (const value :: Variable) const = 0;
	virtual void unite (const Predicate*) = 0;
};

}
}
}
}

#endif /*DEL_INTERFACE_MODEL_QUEUE_PREDICATE_HPP_*/
