/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_tree_up_Level.cpp                             */
/* Description:     level in proof variant tree                              */
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

	template<class A, template<class> class S>
	inline
	Level<A, S> :: Level (const value :: Integer initialCapacity) :
	level_ (initialCapacity) {
	}
	template<class A, template<class> class S>
	Level<A, S> :: ~ Level() {
	}

	// prover :: Level implementation
	template<class A, template<class> class S>
	inline value :: Integer
	Level<A, S> :: getSize () const {
		return level_.getSize();
	}
	template<class A, template<class> class S>
	inline typename Level<A, S> :: Node_*
	Level<A, S> :: getValue (const value :: Integer i) const {
		return level_.getValue (i);
	}
	template<class A, template<class> class S>
	inline typename Level<A, S> :: Node_*
	Level<A, S> :: takeBest()
	{
		Node_* node = level_.getLastValue();
		level_.removeLast();
		return node;
	}
	template<class A, template<class> class S>
	typename Level<A, S> :: Node_*
	Level<A, S> :: takeBestHint()
	{
		const value :: Integer size = level_.getSize();
		for (value :: Integer i = 0; i < size; ++ i) {
			const value :: Integer index = size - i - 1;
			Node_* node = level_.getValue (index);
			if (node->getHint() != NULL) {
				level_.remove (index);
				return node;
			}
		}
		return NULL;
	}
	template<class A, template<class> class S>
	typename Level<A, S> :: Node_*
	Level<A, S> :: takeBestRestricted()
	{
		const value :: Integer
			maxComplexity =
			Math :: statistics()->get (Statistics :: EXPRESSION_COMPLEXITY).getMax();
		const value :: Integer size = level_.getSize();
		for (value :: Integer i = 0; i < size; ++ i) {
			const value :: Integer index = size - i - 1;
			Node_* node = level_.getValue (index);
			if (node->getExpression()->getComplexity() <= maxComplexity) {
				level_.remove (index);
				return node;
			}
		}
		return NULL;
	}

	template<class A, template<class> class S>
	inline bool
	Level<A, S> :: isEmpty (const bool onlyHint, const bool restricted) const
	{
		if (level_.isEmpty()) {
			return true;
		} else if (onlyHint || restricted) {
			const value :: Integer
				maxComplexity =
				Math :: statistics()->get (Statistics :: EXPRESSION_COMPLEXITY).getMax();

			for (value :: Integer i = 0; i < level_.getSize(); ++ i) {
				const Node_* node = level_.getValue (i);
				if (onlyHint && (node->getHint() != NULL)) {
					return false;
				}
				if (restricted && (node->getExpression()->getComplexity() <= maxComplexity)) {
					return false;
				}
			}
			return true;
		} else {
			return false;
		}
	}
	template<class A, template<class> class S>
	inline void
	Level<A, S> :: add (Node_* node) {
		level_.add (node);
	}
	template<class A, template<class> class S>
	inline void
	Level<A, S> :: remove (Node_* node) {
		level_.removeValue (node);
	}
	template<class A, template<class> class S>
	bool
	Level<A, S> :: contains (Node_* node) const {
		return level_.contains (node);
	}
	template<class A, template<class> class S>
	void
	Level<A, S> :: evalPartition (value :: Integer& boundary, value :: Integer& size) const
	{
		level_.qSort();
		boundary = evalPartitionBoundary();
		size = evalPartitionSize();
	}
	template<class A, template<class> class S>
	void
	Level<A, S> :: showPartition (String& string) const
	{
		level_.qSort();
		const Mode mode (string);
		const value :: Real boundary = evalPartitionBoundary();
		const value :: Real size = evalPartitionSize();
		if (mode.getValue (Mode :: SHOW_FULL_DESCRIPTION)) {
			string << "boundary = " << boundary << ", ";
			string << "size = " << size << ", ";
			string << "percent(%) = " << boundary * 100 / size;
		} else {
			string << "b = " << boundary << ", ";
			string << "s = " << size << ", ";
			string << "% = " << boundary * 100 / size;
		}
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;

	// object :: Object implementation
	template<class A, template<class> class S>
	void
	Level<A, S> :: commitSuicide() {
		delete this;
	}
	template<class A, template<class> class S>
	Size_t
	Level<A, S> :: getVolume() const
	{
		Size_t volume = 0;
		volume += level_.getVolume();
		return volume;
	}
	template<class A, template<class> class S>
	Size_t
	Level<A, S> :: getSizeOf() const {
		return sizeof (Level);
	}
	template<class A, template<class> class S>
	void
	Level<A, S> :: show (String& string) const
	{
		const value :: Integer size = level_.getSize();
		for (value :: Integer j = 0; j < size; ++ j) {
			const value :: Integer k = size - j - 1;
			const Node_* node = level_.getValue (k);
			if (showPropNode (node, string)) {
				continue;
			}
			if (showHypNode (node, string)) {
				continue;
			}
			//string << tab << *node->getExpression() << endLine;
		}
		string <<  endLine;
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A, template<class> class S>
	value :: Integer
	Level<A, S> :: evalPartitionBoundary() const
	{
		for (value :: Integer i = 0; i < level_.getSize(); ++ i) {
			const Node_* node = level_.getValue (i);
			if (node->getHint() != NULL) {
				return evalPartitionSize (i);
			}
		}
		return evalPartitionSize();
	}
	template<class A, template<class> class S>
	value :: Integer
	Level<A, S> :: evalPartitionSize (const value :: Integer k) const
	{
		value :: Integer count = 1;
		for (value :: Integer i = k; i < level_.getSize(); ++ i) {
			const Node_* node = level_.getValue (i);
			const value :: Real weight = node->getWeight();
			while (i + 1 < level_.getSize()) {
				const value :: Real nextWeight = level_.getValue (i + 1)->getWeight();
				if (nextWeight != weight) {
					++ count;
					break;
				}
				++ i;
			}
		}
		return count;
	}

	template<class A, template<class> class S>
	bool
	Level<A, S> :: showPropNode (const Node_* node, String& string) const
	{
		const Prop_*
			p = dynamic_cast<const Prop_*>(node);
		if (p != NULL) {
			string << tab;
			if (p->getHint() != NULL) {
				string << "<!> ";
			} else {
				string << "    ";
			}
			string << "prop = ";
			node->getProposition()->getAssertion()->replicateName (string);
			string << ", ";
			string << "down = " << *node->getExpression() << ", ";
			string << "weight = " << node->getWeight();
			string << endLine;
			return true;
		} else {
			return false;
		}
	}
	template<class A, template<class> class S>
	bool
	Level<A, S> :: showHypNode (const Node_* node, String& string) const
	{
		const Hyp_*
			h = dynamic_cast<const Hyp_*>(node);
		if (h != NULL) {
			string << tab;
			if (h->getHint() != NULL) {
				string << "<!> ";
			} else {
				string << "    ";
			}
			string << "hyp = " << *node->getExpression() << ", ";
			string << "weight = " << node->getWeight();
			string << endLine;
			return true;
		} else {
			return false;
		}
	}

	/*template<class A, template<class> class S>
	void
	Level<A, S> :: verifySize() const
	{
		value :: Integer size = 0;
		for (value :: Integer i = heightMin_; i < heightMax_ + 1; ++ i) {
			const Level_* level = levelVector_.getValue (i);
			const value :: Integer s = level->getSize();
			size += s;
			for (value :: Integer j = 0; j < s; ++ j) {
				Node_* node = level->getValue (j);
				if (node == NULL) {
					std :: cout << "NULL NODE IN A CROWN" << std :: endl;;
				}
			}
		}
		if (size != size_) {
			std :: cout << "crown verification fail." << std :: endl;
			std :: cout << "size = " << size << ", size_ = " << size_ << std :: endl << std :: endl;

			String string (1024);
					showTreeStatistics (string);
					std :: cout << std :: endl << string << std :: endl;

			throw Exception ("crown size verification fail");
		}
	}*/
}
}
}
}


