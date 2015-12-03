/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_answer_Question.cpp                         */
/* Description:     unknown step inference                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_PROOF_STEP_QUESTION_CPP_
#define MDL_FORM_PROOF_STEP_QUESTION_CPP_

namespace mdl {
namespace form {
namespace proof {
namespace step {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Question :: Question
	(
		mdl :: proof :: Line* line,
		const Location& location,
		const mdl :: Comments* comments,
		index :: Step localIndex,
		mdl :: Identificator* type,
		array :: Expression* expression,
		mdl :: Theory* theory,
		mdl :: proof :: Scope* scope
	) :
	Ancestor_
	(
		line,
		location,
		comments,
		localIndex,
		type,
		expression,
		theory,
		scope
	),
	isProved_ (false),
	answer_ (NULL),
	guess_ (NULL),
	hint_ (NULL) {
	}
	inline
	Question :: Question (proof :: Step* step) :
	Ancestor_ (step),
	isProved_ (false),
	answer_ (NULL),
	guess_ (NULL),
	hint_ (step) {
	}
	inline
	Question :: Question
	(
		index :: Step index,
		array :: Expression* expression,
		const mdl :: proof :: Step* hint
	) :
	Ancestor_ (index, expression),
	isProved_ (false),
	answer_ (NULL),
	guess_ (NULL),
	hint_ (hint) {
	}
	inline
	Question :: Question (mdl :: Proposition* proposition) :
	Ancestor_ (proposition),
	isProved_ (false),
	answer_ (NULL),
	guess_ (NULL),
	hint_ (NULL) {
	}
	Question :: ~ Question()
	{
		deleteAggregateObject (answer_);
		deleteAggregateObject (guess_);
	}

	// proof :: step :: Question implementation
	void
	Question :: compress (const Time timeLimit)
	{
		isProved_ = false;
		Prover* prover = Prover :: get();
		prover->prove (timeLimit, this);
		if (guess_ != NULL) {
			guess_->commitSuicide();
		}
		guess_ = answer_;
		answer_ = NULL;
		isProved_ = (guess_ != NULL);
	}
	void
	Question :: prove (const Time timeLimit)
	{
		isProved_ = false;
		const mdl :: proof :: Step* newAnswer = NULL;
		Prover* prover = Prover :: get();
		prover->prove (timeLimit, this);
		isProved_ = (answer_ != NULL);
	}
	void
	Question :: clear()
	{
		deleteObject (answer_);
		deleteObject (guess_);
		answer_ = NULL;
		guess_ = NULL;
		hint_ = NULL;
	}
	bool
	Question :: isProved() const {
		return isProved_;
	}
	void
	Question :: confirmAnswer (mdl :: proof :: Step* answer)
	{
		if (answer_ != NULL) {
			answer_->commitSuicide();
		}
		answer_ = answer;
		isProved_ = (answer_ != NULL);
	}
	void
	Question :: confirmGuess()
	{
		if (guess_ == NULL) {
			return;
		}
		if (answer_ != NULL) {
			answer_->commitSuicide();
		}
		answer_ = guess_;
		guess_ = NULL;
	}
	void
	Question :: rejectGuess()
	{
		if (guess_ != NULL) {
			guess_->commitSuicide();
			guess_ = NULL;
		}
	}
	mdl :: proof :: Step*
	Question :: getAnswer() {
		return answer_;
	}
	mdl :: proof :: Step*
	Question :: getGuess() {
		return guess_;
	}
	const mdl :: proof :: Step*
	Question :: getHint() {
		return hint_;
	}
	const mdl :: proof :: Step*
	Question :: getAnswer() const {
		return answer_;
	}
	const mdl :: proof :: Step*
	Question :: getGuess() const {
		return guess_;
	}
	const mdl :: proof :: Step*
	Question :: getHint() const {
		return hint_;
	}

	// proof :: Step implementation
	mdl :: proof :: Step :: Class
	Question :: getClass() const {
		return mdl :: proof :: Step :: QUESTION;
	}
	void
	Question :: addReference (mdl :: proof :: Reference* reference) {
		throw new Error (location_, Error :: SEMANTIC, "proving in a non-proved step.\n");
	}
	void
	Question :: addDown (mdl :: proof :: Step* step)
	{
		if  (answer_ != NULL) {
			answer_->addDown (step);
		}
	}
	index :: Arity
	Question :: getUpArity() const
	{
		if  (answer_ == NULL) {
			return 0;
		} else {
			return answer_->getUpArity();
		}
	}
	index :: Arity
	Question :: getDownArity() const
	{
		if  (answer_ == NULL) {
			return 0;
		} else {
			return answer_->getDownArity();
		}
	}
	mdl :: proof :: Link*
	Question :: getLink()
	{
		if (answer_ == NULL) {
			return NULL;
		} else {
			return answer_->getLink();
		}
	}
	mdl :: proof :: Node*
	Question :: getUp (const index :: Arity i)
	{
		if  (answer_ == NULL) {
			return NULL;
		} else {
			return answer_->getUp (i);
		}
	}
	mdl :: proof :: Step*
	Question :: getDown (const index :: Arity i)
	{
		if  (answer_ == NULL) {
			return NULL;
		} else {
			return answer_->getDown (i);
		}
	}
	const mdl :: proof :: Link*
	Question :: getLink() const
	{
		if (answer_ == NULL) {
			return NULL;
		} else {
			return answer_->getLink();
		}
	}
	const mdl :: proof :: Node*
	Question :: getUp (const index :: Arity i) const
	{
		if  (answer_ == NULL) {
			return NULL;
		} else {
			return answer_->getUp (i);
		}
	}
	const mdl :: proof :: Step*
	Question :: getDown (const index :: Arity i) const
	{
		if  (answer_ == NULL) {
			return NULL;
		} else {
			return answer_->getDown (i);
		}
	}

using manipulator :: endLine;
using manipulator :: space;

	// proof :: Node implementation
	void
	Question :: replicateReference (String& string) const {
		string << Token :: step_  << space << index_;
	}
	void
	Question :: translateReference (String& string) const {
	}

	// proof :: Line implementation
	void
	Question :: incIndex (const index :: Step index)
	{
		Ancestor_ :: incIndex (index);
		if (answer_ != NULL) {
			answer_->incIndex (index);
		}
	}
	void
	Question :: decIndex (const index :: Step index)
	{
		Ancestor_ :: decIndex (index);
		if (answer_ != NULL) {
			answer_->decIndex (index);
		}
	}

	// object :: Verifiable implementation
	void
	Question :: check()
	{
		isVerified_ = false;
		if (answer_ == NULL) {
			Error* error = new Error (location_, Error :: PROVER, "question is not proved.");
			error->message() << *this << endLine;
			throw error;
		}
		try {
			answer_->check();
		} catch (Error* error) {
			error->add (location_);
			error->message() << "question proof failed verification." << endLine;
			error->message() << tab << *this << endLine;
			throw error;
		}
		isVerified_ = true;
	}
	void
	Question :: compress() {
		compress (Config :: getTimeLimit());
	}
	void
	Question :: prove() {
		prove (Config :: getTimeLimit());
	}

	// object :: Writable implementation
	void
	Question :: translate (String& string) const {
		answer_->translate (string);
	}
	void
	Question :: replicate (String& string) const
	{
		if (!Config :: removeComments() && (Ancestor_ :: comments_ != NULL)) {
			string << Ancestor_ :: location_.getIndent();
			Ancestor_ :: comments_->replicate (string);
			string << endLine;
		}
		if ((answer_ == NULL) || Config :: compress()) {
			string << Ancestor_ :: location_.getIndent() << Token :: step_ << space;
			string << (index_ + 1) << space << Token :: colon_ << space;

			Ancestor_ :: type_->replicateName (string); string << space;
			string << Token :: equality_ << space;

			string << Token :: question_ << space;
			string << Token :: turnstile_ << space;

			Ancestor_ :: expression_->write (string); string << space;
			string << Token :: semicolon_ << endLine;
		} else {
			answer_->replicate (string);
		}
	}
	bool
	Question :: lookup() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return true;
		} else {
			return proof :: Step :: lookup();
		}
	}
	const object :: Writable*
	Question :: find() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		} else {
			return proof :: Step :: find();
		}
	}

	// object :: Object implementation
	void
	Question :: commitSuicide() {
		delete this;
	}
	Size_t
	Question :: getVolume() const
	{
		Size_t volume = 0;
		volume += Ancestor_ :: getVolume();
		volume += getAggregateVolume (answer_);
		volume += getAggregateVolume (guess_);
		return volume;
	}
	Size_t
	Question :: getSizeOf() const {
		return sizeof (Question);
	}
}
}
}
}

#endif /*MDL_FORM_PROOF_STEP_QUESTION_CPP_*/
