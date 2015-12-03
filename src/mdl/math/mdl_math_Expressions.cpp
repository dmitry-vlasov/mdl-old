/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_math_Expressions.cpp                                 */
/* Description:     global container for express     i ons                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_MATH_EXPRESSIONS_CPP_
#define MDL_MATH_EXPRESSIONS_CPP_

namespace mdl {
namespace math {

	/****************************
	 *		Public members
	 ****************************/

using manipulator :: endLine;
using manipulator :: tab;

	Expressions :: Expressions () :
	treeAll_ (new Tree_()),
	treeProof_ (new Tree_()),
	treeAssertion_ (new Tree_()),
	mutex_ () {
		pthread_mutex_init (&mutex_, NULL);
	}
	Expressions :: ~ Expressions ()
	{
		deleteAggregateObject (treeAll_);
		deleteAggregateObject (treeProof_);
		deleteAggregateObject (treeAssertion_);
	}

	inline Expressions :: Tree_*
	Expressions :: getTree (const Type_ type)
	{
		switch (type) {
		case PROOF :
			return treeProof_;
		case ASSERTION :
			return treeAssertion_;
		default :
			return treeAll_;
		}
	}
	inline void
	Expressions :: add (const array :: Expression* expression, const Type_ type)
	{
		pthread_mutex_lock (&mutex_);
		if (Config :: useProver() || Config :: useLearning()) {
			switch (type) {
			case PROOF :
				treeProof_->addBranch (expression, expression);
				treeAll_->addBranch (expression, expression);
				break;
			case ASSERTION :
				treeAssertion_->addBranch (expression, expression);
				treeAll_->addBranch (expression, expression);
				break;
			case ALL :
				treeAll_->addBranch (expression, expression);
				break;
			}
		}
		pthread_mutex_unlock (&mutex_);
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;
	
	// object :: Object implementation
	void
	Expressions :: commitSuicide() {
		delete this;
	}
	Size_t
	Expressions :: getVolume() const
	{
		Size_t volume = 0;
		volume += object :: Object :: getAggregateVolume (treeAll_);
		volume += object :: Object :: getAggregateVolume (treeProof_);
		volume += object :: Object :: getAggregateVolume (treeAssertion_);
		return volume;
	}
	Size_t
	Expressions :: getSizeOf() const {
		return sizeof (Expressions);
	}
	void
	Expressions :: show (String& string) const {
		//string << tab << "propositions: " << tab << set_.getSize() << endLine;
	}
}
}

#endif /*MDL_MATH_EXPRESSIONS_CPP_*/
