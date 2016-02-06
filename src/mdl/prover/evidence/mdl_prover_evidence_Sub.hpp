/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_evidence_Sub.hpp                              */
/* Description:     common substitution proof evidence element               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/prover/mdl_prover.dpp"

namespace mdl {
namespace prover {
namespace evidence {

template<class A>
class Sub :
	public Evidence<A>,
	public Scalar<Sub<A>, A> {
public :
	typedef A Allocator_;
	typedef Types<Allocator_> Types_;
	typedef
		typename Types_ :: Substitution_
		Substitution_;
	typedef
		typename Types_ :: Node_
		Node_;
	typedef
		typename Types_ :: Evidence_
		Evidence_;
	typedef
		typename Types_ :: Proof_
		Proof_;

	Sub (Node_* node, Evidence_* up, Substitution_*, bool confirm = true);
	virtual ~ Sub();

	value :: Integer getSize() const;
	void addUp (Evidence_*);
	void clearUp();
	void confirm();

	// prover :: Evidence interface
	virtual bool growDown();
	virtual void setDown (Evidence_*);
	virtual value :: Integer getUpForking() const;
	virtual value :: Integer getDownForking() const;
	virtual Evidence_* getUp (const value :: Integer);
	virtual Evidence_* getDown (const value :: Integer = 0);
	virtual const Evidence_* getUp (const value :: Integer) const;
	virtual const Evidence_* getDown (const value :: Integer = 0) const;
	virtual void verifyIntegrity() const;
	virtual Substitution_* getSubstitution();
	virtual const Substitution_* getSubstitution() const;
	virtual index :: Step getDepth() const;
	virtual value :: Integer getCardinality() const;
	virtual Proof_* constructProof (const Substitution_* = NULL);
	virtual bool givesSameProof (const Evidence_*) const;

	// object :: Cloneable interface
	virtual Evidence_* clone() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	template<class>
	friend class proof :: Prop;

	typedef
		typename mdl :: vector :: Vector
		<
			Evidence_*,
			storage :: ByValue,
			Allocator_
		>
		EvidenceVector_;

	typedef
		typename mdl :: vector :: Vector
		<
			Node_*,
			storage :: ByValue,
			Allocator_
		>
		NodeVector_;

	void showNodeInGML (String&) const;
	void showNodePlain (String&) const;

	Substitution_* substitution_;
	EvidenceVector_ up_;

	const index :: Step depth_;
	const value :: Integer cardinality_;
	mutable Evidence_* clone_;

	mutable NodeVector_ down_;
};

}
}
}


