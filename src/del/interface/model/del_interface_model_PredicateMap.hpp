/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_model_PredicateMap.hpp                     */
/* Description:     abstract interface for predicates in model trees         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface_Object.hpp"
#include "del/interface/model/del_interface_model.dpp"

namespace del {
namespace interface {
namespace model {

class PredicateMap : public Object {
public :
	virtual value :: Integer getSize() const = 0;
	virtual Predicate* getPredicate (const value :: Integer) const = 0;
	virtual Predicate* getPredicate (const Symbol) = 0;
	virtual const Predicate* getPredicate (const Symbol) const = 0;
	virtual void registerVariable (const Symbol) = 0;
	virtual void copy (const PredicateMap&, Model*) = 0;
	virtual bool isEqual (const PredicateMap&, const bool show = false) const = 0;
};

}
}
}


