/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_Sample.cpp                                     */
/* Description:     sample set for teaching / tuning                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_SAMPLE_CPP_
#define MDL_STUDY_SAMPLE_CPP_

namespace mdl {
namespace study {

	/****************************
	 *		Public members
	 ****************************/

	Sample :: Sample
	(
		Format& format,
		const Type_ type
	) :
	format_ (format),
	subFormat_ (format_),
	type_ (type),
	size_ (Config :: getInteger (Config :: SAMPLE_SIZE)),
	base_ (size_),
	primary_ (size_),
	secondary_ (size_ * 16),
	experience_(format_, this),
	fitness_ (format_, this) {
	}
	Sample :: ~ Sample() {
	}

	void
	Sample :: build
	(
		const value :: Integer size,
		Time& timeLimit
	)
	{
		format_.message() << "building sample";
		if (Benchmark :: get()->sample()->getTimePolynomialX() != NULL) {
			const Time estimatedTime =
				Benchmark :: get()->sample()->getTimePolynomialX()->eval (size);
			format_.message() << ", estimated time = " << estimatedTime << " s";
		}

		format_.showStart (timeLimit);
		size_ = size;
		if (experience_.collect()) {
			Math :: propositions()->sort();
		}
		if (primary_.getSize() == 0) {
			initPrimary();
		}
		setSize (size_);
		showPrimary (subFormat_.message());
		subFormat_.showMessage();
		Time limit = timeLimit;
		fitness_.build (limit);
		initSecondary();
		showSecondary (subFormat_.message());
		subFormat_.showMessage();
		format_.showFinal();
		timeLimit -= format_.getTimer().getSeconds();
	}
	void
	Sample :: setSize (const value :: Integer size)
	{
		primary_.clear();
		value :: Real factor = base_.getSize();
		factor /= size;
		for (value :: Integer i = 0; i < size; ++ i) {
			const value :: Integer j = i * factor;
			const value :: Integer index = base_.getValue (j);
			primary_.add (index);
		}
	}
	Time
	Sample :: estimateTime (const value :: Integer sampleSize)
	{
		Time estimatedTime = 0;
		estimatedTime += Benchmark :: get()->sample()->getTimePolynomialX()->eval (sampleSize) * TIME_RESERVE_FACTOR;
		return estimatedTime;
	}

	const Set&
	Sample :: getPrimary() const {
		return primary_;
	}
	const Set&
	Sample :: getSecondary() const {
		return secondary_;
	}
	const Fitness&
	Sample :: getFitness() const {
		return fitness_;
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: mode;
using manipulator :: tab;

	// object :: Object implementation
	void
	Sample :: commitSuicide() {
		delete this;
	}
	Size_t
	Sample :: getVolume() const
	{
		Size_t volume = 0;
		volume += base_.getVolume();
		volume += primary_.getVolume();
		volume += secondary_.getVolume();
		volume += experience_.getVolume();
		volume += fitness_.getVolume();
		return volume;
	}
	Size_t
	Sample :: getSizeOf() const {
		return sizeof (Sample);
	}
	void
	Sample :: show (String& string) const
	{
		showPrimary (string);
		string << ", ";
		showSecondary (string);
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Sample :: showPrimary (String& string, const bool full) const
	{
		if (full) {
			string << "primary sample = {";
			for (value :: Integer i = 0; i < primary_.getSize(); ++ i) {
				const value :: Integer index = primary_.getValue (i);
				Math :: assertions()->getTheorem (index)->replicateName (string);
				if (i + 1 < primary_.getSize()) {
					string << ", ";
				}
			}
		string << "}, size = " << primary_.getSize();
		} else {
			string << "primary sample size = " << primary_.getSize();
		}
	}
	void
	Sample :: showSecondary (String& string, const bool full) const
	{
		if (full) {
			string << endLine;
			string << "secondary sample = {";
			for (value :: Integer i = 0; i < secondary_.getSize(); ++ i) {
				const value :: Integer index = secondary_.getValue (i);
				Math :: assertions()->get (index)->replicateName (string);
				if (i + 1 < secondary_.getSize()) {
					string << ", ";
				}
			}
			string << "}, size = " << secondary_.getSize();
		} else {
			string << "secondary sample size = " << secondary_.getSize();
		}
	}
	void
	Sample :: initPrimary()
	{
		primary_.clear();
		switch (type_) {
		case UNIFORM : {
			const value :: Real totalSize = Math :: assertions()->getTheoremNumber();
			const value :: Real specificFactor = totalSize / size_;
			for (value :: Integer i = 0; i < size_; ++ i) {
				const value :: Integer j = static_cast<value :: Real>(i) * specificFactor;
				const mdl :: Assertion* assertion = Math :: assertions()->getTheorem (j);
				if (assertion->getName() == Config :: excludeAssertion()) {
					continue;
				}
				base_.add (j);
				primary_.add (j);
			}
			break;
		}
		case IN_ORDER :
			for (value :: Integer i = 0; i < size_; ++ i) {
				base_.add (i);
				primary_.add (i);
			}
			break;
		}
	}
	void
	Sample :: initSecondary()
	{
		if (Config :: learn()) {
			for (value :: Integer i = 0; i < Math :: propositions()->getSize(); ++ i) {
				mdl :: Proposition*
					proposition = Math :: propositions()->getDescending (i);
				const value :: Name
					theoremName = proposition->getAssertion()->getName();
				if (Config :: excludeAssertion() == theoremName) {
					continue;
				}
				secondary_.add (i);
			}
		} else {
			typedef Fitness :: Tree_ Tree;
			typedef Fitness :: TreeVector_ TreeVector;

			const TreeVector* treeVector = fitness_.treeVector_;

			for (value :: Integer i = 0; i < treeVector->getSize(); ++ i) {
				Tree* tree = treeVector->getValue (i);
				typedef Tree :: UpTree_ UpTree;
				const UpTree& upTree = tree->up();

				typedef UpTree :: NodeSet_ NodeSet;
				const NodeSet& nodeSet = upTree.getNodeSet();

				for (value :: Integer j = 0; j < nodeSet.getSize(); ++ j) {
					typedef UpTree :: Node_ Node;
					const Node* node = nodeSet.getValue (j);

					const mdl :: Proposition* proposition = node->getProposition();
					if (proposition != NULL) {
						const index :: Assertion
							index = proposition->getSortedIndex();
						secondary_.add (index);
					}
				}
			}
		}
	}
}
}

#endif /*MDL_STUDY_SAMPLE_CPP_*/
