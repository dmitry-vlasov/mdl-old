/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_term_Case.cpp                        */
/* Description:     elementary case of proposition usage                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace form {
namespace evaluation {
namespace term {

	/****************************
	 *		Public members
	 ****************************/

	Case :: Case
	(
		mdl :: proof :: Step* step,
		bool sign
	) :
	location_ (),
	theory_ (NULL),
	sign_ (sign),
	id_ (new form :: Identificator (step->getScope()->getAssertion()->getIdentificator())),
	name_ (step->getScope()->getProof()->getName()),
	path_ (INITIAL_PATH_CAPACITY),
	proof_ (step->getScope()->getProof()),
	step_ (step) {
		initPath (step);
	}
	inline
	Case :: Case
	(
		const Location& location,
		bool sign,
		mdl :: Identificator* id,
		value :: Name name,
		const vector :: value :: Integer& path,
		mdl :: Theory* theory
	) :
	location_ (location),
	theory_ (theory),
	sign_ (sign),
	id_ (id),
	name_ (name),
	path_ (path),
	proof_ (NULL),
	step_ (NULL) {
	}
	Case :: ~ Case() {
		deleteAggregateObject (id_);
	}

	// evaluation :: Case implementation
	bool
	Case :: getSign() const {
		return sign_;
	}
	mdl :: proof :: Step*
	Case :: getStep() {
		return step_;
	}
	const mdl :: proof :: Step*
	Case :: getStep() const {
		return step_;
	}

	// object :: Buildable implementation
	void
	Case :: build()
	{
		findProof();
		findStep();
	}

using manipulator :: space;
using manipulator :: endLine;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Case :: translate (String&) const {
	}
	void
	Case :: replicate (String& string) const
	{
		/* Example:
		 *
			+ theorem xxx proof pr1 step 8
			+ theorem xxx.yyy.zzz proof pr1 step (15.23.4)
			- theorem xxx.yyy proof prf2 step (28.5)
			- theorem zzz.yyy proof 3 step 7
		 */
		if (sign_) {
			string << Token :: plus_ << space;
		} else {
			string << Token :: minus_ << space;
		}
		string << Token :: theorem_ << space;
		id_->replicate (string);
		string << Token :: comma_ << space << Token :: proof_ << space;
		if (name_ != Table :: defaultName()) {
			string << Table :: names()->get (name_) << space;
		}
		string << Token :: step_ << space;
		if (path_.getSize() == 1) {
			string << path_ [0];
		} else {
			string << Token :: openBracket_;
			for (value :: Integer i = 0; i < path_.getSize(); ++ i) {
				string << path_ [i];
				if (i + 1 < path_.getSize()) {
					string << Token :: dot_;
				}
			}
			string << Token :: closeBracket_;
		}
	}

	// object :: Object interface
	void
	Case :: commitSuicide() {
		delete this;
	}
	Size_t
	Case :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (id_);
		volume += path_.getVolume();
		return volume;
	}
	Size_t
	Case :: getSizeOf() const {
		return sizeof (Case);
	}
	void
	Case :: show (String& string) const	{
		replicate (string);
	}

	/****************************
	 *		Public members
	 ****************************/

	void
	Case :: findProof()
	{
		const index :: Assertion
			index = theory_->getIndex (id_);
		if (index == index :: undefined :: FORM) {
			throw new Error (location_, Error :: SEMANTIC, "reference to undefined assertion");
		}
		form :: Theorem*
			theorem = dynamic_cast<form :: Theorem*>(Math :: assertions()->get (index));
		if (theorem != NULL) {
			proof_ = theorem->getProof (name_);
		}
		if (proof_ == NULL) {
			throw new Error (location_, Error :: SEMANTIC, "undefined proof in FRiS evaluation case");
		}
	}
	void
	Case :: findStep ()
	{
		mdl :: Proof* proof = proof_;
		mdl :: proof :: Step* step = NULL;
		for (value :: Integer i = 0; i < path_.getSize(); ++ i) {
			const index :: Step
				index = path_.getValue (i);
			 step = proof->getStep (index);
			 if (i + 1 < path_.getSize()) {
				 mdl :: proof :: Claim*
				 	 claim = dynamic_cast<mdl :: proof :: Claim*>(step);
				 if (claim == NULL) {
					 throw new Error (step->getLocation(), Error :: SEMANTIC, "claim is required");
				 }
				 proof = claim->getProof();
			 }
		}
		step_ = step;
	}

	void
	Case :: initPath (const mdl :: proof :: Step* step)
	{
		const mdl :: proof :: Claim*
			claim = step->getScope()->getClaim();
		if (claim != NULL) {
			initPath (claim);
		}
		path_.add (step->getIndex());
	}
}
}
}
}


