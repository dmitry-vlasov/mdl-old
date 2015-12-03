/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_data_Root.cpp                                 */
/* Description:     prover root statistics data                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_DATA_ROOT_CPP_
#define MDL_PROVER_DATA_ROOT_CPP_

namespace mdl {
namespace prover {
namespace data {

	/****************************
	 *		Public members
	 ****************************/

	Root :: Root() :
	totalVolume_  (0),
	bufferVolume_ (0),
	rootVectorVolume_  (0),
	proofVectorVolume_ (0),
	stepVectorVolume_  (0),

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
	Root :: Root (const typename tree :: Root<A>& root) :
	totalVolume_  (root.getVolume()),
	bufferVolume_ (root.buffer_.getVolume()),
	rootVectorVolume_ (root.rootVector_.getVolume()),
	proofVectorVolume_ (root.proofVector_.getVolume()),
	stepVectorVolume_ (root.stepVector_.getVolume()),

	hypCount_  (0),
	propCount_ (0),
	refCount_  (0),
	topCount_  (0),

	hypVolume_  (0),
	propVolume_ (0),
	refVolume_  (0),
	topVolume_  (0) {
		collectStatistics (root);
	}
	Root :: ~ Root() {
	}

	void
	Root :: operator += (const Root& root)
	{
		totalVolume_       += root.totalVolume_;
		bufferVolume_      += root.bufferVolume_;
		rootVectorVolume_  += root.rootVectorVolume_;
		proofVectorVolume_ += root.proofVectorVolume_;
		stepVectorVolume_  += root.stepVectorVolume_;

		hypCount_  += root.hypCount_;
		propCount_ += root.propCount_;
		refCount_  += root.refCount_;
		topCount_  += root.topCount_;

		hypVolume_  += root.hypVolume_;
		propVolume_ += root.propVolume_;
		refVolume_  += root.refVolume_;
		topVolume_  += root.topVolume_;
	}
	void
	Root :: operator /= (const int count)
	{
		totalVolume_       /= count;
		bufferVolume_      /= count;
		rootVectorVolume_  /= count;
		proofVectorVolume_ /= count;
		stepVectorVolume_  /= count;

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
	Root :: showVolume (String& string, const int indent) const
	{
		string << iterate << indent << tab;
		string << "Tree root volume" << endLine;
		string << iterate << indent << tab;
		string << "------------------" << endLine;
		string << iterate << (indent + 1) << tab;
		string << memory :: UsageMessage (totalVolume_, totalVolume_, "total volume") << endLine;
		string << iterate << (indent + 1) << tab;
		string << memory :: UsageMessage (totalVolume_, bufferVolume_, "buffer") << endLine;

		//string << iterate << indent << tab;
		//string << "root vector size = " << rootVector_.getSize() << endLine;
		string << iterate << (indent + 1) << tab;
		string << memory :: UsageMessage (totalVolume_, rootVectorVolume_, "root vector") << endLine;

		//string << iterate << indent << tab;
		//string << "step vector size = " << stepVector_.getSize() << endLine;
		string << iterate << (indent + 1) << tab;
		string << memory :: UsageMessage (totalVolume_, stepVectorVolume_, "step vector") << endLine;


		//string << iterate << indent << tab;
		//string << "proof vector size = " << proofVector_.getSize() << endLine;
		string << iterate << (indent + 1) << tab;
		string << memory :: UsageMessage (totalVolume_, proofVectorVolume_, "proof vector") << endLine;

		string << iterate << (indent + 1) << tab;
		string << endLine;

		showStatistics (string, indent + 1);
	}
	void
	Root :: showTiming (String& string, const int indent) const {
	}

	// object :: Object interface
	void
	Root :: commitSuicide() {
		delete this;
	}
	Size_t
	Root :: getVolume() const {
		return 0;
	}
	Size_t
	Root :: getSizeOf() const {
		return sizeof (Root);
	}
	void
	Root :: show (String& string) const
	{
		showVolume (string);
		showTiming (string);
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	void
	Root :: collectStatistics (const tree :: Root<A>& root)
	{
		typedef A Allocator;
		typedef Proof<Allocator> Proof;
		typedef proof :: Hyp<Allocator>  Hyp;
		typedef proof :: Prop<Allocator> Prop;
		typedef proof :: Ref<Allocator>  Ref;
		typedef proof :: Top<Allocator>  Top;

		for (int i = 0; i < root.proofVector_.getSize(); ++ i) {
			const Proof* proof = root.proofVector_.getValue (i);
			if (dynamic_cast<const Hyp*>(proof) != NULL)  {
				++ hypCount_;
				hypVolume_ += getAggregateVolume (proof);
			}
			if (dynamic_cast<const Prop*>(proof) != NULL) {
				++ propCount_;
				propVolume_ += getAggregateVolume (proof);
			}
			if (dynamic_cast<const Ref*>(proof) != NULL)  {
				++ refCount_;
				refVolume_ += getAggregateVolume (proof);
			}
			if (dynamic_cast<const Top*>(proof) != NULL)  {
				++ topCount_;
				topVolume_ += getAggregateVolume (proof);
			}
		}
	}

	void
	Root :: showStatistics (String& string, const int indent) const
	{
		string << iterate << indent << tab;
		string << "Tree root statistics" << endLine;
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

#endif /*MDL_PROVER_DATA_ROOT_CPP_*/
