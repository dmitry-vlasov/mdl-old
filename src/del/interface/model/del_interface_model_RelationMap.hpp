/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_model_RelationMap.hpp                      */
/* Description:     abstract interface for predicates in model trees         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_INTERFACE_MODEL_RELATION_MAP_HPP_
#define DEL_INTERFACE_MODEL_RELATION_MAP_HPP_

#include "del/interface/del_interface_Object.hpp"
#include "del/interface/model/del_interface_model.dpp"

namespace del {
namespace interface {
namespace model {

class RelationMap : public Object {
public :
	virtual value :: Integer getSize() const = 0;
	virtual Relation* getRelation (const value :: Integer) const = 0;
	virtual Relation* getRelation (const Symbol) = 0;
	virtual void registerRelation (const Symbol) = 0;
	virtual void copy (const RelationMap&, Model*) = 0;
	virtual bool isEqual (const RelationMap&, const bool show = false) const = 0;
};

}
}
}

#endif /*DEL_INTERFACE_MODEL_RELATION_MAP_HPP_*/
