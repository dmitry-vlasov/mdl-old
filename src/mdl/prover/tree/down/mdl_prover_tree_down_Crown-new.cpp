/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_tree_down_Crown.cpp                           */
/* Description:     crown (bottom) in proof variant tree                     */
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
namespace down {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Crown<A> :: Crown (MainTree_* mainTree, Tree_* tree) :
	mainTree_ (mainTree),
	tree_ (tree),
	evidences_ (INITIAL_EVIDENCES_CAPACITY),
	timer_(),
	counter_ (0) {
	}
	template<class A>
	Crown<A> :: ~ Crown() {
	}

	// prover :: Crown implementation
	template<class A>
	inline bool
	Crown<A> :: grow() {
		#ifdef TREE_GROW_UP_MULTY_THREADED
		return growSingleThreaded();
		#else
		return growSingleThreaded();
		#endif
	}
	template<class A>
	inline void
	Crown<A> :: add (Evidence_* evidence) {
		evidences_.add (evidence);
	}
	template<class A>
	inline void
	Crown<A> :: remove (Evidence_* evidence) {
		evidences_.removeValue (evidence);
	}
	template<class A>
	inline bool
	Crown<A> :: contains (Evidence_* evidence) const {
		return evidences_.contains (evidence);
	}
	template<class A>
	bool
	Crown<A> :: isEmpty () const {
		return evidences_.isEmpty();
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;

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
		volume += evidences_.getVolume();
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
		const Mode mode (string);
		if (mode.getValue (Mode :: SHOW_IN_GML)) {
			for (value :: Integer i = 0; i < evidences_.getSize(); ++ i) {
				const Evidence_*
					evidence = evidences_.getValue (i);
				evidence->show (string);
			}
		} else if (mode.getValue (Mode :: SHOW_TREE_STATISTICS)) {
			showStatistics (string);
		} else {
			showPlain (string);
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	bool
	Crown<A> :: growSingleThreaded()
	{
		if (evidences_.isEmpty()) {
			return false;
		} else {
			bool result = false;
			timer_.start();
			index :: Step minHeight = index :: undefined :: STEP;
			while (growStep (minHeight)) {
				result = true;
				const Size_t upTreeVolume = mainTree_->up().getNodeVolume();
				const Size_t downTreeVolume = mainTree_->down().getNodeVolume();
				const value :: Real factor = Config :: getReal (Config :: UP_DOWN);
				if (upTreeVolume * factor < downTreeVolume) {
					break;
				}
				if (mainTree_->getTimers()->timeIsOver()) {
					break;
				}
			}
			timer_.stop();
			return result;
		}
	}
	template<class A>
	bool
	Crown<A> :: growStep (index :: Step& minHeight)
	{
		for (value :: Integer i = 0; i < evidences_.getSize(); ++ i) {
			Evidence_* node = evidences_.getValue (i);
			if (node->getMinHeight() <= minHeight) {
				evidences_.remove (i);
				if (node->growDown()) {
					if (minHeight == index :: undefined :: STEP) {
						minHeight = node->getMinHeight();
					}
					return true;
				} else {
					evidences_.add (node);
				}
			} else {
				break;
			}
		}
		return false;
	}

	template<class A>
	index :: Step
	Crown<A> :: getMinHeight() const
	{
		index :: Step minHeight = index :: undefined :: STEP;
		for (value :: Integer i = 0; i < evidences_.getSize(); ++ i) {
			Evidence_* node = evidences_.getValue (i);
			if (node->getMinHeight() < minHeight) {
				minHeight = node->getMinHeight();
			}
		}
		return minHeight;
	}

	template<class A>
	void
	Crown<A> :: showStatistics (String& string) const
	{
		const Mode mode (string);
		if (mode.getValue (Mode :: SHOW_DOWN_CROWN_CARD)) {
			if (mode.getValue (Mode :: END_LINE)) {
				string << tab;
			}
			if (mode.getValue (Mode :: SHOW_FULL_DESCRIPTION)) {
				string << "down crown card: " << evidences_.getSize() << " nodes";
			} else {
				string << "dn_cr: " << evidences_.getSize();
			}
			if (mode.getValue (Mode :: END_LINE)) {
				string << endLine;
			} else {
				string << ", ";
			}
		}
		if (mode.getValue (Mode :: SHOW_DOWN_CROWN_VOLUME)) {
			if (mode.getValue (Mode :: END_LINE)) {
				string << tab;
			}
			const Size_t volume = getVolume();
			if (mode.getValue (Mode :: SHOW_FULL_DESCRIPTION)) {
				string << "down crown volume: ";
			} else {
				string << "dn_cr_vol: ";
			}
			memory :: Unit :: show (string, volume);
			if (mode.getValue (Mode :: END_LINE)) {
				string << endLine;
			} else {
				string << ", ";
			}
		}
		if (mode.getValue (Mode :: SHOW_GROW_DOWN_VELOCITY)) {
			if (mode.getValue (Mode :: END_LINE)) {
				string << tab;
			}
			if (mode.getValue (Mode :: SHOW_FULL_DESCRIPTION)) {
				if (timer_.getCumulativeSeconds() > 0) {
					string << "down vel: " << static_cast<value :: Integer>(counter_ / timer_.getCumulativeSeconds());
					string << "n/s";
				} else {
					string << "down vel: --n/s";
				}
			} else {
				if (timer_.getCumulativeSeconds() > 0) {
					string << "d_n_vel: " << static_cast<value :: Integer>(counter_ / timer_.getCumulativeSeconds());
					string << "n/s";
				} else {
					string << "d_n_vel: --n/s";
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
	}
	template<class A>
	void
	Crown<A> :: showPlain (String& string) const
	{
		string << "<evidence_crown>" << endLine;
		for (value :: Integer i = 0; i < evidences_.getSize(); ++ i) {
			const Evidence_* evidence = evidences_.getValue (i);
			string << tab;
			evidence->show (string);
			string << endLine;
		}
		string << "</evidence_crown>" << endLine;
	}
}
}
}
}


