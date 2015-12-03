/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_tree_Root.hpp                                 */
/* Description:     root of the tree                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_ROOT_ROOT_HPP_
#define MDL_PROVER_ROOT_ROOT_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/prover/mdl_prover.dpp"

namespace mdl {
namespace prover {
namespace tree {

template<class A>
class Root :
	public object :: Object,
	public Scalar<Root<A>, A> {
public :
	typedef A Allocator_;
	typedef Tree<Allocator_> Tree_;
	typedef
		Types<Allocator_> Types_;
	typedef
		typename Types_ :: PremiseTree_
		PremiseTree_;
	typedef
		typename Types_ :: ExpressionTree_
		ExpressionTree_;
	typedef
		typename Types_ :: Expression_
		Expression_;
	typedef
		typename Types_ :: Evidence_
		Evidence_;
	typedef
		typename Types_ :: Proof_
		Proof_;
	typedef
		mdl :: vector :: Vector
		<
			mdl :: proof :: Step,
			storage :: ByPointer,
			Allocator_
		>
		StepVector_;


	Root (Tree_*);
	virtual ~ Root();

	// prover :: Root interface
	value :: Integer getSize() const;
	const mdl :: proof :: Step* getProof (const value :: Integer) const;
	void update();
	bool isProved();
	void add (Evidence_*);
	void add (Proof_*);
	void verifyCompilation (const bool forceOutput = false);
	bool hasValidProofs() const;
	mdl :: proof :: Step* takeProof (const value :: Integer);
	mdl :: proof :: Step* takeBestProof();
	bool contains (const Proof_*) const;
	void showInfo (String&, const int indent = 0) const;
	void showVolume (String&, const int indent = 0) const;
	void dumpVolume () const;
	void dumpInvalidProofs() const;

	void block();
	void unblock();

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :

	friend class data :: Root;

	enum {
		INITIAL_BUFFER_CAPACITY = 8,
		INITIAL_PROOF_VECTOR_CAPACITY = 32
	};
	typedef proof :: Hyp<Allocator_>  Hyp_;
	typedef proof :: Prop<Allocator_> Prop_;
	typedef proof :: Ref<Allocator_>  Ref_;
	typedef proof :: Top<Allocator_>  Top_;

	typedef
		mdl :: vector :: Vector
		<
			Proof_,
			storage :: ByPointer,
			Allocator_
		>
		ProofVector_;

	typedef
		mdl :: vector :: Vector
		<
			Proof_*,
			storage :: ByValue,
			Allocator_
		>
		RootVector_;

	typedef
		mdl :: vector :: Vector
		<
			Evidence_*,
			storage :: ByValue,
			Allocator_
		>
		EvidenceVector_;

	void constructProofs();
	virtual void showDiffSubset (String&, const Root*) const;
	value :: Integer getLeastProofIndex() const;
	mdl :: proof :: Step* createStep (Proof_*, mdl :: proof :: Question*) const;
	mdl :: proof :: Step* createClaim (Proof_*, mdl :: proof :: Question*) const;

	mdl :: proof :: Step* createProof (Proof_*) const;
	mdl :: proof :: Step* createClaim (Proof_*) const;
	mdl :: proof :: Step* createStep (Proof_*) const;
	bool verifyProof (mdl :: proof :: Step*, const bool = false) const;
	bool verifyDuplicateProofs();
	bool verifyDuplicateEvidences() const;
	Size_t getProofsVolume() const;

	void showVolumeStatistics (String&, const int indent = 0) const;

	Tree_* tree_;
	EvidenceVector_ buffer_;
	RootVector_     rootVector_;
	ProofVector_    proofVector_;
	StepVector_     stepVector_;

	RootVector_     invalidVector_;
	ProofVector_    unusedVector_;
	bool            isBlocked_;
};

}
}
}

#endif /*MDL_PROVER_ROOT_ROOT_HPP_*/
