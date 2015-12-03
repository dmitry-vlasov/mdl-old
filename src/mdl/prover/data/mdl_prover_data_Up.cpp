/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_data_Up.cpp                                   */
/* Description:     prover up tree statistics data                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_DATA_UP_CPP_
#define MDL_PROVER_DATA_UP_CPP_

namespace mdl {
namespace prover {
namespace data {

	/****************************
	 *		Public members
	 ****************************/

	Up :: Up() :
	totalVolume_ (0),
	crownVolume_ (0),
	levelVectorVolume_ (0),
	nodeSetVolume_     (0),
	nodeVectorVolume_  (0),
	nodeSproutVolume_  (0),

	levelVectorSize_ (0),
	nodeSetSize_     (0),
	nodeVectorSize_  (0),
	nodeSproutSize_  (0),

	hypCount_  (0),
	propCount_ (0),
	refCount_  (0),
	topCount_  (0),

	hypVolume_  (0),
	propVolume_ (0),
	refVolume_  (0),
	topVolume_  (0) {
	}
	template<class A>
	Up :: Up (const typename tree :: up :: Tree<A>& up) :
	totalVolume_       (up.getVolume()),
	crownVolume_       (getAggregateVolume (up.crown_)),
	levelVectorVolume_ (up.tree_.getVolume()),
	nodeSetVolume_     (up.nodeSet_.getVolume()),
	nodeVectorVolume_  (up.nodeVector_.getVolume()),
	nodeSproutVolume_  (up.nodeVector_.getVolume()),

	levelVectorSize_ (up.tree_.getSize()),
	nodeSetSize_     (up.nodeSet_.getSize()),
	nodeVectorSize_  (up.nodeVector_.getSize()),
	nodeSproutSize_  (up.nodeSprout_.getSize()),

	hypCount_  (0),
	propCount_ (0),
	refCount_  (0),
	topCount_  (0),

	hypVolume_  (0),
	propVolume_ (0),
	refVolume_  (0),
	topVolume_  (0) {
		collectStatistics (up);
	}
	Up :: ~ Up() {
	}

	void
	Up :: operator += (const Up& tree)
	{
		totalVolume_       += tree.totalVolume_;
		crownVolume_       += tree.crownVolume_;
		levelVectorVolume_ += tree.levelVectorVolume_;
		nodeSetVolume_     += tree.nodeSetVolume_;
		nodeVectorVolume_  += tree.nodeVectorVolume_;
		nodeSproutVolume_  += tree.nodeSproutVolume_;

		levelVectorSize_ += tree.levelVectorSize_;
		nodeSetSize_     += tree.nodeSetSize_;
		nodeVectorSize_  += tree.nodeVectorSize_;
		nodeSproutSize_  += tree.nodeSproutSize_;

		hypCount_  += tree.hypCount_;
		propCount_ += tree.propCount_;
		refCount_  += tree.refCount_;
		topCount_  += tree.topCount_;

		hypVolume_  += tree.hypVolume_;
		propVolume_ += tree.propVolume_;
		refVolume_  += tree.refVolume_;
		topVolume_  += tree.topVolume_;
	}
	void
	Up :: operator /= (const int count)
	{
		totalVolume_       /= count;
		crownVolume_       /= count;
		levelVectorVolume_ /= count;
		nodeSetVolume_     /= count;
		nodeVectorVolume_  /= count;
		nodeSproutVolume_  /= count;

		levelVectorSize_ /= count;
		nodeSetSize_     /= count;
		nodeVectorSize_  /= count;
		nodeSproutSize_  /= count;

		hypCount_  /= count;
		propCount_ /= count;
		refCount_  /= count;
		topCount_  /= count;

		hypVolume_  /= count;
		propVolume_ /= count;
		refVolume_  /= count;
		topVolume_  /= count;
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;
using manipulator :: iterate;

	void
	Up :: showVolume (String& string, const int indent) const
	{
		string << iterate << indent << tab;
		string << "Up tree volume" << endLine;
		string << iterate << indent << tab;
		string << "------------------" << endLine;
		string << iterate << (indent + 1) << tab;
		string << memory :: UsageMessage (totalVolume_, totalVolume_, "total volume") << endLine;

		string << iterate << (indent + 1) << tab;
		string << memory :: UsageMessage (totalVolume_, crownVolume_, "crown") << endLine;

		string << iterate << (indent + 1) << tab;
		string << "level vector size = " << levelVectorSize_ << endLine;
		string << iterate << (indent + 1) << tab;
		string << memory :: UsageMessage (totalVolume_, levelVectorVolume_, "level vector") << endLine;

		string << iterate << (indent + 1) << tab;
		string << "node set size = " << nodeSetSize_ << endLine;
		string << iterate << (indent + 1) << tab;
		string << memory :: UsageMessage (totalVolume_, nodeSetVolume_, "node set") << endLine;

		string << iterate << (indent + 1) << tab;
		string << "node vector size = " << nodeVectorSize_ << endLine;
		string << iterate << (indent + 1) << tab;
		string << memory :: UsageMessage (totalVolume_, nodeVectorVolume_, "node vector") << endLine;

		string << iterate << (indent + 1) << tab;
		string << "node sprout size = " << nodeSproutSize_ << endLine;
		string << iterate << (indent + 1) << tab;
		string << memory :: UsageMessage (totalVolume_, nodeSproutVolume_, "node sprout") << endLine;


		string << iterate << (indent + 1) << tab;
		string << endLine;

		showStatistics (string, indent + 1);
	}
	void
	Up :: showTiming (String& string, const int indent) const {
	}

	// object :: Object interface
	void
	Up :: commitSuicide() {
		delete this;
	}
	Size_t
	Up :: getVolume() const {
		return 0;
	}
	Size_t
	Up :: getSizeOf() const {
		return sizeof (Up);
	}
	void
	Up :: show (String& string) const
	{
		showVolume (string);
		showTiming (string);
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	void
	Up :: collectStatistics (const tree :: up :: Tree<A>& up)
	{
		typedef A Allocator;
		typedef Node<Allocator> Node;
		typedef node :: Hyp<Allocator>  Hyp;
		typedef node :: Prop<Allocator> Prop;
		typedef node :: Ref<Allocator>  Ref;
		typedef node :: Top<Allocator>  Top;

		for (int i = 0; i < up.nodeVector_.getSize(); ++ i) {
			const Node* node = up.nodeVector_.getValue (i);
			if (dynamic_cast<const Hyp*>(node) != NULL)  {
				++ hypCount_;
				hypVolume_ += getAggregateVolume (node);
			}
			if (dynamic_cast<const Prop*>(node) != NULL) {
				++ propCount_;
				propVolume_ += getAggregateVolume (node);
			}
			if (dynamic_cast<const Ref*>(node) != NULL)  {
				++ refCount_;
				refVolume_ += getAggregateVolume (node);
			}
			if (dynamic_cast<const Top*>(node) != NULL)  {
				++ topCount_;
				topVolume_ += getAggregateVolume (node);
			}
		}
	}
	void
	Up :: showStatistics (String& string, const int indent) const
	{
		string << iterate << indent << tab;
		string << "Up tree statistics" << endLine;
		string << iterate << indent << tab;
		string << "--------------------" << endLine;

		string << iterate << (indent + 1) << tab;
		string << "hyp count = " << hypCount_ << ", " << tab;
		string << "total volume = " << hypVolume_ << ", " << tab;
		string << "average volume = " << ((hypCount_ > 0) ? (hypVolume_ / hypCount_) : 0);
		string << endLine;

		string << iterate << (indent + 1) << tab;
		string << "prop count = " << propCount_ << ", " << tab;
		string << "total volume = " << propVolume_ << ", " << tab;
		string << "average volume = " << ((propCount_ > 0) ? (propVolume_ / propCount_) : 0);
		string << endLine;

		string << iterate << (indent + 1) << tab;
		string << "ref count = " << refCount_ << ", " << tab;
		string << "total volume = " << refVolume_ << ", " << tab;
		string << "average volume = " << ((refVolume_ > 0) ? (refVolume_ / refCount_) : 0);
		string << endLine;

		string << iterate << (indent + 1) << tab;
		string << "top count = " << topCount_ << ", " << tab;
		string << "total volume = " << topVolume_ << ", " << tab;
		string << "average volume = " << ((topVolume_ > 0) ? (topVolume_ / topCount_) : 0);
		string << endLine;

		string << iterate << (indent + 1) << tab;
		string << endLine;
	}
}
}
}

#endif /*MDL_PROVER_DATA_UP_CPP_*/
