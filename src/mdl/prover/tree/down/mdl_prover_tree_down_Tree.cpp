/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_tree_down_Tree.cpp                            */
/* Description:     evidence tree                                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_TREE_DOWN_TREE_CPP_
#define MDL_PROVER_TREE_DOWN_TREE_CPP_

namespace mdl {
namespace prover {
namespace tree {
namespace down {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Tree<A> :: Tree (MainTree_* mainTree, Root_* root) :
	mainTree_ (mainTree),
	crown_ (new Crown_ (mainTree, this)),
	tree_ (INITIAL_TREE_HEIGHT),
	root_ (root),
	height_ (0),
	nodeVolume_ (0),
	isBlocked_ (false),
	evidenceVector_ (INITIAL_VECTOR_CAPACITY),
	mutex_ (),
	unusedEvidences_ (INITIAL_LEVEL_CAPACITY)
	{
		pthread_mutex_init (&mutex_, NULL);
		for (value :: Integer i = 0; i < INITIAL_TREE_HEIGHT; ++ i) {
			Level_* level = NULL;
			if (i == 0) {
				level = new Level_ (INITIAL_ROOT_CAPACITY);
			} else {
				level = new Level_ (INITIAL_LEVEL_CAPACITY);
			}
			tree_.add (level);
		}
	}
	template<class A>
	Tree<A> :: ~ Tree() {
		deleteAggregateObject (crown_);
	}

	template<class A>
	inline void
	Tree<A> :: block() {
		isBlocked_ = true;
	}
	template<class A>
	inline void
	Tree<A> :: unblock() {
		isBlocked_ = false;
	}
	template<class A>
	inline bool
	Tree<A> :: isBlocked() {
		return isBlocked_;
	}
	template<class A>
	inline typename Tree<A> :: Crown_*
	Tree<A> :: crown() {
		return crown_;
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;
using manipulator :: iterate;

	// prover :: Tree implementation
	template<class A>
	inline bool
	Tree<A> :: grow() {
		switch (Config :: growDownMode()) {
		case Config :: GROW_DOWN_DELAYED :
		case Config :: GROW_DOWN_DETERMINED :
			return crown_->grow();
		case Config :: GROW_DOWN_IMMEDIATE :
		default :
			return false;
		}
	}
	template<class A>
	void
	Tree<A> :: add (Evidence_* node)
	{
		if (isBlocked_) {
			#ifdef TREE_GROW_DOWN_MULTY_THREADED
			pthread_mutex_lock (&mutex_);
			#endif
			unusedEvidences_.add (node);
			#ifdef TREE_GROW_DOWN_MULTY_THREADED
			pthread_mutex_unlock (&mutex_);
			#endif
			return;
		}
		if (node == NULL) {
			return;
		}
		#ifdef TREE_GROW_DOWN_MULTY_THREADED
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
				tree_.add (new Level_ (INITIAL_LEVEL_CAPACITY));
			}
		}
		Level_* level = tree_.getValue (height);
		const value :: Integer levelIndex = level->getSize();
		level->add (node);
		node->setLevelIndex (levelIndex);

		const value :: Integer globalIndex = evidenceVector_.getSize();
		evidenceVector_.add (node);
		node->setGlobalIndex(globalIndex);

		typedef evidence :: Top<Allocator_> Top;
		typedef evidence :: Sub<Allocator_> Sub;

		switch (Config :: growDownMode()) {
		case Config :: GROW_DOWN_IMMEDIATE :
			crown_->add (node);
			if (dynamic_cast<Sub*>(node) != NULL && height == 0) {
				root_->add (node);
			}
			break;
		case Config :: GROW_DOWN_DELAYED :
		case Config :: GROW_DOWN_DETERMINED :
			if (dynamic_cast<Sub*>(node) != NULL) {
				if (height > 0) {
					crown_->add (node);
				} else {
					root_->add (node);
				}
			}
			break;
		default : break;
		}
		++ nodeVolume_;

		#ifdef TREE_GROW_DOWN_MULTY_THREADED
		pthread_mutex_unlock (&mutex_);
		#endif
	}
	template<class A>
	void
	Tree<A> :: remove (Evidence_* node)
	{
		if (node == NULL) {
			return;
		}
		pthread_mutex_lock (&mutex_);
		const value :: Integer height = node->getMinHeight();
		Level_* level = tree_.getValue (height);
		level->remove (node);
		-- nodeVolume_;
		pthread_mutex_unlock (&mutex_);
	}
	template<class A>
	bool
	Tree<A> :: contains (Evidence_* evidence) const
	{
		for (value :: Integer i = 0; i < height_ + 1; ++ i) {
			const Level_* level = tree_.getValue (i);
			if (level->contains (evidence)) {
				return true;
			}
		}
		return false;
	}
	template<class A>
	inline const typename Tree<A> :: Crown_*
	Tree<A> :: getCrown() const {
		return crown_;
	}
	template<class A>
	inline value :: Integer
	Tree<A> :: getNodeVolume() const {
		return nodeVolume_;
	}
	template<class A>
	value :: Integer
	Tree<A> :: getEvidenceNumber() const {
		return evidenceVector_.getSize();
	}
	template<class A>
	typename Tree<A> :: Evidence_*
	Tree<A> :: getEvidence (const value :: Integer i) {
		return evidenceVector_.getValue (i);
	}
	template<class A>
	const typename Tree<A> :: Evidence_*
	Tree<A> :: getEvidence (const value :: Integer i) const {
		return evidenceVector_.getValue (i);
	}

	template<class A>
	void
	Tree<A> :: showInfo (String& string, const int indent) const
	{
		MainTree_ :: writeHeader (string, "down", indent);
		for (value :: Integer i = 0; i < evidenceVector_.getSize(); ++ i) {
			const Evidence_* evidence = evidenceVector_.getValue (i);
			evidence->showInfo (string, indent + 1);
		}
		MainTree_ :: writeEnding (string, "down", indent);
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
		volume += evidenceVector_.getVolume();
		volume += unusedEvidences_.getVolume();
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
		const Mode mode (string);
		if (mode.getValue (Mode :: SHOW_IN_GML_GRAPH)) {
			//clearMapped();
			string << "graph [" << endLine;
			string << tab << "directed 1" << endLine;
			string << tab << "id " << 1 << endLine;
			//string << tab << "label \"size = " << evidences_.getSize();
			//string << "\"" << endLine;
			string << tab << "label \"evidences\"" << endLine;
			const Mode mOld (string);
			Mode mNew (mOld);
			mNew.setValue (Mode :: SHOW_IN_GML_GRAPH, false);
			mNew.setValue (Mode :: SHOW_IN_GML, true);
			string << mode << mNew;
			show (string);
			string << mode << mOld;
			string << "]" << endLine;
			string << endLine;
		} else if (mode.getValue (Mode :: SHOW_IN_GML)) {
			Level_* root = tree_.getFirstValue();
			for (value :: Integer i = 0; i < root->getSize(); ++ i) {
				const Evidence_*
					evidence = root->getValue (i);
				evidence->show (string);
			}
			showNodesInGML (string);
			//crown_->show (string);
		} else {
			if (mode.getValue (Mode :: SHOW_DOWN_TREE_CARD)) {
				if (mode.getValue (Mode :: END_LINE)) {
					string << tab;
				}
				if (mode.getValue (Mode :: SHOW_FULL_DESCRIPTION)) {
					string << "down tree card: " << nodeVolume_ << " nodes";
				} else {
					string << "dn: " << nodeVolume_;
				}
				if (mode.getValue (Mode :: END_LINE)) {
					string << endLine;
				} else {
					string << ", ";
				}
			}
			/*if (mode.getValue (Mode :: SHOW_DOWN_ROOT_CARD)) {
				if (mode.getValue (Mode :: END_LINE)) {
					string << tab;
				}
				string << "down root card: " << getRootSize() << " nodes";
				if (mode.getValue (Mode :: END_LINE)) {
					string << endLine;
				} else {
					string << ", ";
				}
			}*/
			if (mode.getValue (Mode :: SHOW_DOWN_TREE_VOLUME)) {
				if (mode.getValue (Mode :: END_LINE)) {
					string << tab;
				}
				const Size_t volume = getVolume();
				if (mode.getValue (Mode :: SHOW_FULL_DESCRIPTION)) {
					string << "down tree volume: ";
				} else {
					string << "dn_vol: ";
				}
				memory :: Unit :: show (string, volume);
				if (mode.getValue (Mode :: END_LINE)) {
					string << endLine;
				} else {
					string << ", ";
				}
			}
			crown_->show (string);
		}
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
			for (value :: Integer j = 0; j < level->getSize(); ++ j) {
				const Evidence_* node = level->getValue (j);
				const Prop_*
					p = dynamic_cast<const Prop_*>(node);
				/*if (p != NULL) {
					string << tab << "prop = ";
					node->getProposition()->getAssertion()->replicateName (string);
					string << ", ";
					string << tab << "down = " << *node->getExpression() << endLine;
					continue;
				}
				const node :: Hyp*
					h = dynamic_cast<const node :: Hyp*>(node);
				if (h != NULL) {
					string << tab << "hyp = " << *node->getExpression() << endLine;
					continue;
				}
				const node :: Root*
					r = dynamic_cast<const node :: Root*>(node);
				if (r != NULL) {
					string << tab << "prop = ";
					node->getProposition()->getAssertion()->replicateName (string);
					string << endLine;
					continue;
				}*/
				//string << tab << *node->getExpression() << endLine;
			}
			string <<  endLine;
		}
		string << endLine << endLine;
	}

	template<class A>
	value :: Integer
	Tree<A> :: getNodeCount() const
	{
		value :: Integer count = 0;
		for (value :: Integer i = 0; i < height_ + 1; ++ i) {
			Level_* level = tree_.getValue (i);
			count += level->getSize();
		}
		return count;
	}
	template<class A>
	void
	Tree<A> :: clearMapped()
	{
		for (value :: Integer i = 0; i < height_ + 1; ++ i) {
			Level_* level = tree_.getValue (i);
			for (value :: Integer j = 0; j < level->getSize(); ++ j) {
				Evidence_* evidence = level->getValue (j);
				evidence->mapped_ = false;
			}
		}
	}
	template<class A>
	void
	Tree<A> :: showNodesInGML (String& string) const
	{
		for (value :: Integer i = 0; i < height_ + 1; ++ i) {
			const Level_* level = tree_.getValue (i);
			for (value :: Integer j = 0; j < level->getSize(); ++ j) {
				const Evidence_* evidence = level->getValue (j);
				evidence->show (string);
			}
		}
	}
}
}
}
}

#endif /*MDL_PROVER_TREE_DOWN_TREE_CPP_*/
