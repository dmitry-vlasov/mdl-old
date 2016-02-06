/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_node_positive_Positive.hpp                     */
/* Description:     a positive node - concept                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface.hpp"
#include "del/model/node/negative/del_model_node_negative.dpp"

namespace del {
namespace model {
namespace node {
namespace positive {

template<class A>
class Positive : public del :: model :: Positive {
public :
	typedef A Allocator_;
	typedef
		del :: model :: Positive
		Positive_;

	Positive (Model*, const value :: Integer);
	Positive
	(
		Model*,
		const Node*,
		const Formula*
	);
	Positive
	(
		Model*,
		const Node* [],
		const value :: Integer,
		const Formula*
	);
	template<class A1>
	Positive (const Positive<A1>&, Model*);
	virtual ~ Positive();

	void add (const Node*);
	bool addNode (const Node*, const Formula*) const;
	bool addNode (const Node* [], const value :: Integer, const Formula*) const;

	// del :: model :: Positive interface
	virtual Symbol getVariable() const = 0;
	virtual pair :: Symbol getPair() const = 0;

	// del :: model :: Node interface
	virtual bool isEqual (const Node*, const Formula*) const;
	virtual bool isEqual (const Node* [], const value :: Integer, const Formula*) const;
	virtual bool fitsUntheory (const del :: set :: Formula*) const;
	virtual void showSuccessBranch (set :: Node*) const;
	virtual const Term* evalInterpolant (const Signature*) const;
	virtual Node* clone (Model*) const = 0;
	virtual bool isEqual (const Node*, const bool show = false) const;

	// del :: Object interface
	virtual void commitSuicide();
	virtual Size_t getSizeOf() const;
	virtual Size_t getVolume() const;
	virtual void show (String&) const;

protected :
	template<class>
	friend class Positive;

	typedef typename negative :: Conjunction<Allocator_> Conjunction_;
	typedef typename negative :: ExistsLeft<Allocator_> ExistsLeft_;
	typedef typename negative :: ExistsRight<Allocator_> ExistsRight_;
	typedef typename negative :: Id<Allocator_> Id_;
	typedef typename negative :: Simple<Allocator_> Simple_;
	typedef typename negative :: Top<Allocator_> Top_;

	typedef
		del :: vector :: Vector
		<
			const Node*,
			storage :: ByValue,
			Allocator_
		>
		NodeVector_;

	const Node* createNode (const Node*, const Formula*) const;
	const Node* createNode (const Node* [], const value :: Integer, const Formula*) const;

	void cloneNodeVector (Model*) const;

	Model* model_;
	mutable NodeVector_ nodeVector_;
};

}
}
}
}


