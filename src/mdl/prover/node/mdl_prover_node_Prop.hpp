/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_node_Prop.hpp                                 */
/* Description:     proposition node in proof variant tree                   */
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
class Prop :
	public Node<A>,
	public Scalar<Prop<A>, A> {
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
	typedef
		typename Types_ :: Matrix_
		Matrix_;

	Prop
	(
		Tree_*,
		mdl :: Proposition*,
		Substitution_* substitutionInt,
		Substitution_* substitutionExt,
		Node_* down,
		const mdl :: proof :: Step* hint
	);
	virtual ~ Prop();

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

private :
	template<class>
	friend class Node;
	template<class>
	friend class Hyp;
	template<class>
	friend class evidence :: Prop;
	template<class>
	friend class proof :: Prop;

	typedef Hyp<Allocator_> Hyp_;
	typedef Rate<Allocator_> Rate_;

	typedef
		typename evidence :: Vector<Allocator_, false>
		EvidenceVector_;

	/*typedef
		typename evidence :: Vector<Allocator_, true>
		EvidenceVector_;*/
	typedef
		typename mdl :: vector :: Vector
		<
			Node_*,
			storage :: ByValue,
			Allocator_
		>
		NodeVector_;

	// grow down routines
	bool checkUp() const;
	value :: Integer getDownVolume() const;
	void unifyDown();
	void unifyMatrix
	(
		Evidences_& evidences,
		const bool = true
	);
	void fillMatrix (Matrix_& matrix) const;
	void addEvidence();

	void showHypEvidences (String&) const;
	void verifySubstitutions() const;
	void verifyVariables (const Substitution_*) const;
	void verifyVariable (const Symbol&, const Substitution_*) const;

	void showNodeInGML (String&) const;
	void showNodePlain (String&) const;
	void showInfoHeader (String&, const int indent) const;
	void showInfoTree (String&, const int indent) const;
	void showInfoNode (String&, const int indent) const;
	void showInfoAssertion (String&, const int indent) const;

	// base
	value :: Integer minHeight_;
	mdl :: Proposition* proposition_;
	index :: Arity arity_;
	Substitution_* substitutionInt_;
	Substitution_* substitutionExt_;
	Expression_* expression_;

	// tree strucutre
	NodeVector_ up_;
	Node_* down_;

	// clone
	mutable Prop* clone_;

	// rate
	mutable Rate_* rate_;

	// all proof evidences
	EvidenceVector_ evidences_;

	// for self-learning algorithms: a true proof hint
	const mdl :: proof :: Step* hint_;

	#ifdef DEBUG_PROVER_MATRIX_UNIFICATION
	EvidenceVector_  evidencesOther_;
	#endif
};

}
}
}


