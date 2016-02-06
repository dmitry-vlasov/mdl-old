/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_model_Model.hpp                            */
/* Description:     abstract interface for model class                       */
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
#include "del/interface/model/del_interface_model.dpp"

namespace del {
namespace interface {
namespace model {

class Model :
	public Object,
	public Cloneable<Model> {
public :
	// build M such that M |- T
	virtual void build (const Theory* T) = 0;

	// check if T |- phi
	virtual bool satisfies (const Theory* T, const Formula* phi) = 0;

	// check if T |- a ⊑ b
	virtual bool isTrueSubseteq (const Symbol a, const Symbol b) const = 0;

	// check if T \ U |- a ⊑ b
	virtual bool isTrueSubseteq
	(
		const Symbol a,
		const Symbol b,
		const set :: Formula* U
	) const = 0;

	// eval such d of signature delta, that T |- a ⊑ d and T |- d ⊑ b
	virtual const Term* evalInterpolant
	(
		const Symbol a,
		const Symbol b,
		const Signature* delta
	) const = 0;

	virtual bool isEqual (const Model*, const bool show = false) const = 0;
	virtual value :: Integer getSize() const = 0;
	virtual const Node* getNode (const value :: Integer) const = 0;
	virtual void registerNode (Node*) = 0;
	virtual void clearNodes() = 0;

	virtual PredicateMap& predicates() = 0;
	virtual RelationMap&  relations() = 0;
	virtual const PredicateMap& getPredicates() const = 0;
	virtual const RelationMap&  getRelations() const = 0;
};

}
}
}


