/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_tree_down_Tree.hpp                            */
/* Description:     evidence tree                                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_TREE_DOWN_TREE_HPP_
#define MDL_PROVER_TREE_DOWN_TREE_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/prover/mdl_prover.dpp"

namespace mdl {
namespace prover {
namespace tree {
namespace down {

template<class A>
class Tree :
	public object :: Object,
	public Scalar<Tree<A>, A> {
public :
	typedef A Allocator_;
	typedef Crown<Allocator_> Crown_;
	typedef Root<Allocator_> Root_;
	typedef
		typename tree :: Tree<Allocator_>
		MainTree_;
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
		typename Types_ :: Node_
		Node_;

	Tree (MainTree_*, Root_*);
	virtual ~ Tree();

	void block();
	void unblock();
	bool isBlocked();
	Crown_* crown();

	// prover :: Tree interface
	bool grow();
	void add (Evidence_*);
	void remove (Evidence_*);
	bool contains (Evidence_*) const;
	const Crown_* getCrown() const;
	value :: Integer getNodeVolume() const;
	value :: Integer getEvidenceNumber() const;
	Evidence_* getEvidence (const value :: Integer i);
	const Evidence_* getEvidence (const value :: Integer i) const;

	void showInfo (String&, const int indent = 0) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	friend class data :: Down;

	enum {
		INITIAL_TREE_HEIGHT = 32,
		INITIAL_LEVEL_CAPACITY  = size :: KILOBYTE,
		INITIAL_VECTOR_CAPACITY = 16, //size :: KILOBYTE * 16,
		INITIAL_ROOT_CAPACITY = 32
	};

	typedef evidence :: Hyp<Allocator_>  Hyp_;
	typedef evidence :: Prop<Allocator_> Prop_;
	typedef evidence :: Ref<Allocator_>  Ref_;
	typedef evidence :: Sub<Allocator_>  Sub_;
	typedef evidence :: Top<Allocator_>  Top_;

	typedef Level<Allocator_> Level_;

	typedef
		mdl :: vector :: Vector
		<
			Level_,
			storage :: ByPointer,
			Allocator_
		>
		LevelVector_;

	typedef
		mdl :: vector :: Vector
		<
			Evidence_*,
			storage :: ByValue,
			Allocator_
		>
		EvidenceVector_;

	void showTreeStatistics (String&) const;

	value :: Integer getNodeCount() const;
	void clearMapped();
	void showNodesInGML (String&) const;

	MainTree_*       mainTree_;
	Crown_*          crown_;
	LevelVector_     tree_;
	Root_*           root_;
	value :: Integer height_;
	value :: Integer nodeVolume_;
	bool             isBlocked_;
	EvidenceVector_  evidenceVector_;
	pthread_mutex_t  mutex_;

	typedef
		mdl :: vector :: Vector
		<
			Evidence_,
			storage :: ByPointer,
			Allocator_
		>
		UnusedEvidences_;

	UnusedEvidences_ unusedEvidences_;
};

}
}
}
}

#endif /*MDL_PROVER_TREE_DOWN_TREE_HPP_*/
