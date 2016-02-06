/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_math_Propositions.cpp                                */
/* Description:     global container for propositions                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace math {

	/****************************
	 *		Public members
	 ****************************/

using manipulator :: endLine;
using manipulator :: tab;

	inline
	Propositions :: Propositions () :
	set_ (INITIAL_SET_CAPACITY),
	tree_ (new forest :: Proposition()),
	mutex_ () {
		pthread_mutex_init (&mutex_, NULL);
	}
	Propositions :: ~ Propositions () {
		deleteAggregateObject (tree_);
	}

	inline forest :: Proposition*
	Propositions :: getTree() {
		return tree_;
	}
	inline void
	Propositions :: addToSet (mdl :: Proposition* proposition)
	{
		pthread_mutex_lock (&mutex_);
		set_.add (proposition);
		pthread_mutex_unlock (&mutex_);
	}
	inline void
	Propositions :: addToTree (mdl :: Proposition* proposition)
	{
		pthread_mutex_lock (&mutex_);
		if (Config :: useProver() || Config :: useLearning()) {
			const index :: Assertion
				sourceIndex = proposition->getSourceIndex();
			tree_->addBranch
			(
				proposition->getExpression(),
				proposition,
				sourceIndex
			);
		}
		pthread_mutex_unlock (&mutex_);
	}

	inline void
	Propositions :: sort() {
		sortByRate();
	}
	void
	Propositions :: sortByRate()
	{
		pthread_mutex_lock (&mutex_);
		set_.qSort (statement :: compareByRate);
		for (index :: Assertion i = 0; i < set_.getSize(); ++ i) {
			mdl :: Proposition* proposition = getDescending (i);
			proposition->setSortedIndex (i);
		}
		pthread_mutex_unlock (&mutex_);
	}
	void
	Propositions :: sortByExpSize()
	{
		pthread_mutex_lock (&mutex_);
		set_.qSort (statement :: compareByExpSize);
		for (index :: Assertion i = 0; i < set_.getSize(); ++ i) {
			mdl :: Proposition* proposition = getDescending (i);
			proposition->setSortedIndex (i);
		}
		pthread_mutex_unlock (&mutex_);
	}

	inline index :: Assertion
	Propositions :: getSize() const {
		return set_.getSize();
	}
	inline mdl :: Proposition*
	Propositions :: get (const index :: Assertion index) {
		return getDescending (index);
	}
	inline mdl :: Proposition*
	Propositions :: getIncreasing (const index :: Assertion index) {
		return set_.getValue (index);
	}
	inline mdl :: Proposition*
	Propositions :: getDescending (const index :: Assertion index)
	{
		const index :: Assertion size = getSize();
		return set_.getValue (size - index - 1);
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;
	
	// object :: Object implementation
	void
	Propositions :: commitSuicide() {
		delete this;
	}
	Size_t
	Propositions :: getVolume() const
	{
		Size_t volume = 0;
		volume += set_.getVolume();
		volume += object :: Object :: getAggregateVolume (tree_);
		return volume;
	}
	Size_t
	Propositions :: getSizeOf() const {
		return sizeof (Propositions);
	}
	void
	Propositions :: show (String& string) const {
		string << tab << "propositions: " << tab << set_.getSize() << endLine;
	}
}
}


