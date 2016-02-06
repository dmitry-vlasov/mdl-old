/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_tree_up_Crown.cpp                             */
/* Description:     crown (top) in proof variant tree                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace prover {
namespace tree {
namespace up {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Crown<A> :: Crown (MainTree_* mainTree, Tree_* tree) :
	mainTree_ (mainTree),
	tree_ (tree),
	levelVector_ (INITIAL_LEVEL_VECTOR_CAPACITY),
	heightMin_ (0),
	heightMax_ (INITIAL_HEIGHT),
	index_ (0),
	onlyHint_ (false),
	limitHeight_ (false),
	restricted_ (false),
	timer_ (),
	counter_ (0)
	{
		for (value :: Integer i = 0; i < getHeight() + 1; ++ i) {
			levelVector_.add (new Level_ (INITIAL_LEVEL_CAPACITY));
		}
		if (Config :: growUpMode() == Config :: GROW_UP_DETERMINED) {
			setMode (RESTRICT_TO_HINTS);
		} else {
			setMode (RESTRICT_COMPLEXITY);
		}
	}
	template<class A>
	Crown<A> :: ~ Crown() {
	}

using manipulator :: mode;

	template<class A>
	void
	Crown<A> :: setMode (Mode_ mode)
	{
		switch (mode) {
		case UNRESTRICTED :
			onlyHint_    = false;
			limitHeight_ = false;
			restricted_  = false;
			break;
		case RESTRICT_COMPLEXITY :
			onlyHint_    = false;
			limitHeight_ = false;
			restricted_  = true;
			break;
		case RESTRICT_TO_HINTS :
			onlyHint_    = true;
			limitHeight_ = false;
			restricted_  = false;
			break;
		case RESTRICT_HEIGHT :
			onlyHint_    = false;
			limitHeight_ = true;
			restricted_  = true;
			break;
		}
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;
using manipulator :: iterate;

	// prover :: Crown implementation
	template<class A>
	bool
	Crown<A> :: grow()
	{
		#ifdef TREE_GROW_UP_MULTY_THREADED
		if (Config :: getConcurrency (Config :: THREADS) == 1) {
			return growSingleThreaded();
		} else {
			return growMultyThreaded();
		}
		#else
		return growSingleThreaded();
		#endif
	}
	template<class A>
	void
	Crown<A> :: grow (Node_* node)
	{
		timer_.start();
		node->growUp();
		timer_.stop();
		++ counter_;
	}
	template<class A>
	void
	Crown<A> :: add (Node_* node)
	{
		if (node == NULL) {
			return;
		}
		const value :: Integer height = node->getMinHeight();
		if (height >= levelVector_.getSize()) {
			const value :: Integer
				toAdd = 1 + height - levelVector_.getSize();
			for (value :: Integer i = 0; i < toAdd; ++ i) {
				levelVector_.add (new Level_ (INITIAL_LEVEL_CAPACITY));
			}
		}
		if (height > heightMax_) {
			heightMax_ = height;
		}
		Level_* level = levelVector_.getValue (height);
		level->add (node);
	}
	template<class A>
	bool
	Crown<A> :: contains (Node_* node)
	{
		if (node == NULL) {
			return false;
		}
		const value :: Integer height = node->getMinHeight();
		if (height >= levelVector_.getSize()) {
			return false;
		}
		Level_* level = levelVector_.getValue (height);
		return level->contains (node);
	}
	template<class A>
	void
	Crown<A> :: removeNonHintLevels (const value :: Integer height)
	{
		for (value :: Integer i = heightMax_; i > height; -- i) {
			Level_* level = levelVector_.getValue (i);
			level->commitSuicide();
			levelVector_.remove (i);
		}
		heightMax_ = height;
		heightMin_ = 1;
		index_ = 1;
	}
	template<class A>
	void
	Crown<A> :: showPartition (String& string) const
	{
		for (value :: Integer i = heightMin_; i < heightMax_ + 1; ++ i) {
			const Level_* level = levelVector_.getValue (i);
			if (level != NULL) {
				string << "lev: " << i << " [";
				level->showPartition (string);
				string << "], ";
			}
		}
	}

	// object :: Object implementation
	template<class A>
	void
	Crown<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Crown<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += levelVector_.getVolume();
		return volume;
	}
	template<class A>
	Size_t
	Crown<A> :: getSizeOf() const {
		return sizeof (Crown);
	}
	template<class A>
	void
	Crown<A> :: show (String& string) const
	{
		showBreefly (string);
		//showTreeStatistics (string);
		//showHintStatistics (string);
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	inline void
	Crown<A> :: incIndex()
	{
		if (index_ + (limitHeight_ ? 1 : 0) < heightMax_) {
			++ index_;
		} else {
			index_ = heightMin_;
		}
	}
	template<class A>
	inline bool
	Crown<A> :: newLevel() const
	{
		const value :: Integer size_0 = NEW_LEVEL_TREE_SIZE_DELTA;
		const value :: Integer size_1 = tree_->getNodeVolume();
		const value :: Integer l = size_1 / size_0;
		return (l > getHeight());
	}
	template<class A>
	typename Crown<A> :: Level_*
	Crown<A> :: nextLevel()
	{
		incIndex();
		Level_* nextLevel = levelVector_.getValue (index_);
		if (nextLevel == NULL) {
			return NULL;
		}
		if (nextLevel->isEmpty (onlyHint_, restricted_)) {
			Level_* level = nextLevel;
			while (level->isEmpty (onlyHint_, restricted_)) {
				incIndex();
				level = levelVector_.getValue (index_);
				if (level == nextLevel) {
					return NULL;
				}
			}
			return level;
		} else {
			return nextLevel;
		}
	}
	template<class A>
	typename Crown<A> :: Level_*
	Crown<A> :: popFromLevel(Node_* node)
	{
		for (value :: Integer i = heightMin_; i < heightMax_ + 1; ++ i) {
			Level_* level = levelVector_.getValue (i);
			if (level->contains (node)) {
				level->remove (node);
				return level;
			}
		}
		return NULL;
	}

	template<class A>
	inline value :: Integer
	Crown<A> :: getHeight() const {
		return (heightMax_ - heightMin_);
	}
	template<class A>
	value :: Integer
	Crown<A> :: getSize() const
	{
		value :: Integer size = 0;
		for (value :: Integer i = heightMin_; i < heightMax_ + 1; ++ i) {
			const Level_* level = levelVector_.getValue (i);
			if (level != NULL) {
				size += level->getSize();
			}
		}
		return size;
	}
	template<class A>
	value :: Integer
	Crown<A> :: getMinHintIndex (const value :: Integer i) const
	{
		const Level_* level = levelVector_.getValue (i);
		const value :: Integer size = level->getSize();
		for (value :: Integer j = 0; j < size; ++ j) {
			Node_* node = level->getValue (j);
			if (node->getHint() != NULL) {
				return j;
			}
		}
		return value :: undefined :: INTEGER;
	}
	template<class A>
	double
	Crown<A> :: getMinHintPercent (const value :: Integer i) const
	{
		const value :: Integer index = getMinHintIndex (i);
		if (index == value :: undefined :: INTEGER) {
			return -1;
		} else {
			const Level_* level = levelVector_.getValue (i);
			const value :: Integer size = level->getSize();
			return 100 * static_cast<double>(index) / size;
		}
	}

	template<class A>
	typename Crown<A> :: Node_*
	Crown<A> :: takeNode()
	{
		Level_* level = nextLevel();
		if (level == NULL) {
			return NULL;
		}
		Node_* node =
			onlyHint_ ?
			level->takeBestHint() :
			(
				restricted_ ?
				level->takeBestRestricted() :
				level->takeBest()
			);
		if (level->isEmpty (onlyHint_, restricted_)) {
			if (index_ == heightMin_) {
				if (limitHeight_) {
					if (heightMin_ < heightMax_) {
						++ heightMin_;
					}
				} else {
					++ heightMin_;
				}
			}
		}
		if (limitHeight_) {
			if (heightMin_ == heightMax_) {
				return NULL;
			}
		} else {
			if ((heightMin_ == heightMax_) || newLevel()) {
				++ heightMax_;
				levelVector_.add (new Level_ (INITIAL_LEVEL_CAPACITY));
			}
		}
		return node;
	}

	template<class A>
	bool
	Crown<A> :: growSingleThreaded()
	{
		Node_* node = takeNode();
		if (node != NULL) {
			grow (node);
			return true;
		} else {
			return false;
		}
	}
	template<class A>
	bool
	Crown<A> :: growMultyThreaded()
	{
		const value :: Integer threadCount = Config :: getConcurrency (Config :: THREADS);
		pthread_t  threads [threadCount];
		Arguments_ arguments [threadCount];
		NodeVector_ nodeVectors [threadCount];
		Node_* allNodes [NODES_TO_PROCESS_IN_PARALLEL];
		int count = 0;
		for (int i = 0; i < NODES_TO_PROCESS_IN_PARALLEL; ++ i) {
			Node_* node = takeNode();
			if (node == NULL) {
				break;
			}
			nodeVectors [i % threadCount].add (node);
			allNodes [count] = node;
			++ count;
		}
		if (count == 0) {
			return false;
		} else if (count < SINGLE_THREADED_THRESHOLD) {
			for (int i = 0; i < count; ++ i) {
				Node_* node = allNodes [i];
				grow (node);
			}
			return true;
		} else {
			for (int i = 0; i < threadCount; ++ i) {
				arguments [i].threadIndex_ = i;
				arguments [i].threadCount_ = threadCount;
				arguments [i].crown_ = this;
				arguments [i].nodes_  = nodeVectors + i;
				pthread_create (threads + i, NULL, &growInThread<Allocator_>, reinterpret_cast<void*>(arguments + i));
			}
			Error* error = NULL;
			for (int i = 0; i < threadCount; ++ i) {
				Error* err = NULL;
				pthread_join (threads [i], reinterpret_cast<void**>(&err));
				if (err != NULL) {
					err->setNext (error);
					error = err;
				}
			}
			if (error != NULL) {
				throw error;
			} else {
				return true;
			}
		}
	}

	template<class A>
	void* growInThread (void* pointer)
	{
		typedef Crown<A> Crown;
		typedef typename Crown :: Node_ Node;
		typedef typename Crown :: Arguments_ Arguments;
		Error* error = NULL;
		Memory :: pile().registerThread();
		Arguments* arguments = reinterpret_cast<Arguments*>(pointer);
		bool success = false;
		const value :: Integer threadCount = arguments->threadCount_;
		Crown* crown = arguments->crown_;
		for (value :: Integer i = 0; i < arguments->nodes_->getSize(); ++ i) {
			Node* node = arguments->nodes_->getValue (i);
			try {
				crown->grow (node);
			} catch (Error* e) {
				error = e;
				break;
			} catch (std :: exception& exception) {
				error = new Error (Error :: SEMANTIC, exception.what());
				break;
			} catch (...) {
				error = new Error (Error :: SEMANTIC, "unknown exception.");
				break;
			}
		}
		Memory :: pile().releaseThread();
		return error;
	}

		template<class A>
	void
	Crown<A> :: showBreefly (String& string) const
	{
		const Mode mode (string);
		if (mode.getValue (Mode :: SHOW_UP_CROWN_CARD)) {
			if (mode.getValue (Mode :: END_LINE)) {
				string << tab;
			}
			if (mode.getValue (Mode :: SHOW_FULL_DESCRIPTION)) {
				string << "up crown card: " << getSize() << " nodes";
			} else {
				string << "up: " << getSize();
			}
			if (mode.getValue (Mode :: END_LINE)) {
				string << endLine;
			} else {
				string << ", ";
			}
		}
		if (mode.getValue (Mode :: SHOW_UP_CROWN_VOLUME)) {
			if (mode.getValue (Mode :: END_LINE)) {
				string << tab;
			}
			const Size_t volume = getVolume();
			if (mode.getValue (Mode :: SHOW_FULL_DESCRIPTION)) {
				string << "up crown volume: ";
			} else {
				string << "up_cr_vol: ";
			}
			memory :: Unit :: show (string, volume);
			if (mode.getValue (Mode :: END_LINE)) {
				string << endLine;
			} else {
				string << ", ";
			}
		}
		if (mode.getValue (Mode :: SHOW_UP_CROWN_H_MIN)) {
			if (mode.getValue (Mode :: END_LINE)) {
				string << tab;
			}
			if (mode.getValue (Mode :: SHOW_FULL_DESCRIPTION)) {
				string << "up crown h min: " << heightMin_;
			} else {
				string << "up_cr_h_min: ";
			}
			if (mode.getValue (Mode :: END_LINE)) {
				string << endLine;
			} else {
				string << ", ";
			}
		}
		if (mode.getValue (Mode :: SHOW_UP_CROWN_H_MAX)) {
			if (mode.getValue (Mode :: END_LINE)) {
				string << tab;
			}
			if (mode.getValue (Mode :: SHOW_FULL_DESCRIPTION)) {
				string << "up crown h max: " << heightMax_;
			} else {
				string << "up_cr_h_max: ";
			}
			if (mode.getValue (Mode :: END_LINE)) {
				string << endLine;
			} else {
				string << ", ";
			}
		}
		if (mode.getValue (Mode :: SHOW_GROW_UP_VELOCITY)) {
			if (mode.getValue (Mode :: END_LINE)) {
				string << tab;
			}
			if (mode.getValue (Mode :: SHOW_FULL_DESCRIPTION)) {
				if (timer_.getCumulativeSeconds() > 0) {
					string << "up vel: " << static_cast<value :: Integer>(counter_ / timer_.getCumulativeSeconds());
					string << "n/s";
				} else {
					string << "up vel: --n/s";
				}
			} else {
					if (timer_.getCumulativeSeconds() > 0) {
					string << "up_vel: " << static_cast<value :: Integer>(counter_ / timer_.getCumulativeSeconds());
					string << "n/s";
				} else {
					string << "up_vel: --n/s";
				}
			}
			counter_ = 0;
			timer_.clear();
			if (mode.getValue (Mode :: END_LINE)) {
				string << endLine;
			} else {
				string << ", ";
			}
		}
		if (mode.getValue (Mode :: SHOW_HINT_STAT)) {
			if (mode.getValue (Mode :: END_LINE)) {
				string << tab;
			}
			if (mode.getValue (Mode :: SHOW_FULL_DESCRIPTION)) {
				string << "hint min: ";
			} else {
				string << "hint_min: ";
			}
			for (value :: Integer i = heightMin_; i < heightMax_ + 1; ++ i) {
				const double percent = getMinHintPercent (i);
				if (percent == -1) {
					string << i << "-No";
				} else {
					string << i << "-" << static_cast<value :: Integer>(percent) << "%";
				}
				if (i < heightMax_) {
					string << ", ";
				}
			}
			if (mode.getValue (Mode :: END_LINE)) {
				string << endLine;
			} else {
				string << ", ";
			}
		}
	}
	template<class A>
	void
	Crown<A> :: showTreeStatistics (String& string) const
	{
		string << "crown statistics:" << endLine;
		string << "size: " << getSize() << endLine;
		string << "heightMax: " << heightMax_ << endLine;
		string << "heightMin: " << heightMin_ << endLine;
		string << "-----------------------------------------------" << endLine;
		string << "level:" << tab;
		for (value :: Integer i = heightMin_; i < heightMax_ + 1; ++ i) {
			string << i << tab;
		}
		string << endLine;
		string << "size: " << tab;
		for (value :: Integer i = heightMin_; i < heightMax_ + 1; ++ i) {
			string <<  levelVector_ [i]->getSize() << tab;
		}
		string << endLine;
		for (value :: Integer i = heightMin_; i < heightMax_ + 1; ++ i) {
			const Level_* level = levelVector_.getValue (i);
			string << "level " << i << ":" << endLine;
			for (value :: Integer j = 0; j < level->getSize(); ++ j) {
				const Node_* node = level->getValue (j);
				string << tab << tab;
				if (node->getHint() != NULL) {
					string << "(+) ";
				}
				if (node->getProposition() == NULL) {
					string << *node->getExpression();
				} else {
					node->getProposition()->getAssertion()->replicateName (string);
				}
				const Prop_*
					prop = dynamic_cast<const Prop_*>(node);
				if (prop != NULL) {
					//string << " [" << prop->index_ << "]";
				}
				string << " weight = " << node->getWeight() << endLine;
			}
			string << endLine;
		}
		string << "-----------------------------------------------" << endLine;
		string << "level:" << tab;
		for (value :: Integer i = 0; i < levelVector_.getSize(); ++ i) {
			string << i << tab;
		}
		string << endLine;
		string << "size: " << tab;
		for (value :: Integer i = 0; i < levelVector_.getSize(); ++ i) {
			string <<  levelVector_ [i]->getSize() << tab;
		}
		//string << endLine;
		string << endLine;
	}
	template<class A>
	void
	Crown<A> :: showHintStatistics (String& string) const
	{
		string << "hint statistics:" << endLine;
		for (value :: Integer i = heightMin_; i < heightMax_ + 1; ++ i) {
			const Level_* level = levelVector_ [i];
			const value :: Integer size = level->getSize();
			string << "level " << i << " ";
			if (level->getSize() > 0) {
				Node_* n = level->getLastValue();
				string << "(size = " << size << ", w max = " << n->getWeight() << "):";
			}
			string << tab;
			for (value :: Integer j = 0; j < size; ++ j) {
				const Node_* node = level->getValue (j);
				if (node->getHint() != NULL) {
					string << "i = " << j << " (" << static_cast<double>(100 * j) / size << " %) ";
					string << "w = " << node->getWeight();
					string << ", ";
				}
			}
			string << endLine;
		}
		string << endLine;
	}

}
}
}
}


