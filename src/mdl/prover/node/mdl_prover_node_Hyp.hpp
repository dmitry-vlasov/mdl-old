/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_node_Hyp.hpp                                  */
/* Description:     hypothesis node in proof variant tree                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_NODE_HYP_HPP_
#define MDL_PROVER_NODE_HYP_HPP_

#include "mdl/prover/mdl_prover.dpp"
#include "mdl/prover/evidence/mdl_prover_evidence_Vector.hpp"

namespace mdl {
namespace prover {
namespace node {

template<class A>
class Hyp :
	public Node<A>,
	public Scalar<Hyp<A>, A> {
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

	Hyp
	(
		Tree_*,
		Expression_*,
		const mdl :: proof :: Node* hint = NULL,
		Node_* down = NULL,
		index :: Arity index = 0
	);
	virtual ~ Hyp();

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
	typedef Prop<Allocator_> Prop_;
	typedef Ref<Allocator_> Ref_;
	typedef Top<Allocator_> Top_;
	typedef
		typename forest :: Proposition :: Unify_
		<
			Expression_,
			unify :: policy :: SYMMETRIC
		> :: Result_
		Propositions_;
	typedef
		typename PremiseTree_ :: template Unify_
		<
			Expression_,
			unify :: policy :: INVERSE
		> :: Result_
		UnifiedPremises_;
	typedef
		typename ExpressionTree_ :: template Equify_
		<
			Expression_,
			unify :: policy :: INVERSE
		> :: Result_
		UnifiedRefs_;

	typedef
		typename mdl :: vector :: Vector
		<
			Node_*,
			storage :: ByValue,
			Allocator_
		>
		NodeVector_;
	typedef
		typename evidence :: Vector<Allocator_, false>
		EvidenceVector_;

	// grow up routines
	bool growUpRefs();
	void growUpProps();
	void growUpRef (const typename UnifiedRefs_ :: Node_*);
	void growUpProp
	(
		const typename Propositions_ :: Node_*,
		const index :: Assertion,
		const bool onlyHint,
		value :: Integer& count
	);

	void buildSubstitutions
	(
		const mdl :: Assertion* const,
		const mdl :: Proposition* const,
		const stack :: Substitution*,
		const stack :: Substitution*,
		Substitution_*&,
		Substitution_*&
	);
	const stack :: Substitution*
	buildVariableReplacement
	(
		const mdl :: Assertion* const,
		const stack :: Substitution*
	);

	// grow down routines
	void unifyPremises();
	bool addEvidence (Evidence_*);
	void addTop
	(
		const typename UnifiedPremises_ :: Node_*,
		const bool onlyHint,
		value :: Integer& count
	);

	// verification routines
	void verifySubstitutionInt (const Substitution_*) const;
	void verifySubstitutionExt
	(
		const mdl :: Proposition* const,
		const Substitution_*
	) const;
	void verifySubstitutionExt
	(
		const Symbol& variable,
		const mdl :: Proposition* const proposition,
		const Substitution_* substitutionExt
	) const;

	void showNodeInGML (String&) const;
	void showNodePlain (String&) const;
	void showInfoHeader (String&, const int indent) const;
	void showInfoTree (String&, const int indent) const;
	void showInfoNode (String&, const int indent) const;
	void showInfoExpression (String&, const int indent) const;

	template<class>
	friend class Prop;
	friend class Root;

	enum {
		INITIAL_UP_CAPACITY = 32,
		INITIAL_DOWN_CAPACITY = 4
	};

	// base
	index :: Arity   index_;
	value :: Integer minHeight_;
	Expression_* expression_;

	// variant tree
	NodeVector_ up_;
	NodeVector_ down_;

	// clone
	mutable Hyp* clone_;

	// all proof evidences
	EvidenceVector_ evidences_;

	// for self-learning algorithms: a true proof hint
	const mdl :: proof :: Node* hint_;
};

}
}
}

#endif /*MDL_PROVER_NODE_HYP_HPP_*/
