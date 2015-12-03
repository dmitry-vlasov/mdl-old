/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_model_Relation.hpp                         */
/* Description:     abstract interface for relations in model trees          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_INTERFACE_MODEL_RELATION_HPP_
#define DEL_INTERFACE_MODEL_RELATION_HPP_

#include "del/interface/del_interface_Object.hpp"
#include "del/interface/del_interface_Cloneable.hpp"
#include "del/interface/model/del_interface_model.dpp"

namespace del {
namespace interface {
namespace model {

class Relation : public Object {
public :
	virtual value :: Integer getSize() const = 0;
	virtual const Positive* getNode (const value :: Integer) const = 0;
	virtual const Node* find (const Symbol, const Symbol) const = 0;
	virtual bool addNode (const Symbol, const Symbol, const Node*, const Formula*) = 0;
	virtual Relation* clone (Model*) const = 0;
	virtual bool isEqual (const Relation*, const bool show = false) const = 0;
};

}
}
}

#endif /*DEL_INTERFACE_MODEL_RELATION_HPP_*/
