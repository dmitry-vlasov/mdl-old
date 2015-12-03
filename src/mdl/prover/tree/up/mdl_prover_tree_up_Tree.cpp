/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_tree_up_Tree.cpp                              */
/* Description:     variant tree                                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_TREE_UP_TREE_CPP_
#define MDL_PROVER_TREE_UP_TREE_CPP_

namespace mdl {
namespace prover {
namespace tree {
namespace up {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	Tree<A> :: Tree (MainTree_* mainTree) :
	mainTree_ (mainTree),
	crown_ (new Crown_ (mainTree, this)),
	tree_ (INITIAL_TREE_HEIGHT),
	root_ (NULL),
	height_ (0),
	expressionVolume_ (0),
	mutex_ (),
	nodeSet_ (INITIAL_NODE_STORAGE_CAPACITY),
	nodeVector_ (INITIAL_NODE_STORAGE_CAPACITY),
	nodeSprout_ (INITIAL_NODE_SPROUT_CAPACITY)
	{
		pthread_mutex_init (&mutex_, NULL);
		for (value :: Integer i = 0; i < INITIAL_TREE_HEIGHT; ++ i) {
			tree_.add (new Level_());
		}
	}
	template<class A>
	Tree<A> :: ~ Tree()
	{
		deleteAggregateObject (crown_);
		root_ = NULL;
		nodeSet_.clear();
		nodeVector_.clear();
		nodeSprout_.clear();
	}

	template<class A>
	void
	Tree<A> :: createRoot (Expression_* expression, const mdl :: proof :: Step* hint)
	{
		root_ = new Hyp_ (mainTree_, expression, hint);
		root_->setGlobalIndex(0); // the first node in the tree
		root_->setLevelIndex(0);  // the first node in the tree
	}

	template<class A>
	inline typename Tree<A> :: Node_*
	Tree<A> :: getNode (const value :: Integer index) const {
		return nodeVector_.getValue (index);
	}
	template<class A>
	inline value :: Integer
	Tree<A> :: getSize () const {
		return nodeVector_.getSize();
	}
	template<class A>
	inline value :: Integer
	Tree<A> :: getHeight() const {
		return height_;
	}
	template<class A>
	inline value :: Integer
	Tree<A> :: getLevelWidth (const value :: Integer i) const
	{
		Level_* level = tree_.getValue (i);
		return level->getSize();
	}
	template<class A>
	value :: Real
	Tree<A> :: evalFitness() const
	{
		value :: Integer sumBoundary = 0;
		value :: Integer sumSize = 0;
		evalPartition (sumBoundary, sumSize);
		return static_cast<value :: Real>(sumBoundary) * 100 / sumSize;
	}
	template<class A>
	void
	Tree<A> :: evalPartition (value :: Integer& sumBoundary, value :: Integer& sumSize) const
	{
		value :: Integer boundary = 0;
		value :: Integer size = 0;
		for (value :: Integer i = 0; i < height_ + 1; ++ i) {
			const Level_* level = tree_.getValue (i);
			level->evalPartition (boundary, size);
			sumBoundary += boundary;
			sumSize += size;
		}
	}
	template<class A>
	void
	Tree<A> :: showPartition (String& string) const
	{
		const Mode mode (string);
		for (value :: Integer i = 0; i < height_ + 1; ++ i) {
			const Level_* level = tree_.getValue (i);

			if (mode.getValue (Mode :: END_LINE)) {
				string << tab << tab;
			}
			if (mode.getValue (Mode :: SHOW_FULL_DESCRIPTION)) {
				string << "level ";
			} else {
				string << "lev ";
			}
			string << i << " : ";
			level->showPartition (string);
			//string << "], ";
			if (mode.getValue (Mode :: END_LINE)) {
				string << endLine;
			} else {
				string << ", ";
			}
		}
	}
	template<class A>
	void
	Tree<A> :: removeNonHintLevels()
	{
		for (value :: Integer i = 0; i < height_ + 1; ++ i) {
			const value :: Integer k = height_ - i;
			Level_* level = tree_.getValue (k);
			bool hint = false;
			for (value :: Integer j = 0; j < level->getSize(); ++ j) {
				const Node_* node = level->getValue (j);
				if (node->getHint() != NULL) {
					hint = true;
					break;
				}
			}
			if (!hint) {
				for (value :: Integer j = 0; j < level->getSize(); ++ j) {
					Node_* node = level->getValue (j);
					nodeSet_.removeValue (node);
				}
				level->commitSuicide();
				tree_.remove (k);
			} else {
				height_ = k;
				break;
			}
		}
		crown_->removeNonHintLevels (height_);
	}

	// prover :: Tree implementation
	template<class A>
	inline bool
	Tree<A> :: grow()
	{
		nodeSprout_.clear();
		if (Config :: runServer() &&
			Config :: growUpMode() != Config :: GROW_UP_DETERMINED) {
			const value :: Integer index = Config :: getInteger(Config :: INDEX);
			if (index < nodeVector_.getSize()) {
				Node_* node = nodeVector_.getValue (index);
				if (crown_->contains (node)) {
					crown_->grow (node);
					return true;
				} else {
					return false;
				}
			} else {
				return false;
			}
		} else {
			return crown_->grow();
		}
	}
	template<class A>
	void
	Tree<A> :: add (Node_* node)
	{
		if (node == NULL) {
			return;
		}
		#ifdef TREE_GROW_UP_MULTY_THREADED
		pthread_mutex_lock (&mutex_);
		#endif
		const value :: Integer height = node->getMinHeight();
		if (height_ < height) {
			height_ = height;
		}
		if (height >= tree_.getSize()) {
			const value :: Integer
				toAdd = 1 + height - tree_.getSize();
			for (value :: Integer i = 0; i < toAdd; ++ i) {
				tree_.add (new Level_());
			}
		}

		const value :: Integer globalIndex = nodeVector_.getSize();
		node->setGlobalIndex(globalIndex);
		nodeVector_.add (node);

		Level_* level = tree_.getValue (height);
		const value :: Integer levelIndex = level->getSize();
		level->add (node);
		if (node->mayGrowUp()) {
			crown_->add (node);
		}
		node->setLevelIndex (levelIndex);
		nodeSet_.add (node);
		nodeSprout_.add (node);

		expressionVolume_ += node->getExpression()->getComplexity();

		#ifdef DEBUG_PROVER_UP
		//node->verifyIntegrity();
		#endif

		#ifdef TREE_GROW_UP_MULTY_THREADED
		pthread_mutex_unlock (&mutex_);
		#endif
	}
	template<class A>
	inline typename Tree<A> :: Node_*
	Tree<A> :: getRoot () {
		return root_;
	}
	template<class A>
	inline const typename Tree<A> :: Node_*
	Tree<A> :: getRoot () const {
		return root_;
	}
	template<class A>
	inline const typename Tree<A> :: Crown_*
	Tree<A> :: getCrown() const {
		return crown_;
	}
	template<class A>
	inline value :: Integer
	Tree<A> :: getNodeVolume() const {
		return nodeSet_.getSize();
	}
	template<class A>
	inline value :: Integer
	Tree<A> :: getExpressionVolume() const {
		return expressionVolume_;
	}

	template<class A>
	inline const typename Tree<A> :: NodeSet_&
	Tree<A> :: getNodeSet() const {
		return nodeSet_;
	}
	template<class A>
	inline const typename Tree<A> :: NodeVector_&
	Tree<A> :: getNodeVector() const {
		return nodeVector_;
	}
	template<class A>
	inline const typename Tree<A> :: NodeVector_&
	Tree<A> :: getNodeSprout() const {
		return nodeSprout_;
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;
using manipulator :: iterate;

	template<class A>
	void
	Tree<A> :: showInfo (String& string, const int indent) const
	{
		MainTree_ :: writeHeader (string, "up", indent);
		if (Config :: growCompleteTree()) {
			if (nodeVector_.getSize() == 1) {
				// Root case
				const Node_* node = nodeVector_.getValue (0);
				node->showInfo (string, indent + 1);
			} else {
				// All other nodes
				for (value :: Integer i = 1; i < nodeVector_.getSize(); ++ i) {
					const Node_* node = nodeVector_.getValue (i);
					node->showInfo (string, indent + 1);
				}
			}
		} else {
			const NodeVector_& nodes =
				Config :: infoTree (Config :: SHOW_TREE_SPROUT) ?
				nodeSprout_ :
				nodeVector_;
			for (value :: Integer i = 0; i < nodes.getSize(); ++ i) {
				const Node_* node = nodes.getValue (i);
				node->showInfo (string, indent + 1);
			}
		}
		MainTree_ :: writeEnding (string, "up", indent);
	}

	// object :: Object implementation
	template<class A>
	void
	Tree<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Tree<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (crown_);
		volume += tree_.getVolume();
		volume += nodeSet_.getVolume();
		volume += nodeVector_.getVolume();
		volume += nodeSprout_.getVolume();
		return volume;
	}
	template<class A>
	Size_t
	Tree<A> :: getSizeOf() const {
		return sizeof (Tree);
	}
	template<class A>
	void
	Tree<A> :: show (String& string) const
	{
		mainTree_->format_.setOutput (string);
		const Mode mode (string);
		if (mode.getValue (Mode :: SHOW_IN_GML_GRAPH)) {
			root_->show (string);
		} if (mode.getValue (Mode :: SHOW_UP_TREE_LEVELS)) {
			showTreeStatistics (string);
		} else {
			if (mode.getValue (Mode :: SHOW_UP_TREE_CARD)) {
				if (mode.getValue (Mode :: END_LINE)) {
					string << tab;
				}
				if (mode.getValue (Mode :: SHOW_FULL_DESCRIPTION)) {
					string << "up tree card: " << getNodeVolume() << " nodes";
				} else {
					string << "up: " << getNodeVolume();
				}
				if (mode.getValue (Mode :: END_LINE)) {
					string << endLine;
				} else {
					string << ", ";
				}
			}
			if (mode.getValue (Mode :: SHOW_UP_TREE_EXP_VOLUME)) {
				if (mode.getValue (Mode :: END_LINE)) {
					string << tab;
				}
				if (mode.getValue (Mode :: SHOW_FULL_DESCRIPTION)) {
					string << "up tree exp volume: " << getExpressionVolume() << " nodes";
				} else {
					string << "up exp vol: " << getExpressionVolume();
				}
				if (mode.getValue (Mode :: END_LINE)) {
					string << endLine;
				} else {
					string << ", ";
				}
			}
			if (mode.getValue (Mode :: SHOW_UP_TREE_LEVELS_CARD)) {
				if (mode.getValue (Mode :: SHOW_FULL_DESCRIPTION)) {
					string << "level cards: ";
				} else {
					"lvl: ";
				}
				for (value :: Integer i = 0; i < height_ + 1; ++ i) {
					Level_* level = tree_.getValue (i);
					string << "l_" << i << "=" << level->getSize();
					if (i == height_) {
						string << "; ";
					} else {
						string << ", ";
					}
				}
			}
			if (mode.getValue (Mode :: SHOW_UP_TREE_VOLUME)) {
				if (mode.getValue (Mode :: END_LINE)) {
					string << tab;
				}
				const Size_t volume = getVolume();
				if (mode.getValue (Mode :: SHOW_FULL_DESCRIPTION)) {
					string << "up tree volume: ";
				} else {
					string << "up_vol: ";
				}
				memory :: Unit :: show (string, volume);
				if (mode.getValue (Mode :: END_LINE)) {
					string << endLine;
				} else {
					string << ", ";
				}
			}
			if (mode.getValue (Mode :: SHOW_UP_TREE_FITNESS)) {
				if (mode.getValue (Mode :: END_LINE)) {
					string << tab;
				}
				if (mode.getValue (Mode :: SHOW_FULL_DESCRIPTION)) {
					string << "up tree fitness: ";
				} else {
					string << "fitness: ";
				}
				const value :: Real fitness = evalFitness();
				string << fitness;
				if (mode.getValue (Mode :: END_LINE)) {
					string << endLine;
				} else {
					string << ", ";
				}
			}
			if (mode.getValue (Mode :: SHOW_UP_TREE_PARTITION)) {
				if (mode.getValue (Mode :: END_LINE)) {
					string << tab;
				}
				if (mode.getValue (Mode :: SHOW_FULL_DESCRIPTION)) {
					string << "up tree partition: ";
				} else {
					string << "partition: ";
				}
				if (mode.getValue (Mode :: END_LINE)) {
					string << endLine;
				}
				showPartition (string);
				if (mode.getValue (Mode :: END_LINE)) {
					string << endLine;
				} else {
					string << ", ";
				}
			}
			crown_->show (string);
		}
		mainTree_->format_.unsetOutput();
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	void
	Tree<A> :: showTreeStatistics (String& string) const
	{
		string << "tree statistics:" << endLine;
		string << "------------------" << endLine;
		string << "depth:" << tab;
		for (value :: Integer i = 0; i < height_ + 1; ++ i) {
			string <<  i << tab;
		}
		string << endLine;
		string << "level:" << tab;
		for (value :: Integer i = 0; i < height_ + 1; ++ i) {
			Level_* level = tree_.getValue (i);
			string <<  level->getSize() << tab;
		}
		string << endLine << "--------------------------------" << endLine;
		for (value :: Integer i = 0; i < height_ + 1; ++ i) {
			Level_* level = tree_.getValue (i);
			string << "level: " << i << endLine;
			level->show (string);
		}
		string << endLine << endLine;
	}
}
}
}
}

#endif /*MDL_PROVER_TREE_UP_TREE_CPP_*/
