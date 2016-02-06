/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_model_Predicate.hpp                        */
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

class Predicate : public Object {
public :
	virtual value :: Integer getSize() const = 0;
	virtual const Positive* getNode (const value :: Integer) const = 0;
	virtual const Node* find (const Symbol) const = 0;
	virtual bool addNode (const Symbol, const Node* = NULL, const Formula* = NULL) = 0;
	virtual bool addNode (const Symbol, const Node* [], const value :: Integer, const Formula*) = 0;
	virtual Predicate* clone (Model*) const = 0;
	virtual bool isEqual (const Predicate*, const bool show = false) const = 0;

	bool isTrue (const Symbol) const;
	bool isTrue (const value :: Variable) const;
};

}
}
}


