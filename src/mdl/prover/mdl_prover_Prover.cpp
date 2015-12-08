/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_prover_Prover.cpp                                    */
/* Description:     class for the prover                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_PROVER_CPP_
#define MDL_PROVER_PROVER_CPP_

namespace mdl {
namespace prover {

	/****************************
	 *		Private members
	 ****************************/

	template<>
	void
	Prover :: setupTarget<mdl :: proof :: Question> (mdl :: proof :: Question* question)
	{
		if (run_ != NULL) {
			run_->commitSuicide();
		}
		if (Config :: proveInHeap()) {
			run_ = new run :: Heap (format_, subFormat_, question);
		} else {
			run_ = new run :: Boxed (format_, subFormat_, question);
		}
	}
	template<>
	void
	Prover :: setupTarget<mdl :: proof :: Step> (mdl :: proof :: Step* step)
	{
		mdl :: proof :: Question* question = step->questionSelf();
		setupTarget<mdl :: proof :: Question> (question);
	}

	/****************************
	 *		Public members
	 ****************************/

	inline
	Prover :: Prover (Format& format) :
	format_ (format, true),
	subFormat_ (format_, true),
	subSubFormat_ (subFormat_, true),
	run_ (NULL),
	dataStore_ ()
	{
		if (prover_ != NULL) {
			Error* error = new Error(Error :: SEMANTIC, "double instantiation of prover");
			throw error;
		}
		prover_ = this;
	}
	inline
	Prover :: ~ Prover () {
		deleteAggregateObject (run_);
	}

	void
	Prover  :: create (Format& format)
	{
		if (prover_ == NULL) {
			prover_ = new Prover (format);
		}
	}
	inline Prover*
	Prover  :: get() {
		return prover_;
	}
	void
	Prover :: release()
	{
		if (prover_ == NULL) {
			return;
		}
		prover_->commitSuicide();
		prover_ = NULL;
	}
	void
	Prover :: clear()
	{
		if (prover_ == NULL) {
			return;
		}
		if (prover_->run_ == NULL) {
			return;
		}
		prover_->run_->commitSuicide();
		prover_->run_ = NULL;
	}

	bool
	Prover :: provingIsStarted() const {
		return prover_->run_ != NULL;
	}
	bool
	Prover :: prove (const Time timeLimit, mdl :: proof :: Step* step)
	{
		if (Config :: growUpMode() == Config :: GROW_UP_DETERMINED) {
			return proveTarget<mdl :: proof :: Step>(timeLimit, step);
		} else {
			mdl :: proof :: Question*
				question = dynamic_cast<mdl :: proof :: Question*>(step);
			if ((step != NULL) && (question == NULL)) {
				format_.message() << "question is demanded for proving";
				format_.showMessage();
				return false;
			}
			return proveTarget<mdl :: proof :: Question>(timeLimit, question);
		}
	}
	bool
	Prover :: reprove (const Time timeLimit, mdl :: proof :: Step* step) {
		return proveTarget<mdl :: proof :: Step>(timeLimit, step);
	}

	void
	Prover :: plantTree()
	{
		if (Config :: growUpMode() == Config :: GROW_UP_DETERMINED) {
			plantTree<mdl :: proof :: Step>();
		} else {
			plantTree<mdl :: proof :: Question>();
		}
	}
	inline void
	Prover :: growTree () {
		run_->grow();
	}
	void
	Prover :: fellTree()
	{
		Data* data = run_->getData();
		dataStore_.add (data);
		run_->stop();
		run_->commitSuicide();
		run_ = NULL;
	}
	void
	Prover :: infoTree (String& outputBuffer) {
		run_->info (outputBuffer);
	}
	inline void
	Prover :: confirmProof() {
		run_->confirm();
	}

	inline void
	Prover :: showVolume (String& string) const {
		dataStore_.showVolume (string);
	}
	inline void
	Prover :: showTiming (String& string) const {
		dataStore_.showTiming (string);
	}

	// object :: Object implementation
	void
	Prover :: commitSuicide() {
		delete this;
	}
	Size_t
	Prover :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (run_);
		volume += format_.getVolume();
		volume += subFormat_.getVolume();
		volume += subSubFormat_.getVolume();
		volume += dataStore_.getVolume();
		volume += getSizeOf();
		return volume;
	}
	Size_t
	Prover :: getSizeOf() const {
		return sizeof (Prover);
	}
	void
	Prover :: show (String& string) const
	{
		showVolume (string);
		showTiming (string);
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class T>
	bool
	Prover :: proveTarget (const Time timeLimit, T* step)
	{
		typedef T Target;
		if (step == NULL) {
			step = find<Target>();
		}
		if (step == NULL) {
			format_.message() << "nothing to prove";
			format_.showMessage();
			return false;
		} else {
			setupTarget<Target> (step);
		}
		bool result = run_->prove (timeLimit);
		Data* data = run_->getData();
		dataStore_.add (data);
		return result;
	}

	template<class T>
	void
	Prover :: plantTree()
	{
		typedef T Target;
		Target*
			target = find<Target>();
		if (target != NULL) {
			setupTarget<Target> (target);
			run_->start (format_.message());
			format_.showMessage();
		} else {
			format_.message() << "nothing to prove";
			format_.showMessage();
		}
	}

	template<class T>
	T*
	Prover :: find()
	{
		typedef T Target;
		Source* source = Source :: get();
		if (Config :: locationIsSet()) {
			object :: Writable* object = source->find();
			if (object != NULL) {
				mdl :: Proof* proof = dynamic_cast<mdl :: Proof*>(object);
				if (proof != NULL) {
					return findInProof<Target>(proof);
				}
				mdl :: Theorem* theorem = dynamic_cast<mdl :: Theorem*>(object);
				if (theorem != NULL) {
					return findInTheorem<Target>(theorem);
				}
				Target* target = dynamic_cast<Target*>(object);
				if (target != NULL) {
					return target;
				}
			}
			format_.message() << "wrong target to prove";
			format_.showMessage();
			return NULL;
		} else {
			return findInComponents<Target> (source);
		}
	}
	template<class T>
	T*
	Prover :: findInComponents (mdl :: Components* components)
	{
		typedef T Target;
		if (components == NULL) {
			return NULL;
		}
		for (value :: Integer i = 0; i < components->getSize(); ++ i) {
			object :: Verifiable* component = components->getComponent (i);
			mdl :: Proof*
				proof = dynamic_cast<mdl :: Proof*>(component);
			if (proof != NULL) {
				Target* target = findInProof<Target> (proof);
				if (target != NULL) {
					return target;
				}
			}
			mdl :: Contents*
				contents = dynamic_cast<mdl :: Contents*>(component);
			if (contents != NULL) {
				Target* target = findInComponents<Target> (contents);
				if (target != NULL) {
					return target;
				}
			}
		}
		return NULL;
	}
	template<class T>
	T*
	Prover :: findInTheorem (mdl :: Theorem* theorem)
	{
		typedef T Target;
		if (theorem == NULL) {
			return NULL;
		}
		for (value :: Integer i = 0; i < theorem->getProofVector().getSize(); ++ i) {
			mdl :: Proof*
				proof = const_cast<mdl :: Proof*>(theorem->getProofVector().getValue (i));
			Target* target = findInProof<Target> (proof);
			if (target != NULL) {
				return target;
			}
		}
		return NULL;
	}
	template<>
	mdl :: proof :: Question*
	Prover :: findInProof<mdl :: proof :: Question> (mdl :: Proof* proof)
	{
		if (proof == NULL) {
			return NULL;
		}
		for (value :: Integer i = 0; i < proof->getLength(); ++ i) {
			mdl :: proof :: Step* step = const_cast<mdl :: proof :: Step*>(proof->getStep (i));
			mdl :: proof :: Question*
				question = dynamic_cast<mdl :: proof :: Question*>(step);
			if (question != NULL) {
				return question;
			}
			mdl :: proof :: Claim*
				claim = dynamic_cast<mdl :: proof :: Claim*>(step);
			if (claim != NULL) {
				mdl :: Proof* claimProof = const_cast<mdl :: Proof*>(claim->getProof());
				mdl :: proof :: Question*
					question = findInProof<mdl :: proof :: Question> (claimProof);
				if (question != NULL) {
					return question;
				}
			}
		}
		return NULL;
	}
	template<>
	mdl :: proof :: Step*
	Prover :: findInProof<mdl :: proof :: Step> (mdl :: Proof* proof)
	{
		if (proof == NULL) {
			return NULL;
		} else {
			return proof->getQed (0)->getStep();
		}
	}

	/********************************
	 *		Static private members
	 ********************************/

	Prover* Prover :: prover_ = NULL;
}
}

#endif /*MDL_PROVER_PROVER_CPP_*/
