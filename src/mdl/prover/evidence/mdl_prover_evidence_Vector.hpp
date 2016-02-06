/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_evidence_Vector.hpp                           */
/* Description:     evidences: vector of evidences                           */
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

template<class A, bool D>
class Vector :
	public Evidences<A>,
	public Scalar<Vector<A, D>, A> {
public :
	typedef A Allocator_;
	enum {
		duplicate_ = D
	};
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

	Vector (Node_*);
	virtual ~ Vector();

	virtual bool isEqual (const Vector*) const;
	virtual void showDifference (String&, const Vector*) const;

	void showSubstitutions (String&, const bool = false) const;

	// prover :: Evidences interface
	virtual void checkForDuplicateProofs();
	virtual void add (const stack :: Substitution*, Evidence_* up);
	virtual void verifyIntegrity() const;
	virtual value :: Integer getSize() const;
	virtual void add (Evidence_*);
	virtual Evidence_* getValue (const value :: Integer);
	virtual Node_* getNode();
	virtual const Evidence_* getValue (const value :: Integer) const;
	virtual void show (String&, const int indent = 0) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	template<class>
	friend class node :: Prop;

	typedef Hyp<Allocator_> Hyp_;
	typedef Prop<Allocator_> Prop_;
	typedef Ref<Allocator_> Ref_;
	typedef Sub<Allocator_> Sub_;
	typedef Top<Allocator_> Top_;

	typedef
		mdl :: vector :: Vector
		<
			Evidence_*,
			storage :: ByValue,
			Allocator_
		>
		EvidenceVector_;

	bool containsSameProof (const Evidence_*) const;
	bool containsSubstitution (const Evidence_*) const;
	void showDiffSubset (String&, const Vector*) const;
	bool isSubset (const Vector*) const;

	void addWithoutDuplicate (const stack :: Substitution*, Evidence_* up);
	void addWithDuplicate (const stack :: Substitution*, Evidence_* up);

	enum {
		INITIAL_EVIDENCE_VECTOR_CAPACITY = 8
	};

	Node_* node_;
	EvidenceVector_ evidenceVector_;
};

}
}
}


