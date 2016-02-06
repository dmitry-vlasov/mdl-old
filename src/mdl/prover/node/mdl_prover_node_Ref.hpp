/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_node_Ref.hpp                                  */
/* Description:     reference node in proof variant tree                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/prover/mdl_prover.dpp"
#include "mdl/prover/evidence/mdl_prover_evidence_Vector.hpp"

namespace mdl {
namespace prover {
namespace node {

template<class A>
class Ref :
	public Node<A>,
	public Scalar<Ref<A>, A> {
public :
	typedef A Allocator_;
	typedef Types<Allocator_> Types_;
	typedef
		typename Types_ :: Expression_
		Expression_;
	typedef
		typename Types_ :: Substitution_
		Substitution_;
	typedef
		typename Types_ :: Node_
		Node_;
	typedef
		typename tree :: Tree<Allocator_>
		Tree_;
	typedef
		typename Types_ :: Evidence_
		Evidence_;
	typedef
		typename Types_ :: Evidences_
		Evidences_;
	typedef
		typename Types_ :: Proof_
		Proof_;
	typedef
		typename Types_ :: PremiseTree_
		PremiseTree_;
	typedef
		typename Types_ :: Premise_
		Premise_;
	typedef
		typename Types_ :: ExpressionTree_
		ExpressionTree_;

	Ref
	(
		Tree_*,
		Substitution_* replacement,
		Node_* down,
		Node_* up,
		const mdl :: proof :: Node* hint
	);
	virtual ~ Ref();

	// prover :: Node interface
	virtual const mdl :: proof :: Node* getHint() const;
	virtual void markHint (const mdl :: proof :: Node*);

	virtual value :: Integer getUpArity() const;
	virtual value :: Integer getDownArity() const;
	virtual Node_* getUp (const value :: Integer);
	virtual Node_* getDown (const value :: Integer);
	virtual const Node_* getUp (const value :: Integer) const;
	virtual const Node_* getDown (const value :: Integer) const;

	virtual void growUp();
	virtual bool growDown (Evidence_*);

	virtual Expression_* getExpression();
	virtual mdl :: Proposition* getProposition();
	virtual const Expression_* getExpression() const;
	virtual const mdl :: Proposition* getProposition() const;
	virtual Evidences_& getEvidences();
	virtual const Evidences_& getEvidences() const;
	virtual value :: Integer getMaxHeight() const;
	virtual value :: Integer getMinHeight() const;
	virtual value :: Real getWeight() const;
	virtual bool isProved() const;
	virtual bool isRoot() const;
	virtual bool mayGrowUp() const;
	virtual void addDown (Node_*);
	virtual bool liesDown (const Node_*) const;
	virtual void showBack (String&) const;
	virtual void showTreeBriefly (String&) const;
	virtual value :: Integer getForking() const;
	virtual void showInfo (String&, const int indent = 0) const;

	// object :: Cloneable interface
	virtual Node_* clone() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

protected :
	virtual int getXGraphCoord() const;
	virtual int getYGraphCoord() const;

private :
	typedef
		typename evidence :: Vector<Allocator_, false>
		EvidenceVector_;

	// weight routines
	void calculateWeight() const;

	// build down routines
	bool addEvidence (Evidence_*);

	void verify() const;
	void showNodeInGML (String&) const;
	void showNodePlain (String&) const;
	void showInfoHeader (String&, const int indent) const;
	void showInfoTree (String&, const int indent) const;
	void showInfoNode (String&, const int indent) const;
	void showInfoExpression (String&, const int indent) const;

	template<class>
	friend class Prop;
	template<class>
	friend class Hyp;

	// base
	const value :: Integer minHeight_;
	Substitution_* replacement_;

	// variant tree
	Node_* up_;
	Node_* down_;

	// clone
	mutable Ref* clone_;

	// all proof evidences
	EvidenceVector_ evidences_;

	// for self-learning algorithms: a true proof hint
	const mdl :: proof :: Node* hint_;

	mutable value :: Real xx_;
	mutable value :: Real yy_;
};

}
}
}


