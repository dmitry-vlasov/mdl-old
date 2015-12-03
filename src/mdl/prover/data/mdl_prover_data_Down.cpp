/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_data_Down.cpp                                   */
/* Description:     prover up tree statistics data                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_DATA_DOWN_CPP_
#define MDL_PROVER_DATA_DOWN_CPP_

namespace mdl {
namespace prover {
namespace data {

	/****************************
	 *		Public members
	 ****************************/

	Down :: Down () :
	totalVolume_ (0),
	crownVolume_ (0),
	levelVectorVolume_    (0),
	evidenceVectorVolume_ (0),
	unusedVectorVolume_   (0),

	levelVectorSize_    (0),
	evidenceVectorSize_ (0),
	unusedVectorSize_   (0),

	hypCount_  (0),
	propCount_ (0),
	refCount_  (0),
	subCount_  (0),
	topCount_  (0),

	hypVolume_  (0),
	propVolume_ (0),
	refVolume_  (0),
	subVolume_  (0),
	topVolume_  (0) {
	}
	template<class A>
	Down :: Down (const typename tree :: down :: Tree<A>& down) :
	totalVolume_ (down.getVolume()),
	crownVolume_ (getAggregateVolume (down.crown_)),
	levelVectorVolume_ (down.tree_.getVolume()),
	evidenceVectorVolume_ (down.evidenceVector_.getVolume()),
	unusedVectorVolume_ (down.unusedEvidences_.getVolume()),

	levelVectorSize_ (down.tree_.getSize()),
	evidenceVectorSize_ (down.evidenceVector_.getSize()),
	unusedVectorSize_ (down.unusedEvidences_.getSize()),

	hypCount_  (0),
	propCount_ (0),
	refCount_  (0),
	subCount_  (0),
	topCount_  (0),

	hypVolume_  (0),
	propVolume_ (0),
	refVolume_  (0),
	subVolume_  (0),
	topVolume_  (0) {
		collectStatistics (down);
	}
	Down :: ~ Down() {
	}

	void
	Down :: operator += (const Down& tree)
	{
		totalVolume_          += tree.totalVolume_;
		crownVolume_          += tree.crownVolume_;
		levelVectorVolume_    += tree.levelVectorVolume_;
		evidenceVectorVolume_ += tree.evidenceVectorVolume_;
		unusedVectorVolume_   += tree.unusedVectorVolume_;

		levelVectorSize_    += tree.levelVectorSize_;
		evidenceVectorSize_ += tree.evidenceVectorSize_;
		unusedVectorSize_   += tree.unusedVectorSize_;

		hypCount_  += tree.hypCount_;
		propCount_ += tree.propCount_;
		refCount_  += tree.refCount_;
		subCount_  += tree.subCount_;
		topCount_  += tree.topCount_;

		hypVolume_  += tree.hypVolume_;
		propVolume_ += tree.propVolume_;
		refVolume_  += tree.refVolume_;
		subVolume_  += tree.subVolume_;
		topVolume_  += tree.topVolume_;
	}
	void
	Down :: operator /= (const int count)
	{
		totalVolume_          /= count;
		crownVolume_          /= count;
		levelVectorVolume_    /= count;
		evidenceVectorVolume_ /= count;
		unusedVectorVolume_   /= count;

		levelVectorSize_    /= count;
		evidenceVectorSize_ /= count;
		unusedVectorSize_   /= count;

		hypCount_  /= count;
		propCount_ /= count;
		refCount_  /= count;
		subCount_  /= count;
		topCount_  /= count;

		hypVolume_  /= count;
		propVolume_ /= count;
		refVolume_  /= count;
		subVolume_  /= count;
		topVolume_  /= count;
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;
using manipulator :: iterate;

	void
	Down :: showVolume (String& string, const int indent) const
	{
		string << iterate << indent << tab;
		string << "Down tree volume" << endLine;
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
		string << "evidence vector size = " << evidenceVectorSize_ << endLine;
		string << iterate << (indent + 1) << tab;
		string << memory :: UsageMessage (totalVolume_, evidenceVectorVolume_, "node vector") << endLine;

		string << iterate << (indent + 1) << tab;
		string << "unused evidences size = " << unusedVectorSize_ << endLine;
		string << iterate << (indent + 1) << tab;
		string << memory :: UsageMessage (totalVolume_, unusedVectorVolume_, "unused evidences") << endLine;

		string << iterate << (indent + 1) << tab;
		string << endLine;

		showStatistics (string, indent + 1);
	}
	void
	Down :: showTiming (String& string, const int indent) const {
	}

	// object :: Object interface
	void
	Down :: commitSuicide() {
		delete this;
	}
	Size_t
	Down :: getVolume() const {
		return 0;
	}
	Size_t
	Down :: getSizeOf() const {
		return sizeof (Down);
	}
	void
	Down :: show (String& string) const
	{
		showVolume (string);
		showTiming (string);
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	void
	Down :: collectStatistics (const tree :: down :: Tree<A>& down)
	{
		typedef A Allocator;
		typedef Evidence<Allocator> Evidence;
		typedef evidence :: Hyp<Allocator>  Hyp;
		typedef evidence :: Prop<Allocator> Prop;
		typedef evidence :: Ref<Allocator>  Ref;
		typedef evidence :: Sub<Allocator>  Sub;
		typedef evidence :: Top<Allocator>  Top;

		for (int i = 0; i < down.evidenceVector_.getSize(); ++ i) {
			const Evidence* node = down.evidenceVector_.getValue (i);
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
			if (dynamic_cast<const Sub*>(node) != NULL)  {
				++ subCount_;
				subVolume_ += getAggregateVolume (node);
			}
			if (dynamic_cast<const Top*>(node) != NULL)  {
				++ topCount_;
				topVolume_ += getAggregateVolume (node);
			}
		}
	}

	void
	Down :: showStatistics (String& string, const int indent) const
	{
		string << iterate << indent << tab;
		string << "Down tree statistics" << endLine;
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
		string << "sub count = " << subCount_ << ", " << tab;
		string << "total volume = " << subVolume_ << ", " << tab;
		string << "average volume = " << ((subVolume_ > 0) ? (subVolume_ / subCount_) : 0);
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

#endif /*MDL_PROVER_DATA_DOWN_CPP_*/
