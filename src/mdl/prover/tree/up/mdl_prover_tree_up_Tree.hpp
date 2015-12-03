/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_tree_up_Tree.hpp                              */
/* Description:     variant tree                                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_TREE_UP_TREE_HPP_
#define MDL_PROVER_TREE_UP_TREE_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/prover/mdl_prover.dpp"
#include "mdl/prover/node/mdl_prover_node.hpp"
#include "mdl/prover/tree/up/mdl_prover_tree_up_Level.hpp"

namespace mdl {
namespace prover {
namespace tree {
namespace up {

template<class A>
class Tree :
	public object :: Object,
	public Scalar<Tree<A>, A> {
public :
	typedef A Allocator_;
	typedef Crown<Allocator_> Crown_;
	typedef node :: Hyp<Allocator_> Hyp_;
	typedef node :: Prop<Allocator_> Prop_;
	typedef node :: Ref<Allocator_> Ref_;
	typedef node :: Top<Allocator_> Top_;
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

	typedef
		mdl :: set :: Set
		<
			Node_*,
			storage :: ByValue,
			Allocator_
		>
		NodeSet_;
	typedef
		mdl :: vector :: Vector
		<
			Node_*,
			storage :: ByValue,
			Allocator_
		>
		NodeVector_;

	Tree (MainTree_* mainTree);
	virtual ~ Tree();

	void createRoot (Expression_* expression, const mdl :: proof :: Step* hint);

	Node_* getNode (const value :: Integer) const;
	value :: Integer getSize () const;
	value :: Integer getHeight() const;
	value :: Integer getLevelWidth (const value :: Integer) const;
	value :: Real evalFitness() const;
	void evalPartition (value :: Integer&, value :: Integer&) const;
	void showPartition (String&) const;
	void removeNonHintLevels();

	// prover :: Tree interface
	bool grow();
	void add (Node_*);
	Node_* getRoot();
	const Node_* getRoot() const;
	const Crown_* getCrown() const;
	value :: Integer getNodeVolume() const;
	value :: Integer getExpressionVolume() const;

	const NodeSet_& getNodeSet() const;
	const NodeVector_& getNodeVector() const;
	const NodeVector_& getNodeSprout() const;

	void showInfo (String&, const int indent = 0) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	friend class data :: Up;
	template<class>
	friend class tree :: Tree;

	enum {
		INITIAL_TREE_HEIGHT = 32,
		INITIAL_NODE_STORAGE_CAPACITY = size :: KILOBYTE,
		INITIAL_NODE_SPROUT_CAPACITY  = 32
	};

	typedef
		Level<Allocator_, storage :: ByPointer>
		Level_;

	typedef
		mdl :: vector :: Vector
		<
			Level_,
			storage :: ByPointer,
			Allocator_
		>
		LevelVector_;

	void showTreeStatistics (String&) const;

	MainTree_*    mainTree_;
	Crown_*       crown_;
	LevelVector_  tree_;
	Node_*        root_;
	value :: Integer height_;
	value :: Integer expressionVolume_;
	pthread_mutex_t mutex_;

	NodeSet_    nodeSet_;
	NodeVector_ nodeVector_;
	NodeVector_ nodeSprout_;
};

}
}
}
}

#endif /*MDL_PROVER_TREE_UP_TREE_HPP_*/
