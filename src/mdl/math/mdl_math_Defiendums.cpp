/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_math_Defiendums.cpp                                  */
/* Description:     global container for defiendum terms                     */
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

	inline
	Defiendums :: Defiendums () :
	tree_ (new tree :: Term()),
	count_ (0),
	mutex_ () {
		pthread_mutex_init (&mutex_, NULL);
	}
	Defiendums :: ~ Defiendums () {
		deleteAggregateObject (tree_);
	}
	
	void
	Defiendums :: add (mdl :: term :: Definition* term)
	{
		pthread_mutex_lock (&mutex_);
		if (Config :: shallowParsing()) {
			return;
		}
		tree_->addBranch (term->getExpression(), term);
		++ count_;
		pthread_mutex_unlock (&mutex_);
	}
	mdl :: Term*
	Defiendums :: unifiesWith (const mdl :: term :: Definition* term)
	{
		pthread_mutex_lock (&mutex_);
		Memory :: stack().push();
		Unify_ :: Result_
			result = tree_->unifyDirect<array :: Expression> (term->getExpression());
		Memory :: stack().pop();
		mdl :: Term* resultTerm =
			result.isEmpty() ?
			NULL :
			const_cast<mdl :: Term*>(result.getFirst()->getValue().getFirst()->getData().getValue());
		pthread_mutex_unlock (&mutex_);
		return resultTerm;
	}

	// object :: Object interface
	void
	Defiendums :: commitSuicide() {
		delete this;
	}
	Size_t
	Defiendums :: getVolume() const {
		return getAggregateVolume (tree_);
	}
	Size_t
	Defiendums :: getSizeOf() const {
		return sizeof (Defiendums);
	}
	void
	Defiendums :: show (String& string) const
	{
		//string << tab << "defiendums:    " << tab;
		//string << count_ << endLine;
	}
}
}


