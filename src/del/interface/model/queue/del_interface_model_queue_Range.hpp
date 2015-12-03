/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_model_queue_Range.hpp                      */
/* Description:     abstract interface for queue (range) element             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_INTERFACE_MODEL_QUEUE_RANGE_HPP_
#define DEL_INTERFACE_MODEL_QUEUE_RANGE_HPP_

#include "del/interface/model/queue/del_interface_model_queue_Element.hpp"

namespace del {
namespace interface {
namespace model {
namespace queue {

class Range : public Element {
public :
	enum Type {
		SIMPLE = 0,
		CONJ   = 1,
		EXISTS = 2
	};
	virtual Type getType() const = 0;
	virtual value :: Integer getSize() const = 0;
	virtual value :: Variable getConcept (const value :: Integer = 0) const = 0;
	virtual value :: Relation getRelation() const = 0;

	bool operator < (const Range&) const;
	bool operator > (const Range&) const;
	bool operator == (const Range&) const;
};

}
}
}
}

#endif /*DEL_INTERFACE_MODEL_QUEUE_RANGE_HPP_*/
