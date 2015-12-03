/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_evidence_Prop.hpp                             */
/* Description:     prop proof evidence element                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_EVIDENCE_PROP_HPP_
#define MDL_PROVER_EVIDENCE_PROP_HPP_

#include "mdl/prover/mdl_prover.dpp"

namespace mdl {
namespace prover {
namespace evidence {

template<class A>
class Prop :
	public Evidence<A>,
	public Scalar<Prop<A>, A> {
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

	Prop
	(
		Node_* node,
		const index :: Arity,
		Evidence_* up[],
		Substitution_* = NULL
	);
	virtual ~ Prop();

	index :: Arity getArity() const;

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
		typename node :: Prop<Allocator_>
		Prop_;
	typedef
		typename mdl :: array :: Array
		<
			Evidence_*,
			storage :: ByValue,
			Allocator_
		>
		Array_;

	void verifyUp() const;
	void verifySubstitutions() const;
	void verifyVariables (const Substitution_*) const;
	void verifyVariable (const Symbol&, const Substitution_*) const;
	void showVerification (String&) const;

	void showNodeInGML (String&) const;
	void showNodePlain (String&) const;

	Substitution_* substitution_;
	Array_ up_;
	Evidence_* down_;

	const index :: Step depth_;
	const value :: Integer cardinality_;
	mutable Prop* clone_;
};

}
}
}

#endif /*MDL_PROVER_EVIDENCE_PROP_HPP_*/
