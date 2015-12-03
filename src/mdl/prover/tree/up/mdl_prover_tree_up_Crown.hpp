/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_tree_up_Crown.hpp                             */
/* Description:     crown (top) in proof variant tree                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_TREE_UP_CROWN_HPP_
#define MDL_PROVER_TREE_UP_CROWN_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/prover/mdl_prover.dpp"

namespace mdl {
namespace prover {
namespace tree {
namespace up {

template<class A>
class Crown :
	public object :: Object,
	public Scalar<Crown<A>, A> {
public :
	typedef A Allocator_;
	typedef Prop<Allocator_> Prop_;
	typedef Tree<Allocator_> Tree_;
	typedef
		typename tree :: Tree<Allocator_> MainTree_;
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

	enum Mode_ {
		UNRESTRICTED,        //< No restrictions on new nodes
		RESTRICT_COMPLEXITY, //< Restrict nodes with maximal complexity of expressions
		RESTRICT_TO_HINTS,   //< Grow only those nodes, who have hints (true proof)
		RESTRICT_HEIGHT      //< Restrict the tree with the current height
	};

	Crown (MainTree_*, Tree_*);
	virtual ~ Crown();

	// prover :: Crown interface
	void setMode (Mode_);
	bool grow();
	void grow(Node_*);
	void add (Node_*);
	bool contains (Node_*);
	void removeNonHintLevels (const value :: Integer);
	void showPartition (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	template<class>
	friend class tree :: Tree;

	enum {
		INITIAL_HEIGHT                = 2,
		INITIAL_LEVEL_CAPACITY        = size :: KILOBYTE * 4,
		INITIAL_LEVEL_VECTOR_CAPACITY = 32,  // crown levels capacity
		NEW_LEVEL_TREE_SIZE_DELTA     = 1024 // delta of a tree size, at which the crown adds a new level
	};

	typedef
		Level<Allocator_, storage :: ByWeakPointer>
		Level_;

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
			Node_*,
			storage :: ByValue,
			Allocator_
		>
		NodeVector_;

	enum NextNodePolicy_ {
		NORMAL_NEXT_NODE    = 0,
		ONLY_HINT_NEXT_NODE = 1,
		RESTRICT_EXPR_COMPLEXITY_NEXT_NODE = 2
	};

	void incIndex();
	void incCrown();
	bool newLevel() const;
	Level_* nextLevel();
	Level_* popFromLevel(Node_*);

	value :: Integer getHeight() const;
	value :: Integer getSize() const;
	value :: Integer getMinHintIndex (const value :: Integer) const;
	double getMinHintPercent (const value :: Integer) const;

	Node_* takeNode();

	enum {
		NODES_TO_PROCESS_IN_PARALLEL = 64,
		SINGLE_THREADED_THRESHOLD    = 2
	};

	bool growSingleThreaded();
	bool growMultyThreaded ();

	template<class>
	friend void* growInThread (void* pointer);
	struct Arguments_ {
		Arguments_() :
		threadIndex_ (0),
		threadCount_ (0),
		nodes_ (NULL),
		crown_ (NULL) {
		}
		int threadIndex_;
		int threadCount_;
		NodeVector_* nodes_;
		Crown*       crown_;
	};

	void showBreefly (String&) const;
	void showTreeStatistics (String&) const;
	void showHintStatistics (String&) const;

	MainTree_*       mainTree_;
	Tree_*           tree_;
	LevelVector_     levelVector_;
	value :: Integer heightMin_;
	value :: Integer heightMax_;
	value :: Integer index_;

	bool onlyHint_;
	bool limitHeight_;
	bool restricted_;

	mutable Timer timer_;
	mutable value :: Integer counter_;
};

	template<class>
	void* growInThread (void* pointer);
}
}
}
}

#endif /*MDL_PROVER_TREE_UP_CROWN_HPP_*/
