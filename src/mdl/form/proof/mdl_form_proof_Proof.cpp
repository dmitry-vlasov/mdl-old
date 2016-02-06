/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_Proof.cpp                                 */
/* Description:     proof class                                              */
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
namespace proof {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Proof :: Proof() :
	form :: Identifiable(),
	firstLine_ (NULL),
	lastLine_ (NULL),
	stepVector_ (DEFAULT_STEP_VECTOR_CAPACITY),
	qedVector_ (DEFAULT_QED_VECTOR_CAPACITY),
	scope_ (NULL),
	scopeUp_ (NULL),
	isVerified_ (false),
	isCompressed_ (false)
	{
		if (owner_ == NULL) {
			owner_ = this;
			Refiner :: init();
		}
	}
	Proof :: Proof
	(
		const Location& location,
		const mdl :: Comments* comments,
		mdl :: proof :: Line* firstLine,
		const vector :: parser :: Step& stepVector,
		mdl :: Theory* theory
	) :
	form :: Identifiable (location, comments, Table :: defaultName(), theory),
	firstLine_ (firstLine),
	lastLine_ (NULL),
	stepVector_ (stepVector),
	qedVector_ (DEFAULT_QED_VECTOR_CAPACITY),
	scope_ (NULL),
	scopeUp_ (NULL),
	isVerified_ (false),
	isCompressed_ (false)
	{
		mdl :: proof :: Line* line = firstLine_;
		while (line != NULL) {
			mdl :: proof :: Qed*
				qed = dynamic_cast<mdl :: proof :: Qed*>(line);
			if (qed != NULL) {
				qedVector_.add (qed);
			}
			line = line->getNext();
		}
		if (owner_ == NULL) {
			owner_ = this;
			Refiner :: init();
		}
	}
	Proof :: Proof
	(
		mdl :: proof :: Step* step,
		index :: Step length
	) :
	form :: Identifiable
	(
		step->getLocation(),
		NULL,
		Table :: defaultName(),
		step->getScope()->getProof()->getTheory()
	),
	firstLine_ (NULL),
	lastLine_ (NULL),
	stepVector_ (length),
	qedVector_ (DEFAULT_QED_VECTOR_CAPACITY),
	scope_ (NULL),
	scopeUp_ (NULL),
	isVerified_ (false),
	isCompressed_ (false)
	{
		if (owner_ == NULL) {
			owner_ = this;
			Refiner :: init();
		}
	}
	Proof :: Proof (const mdl :: Assertion* problem) :
	firstLine_ (NULL),
	lastLine_ (NULL),
	stepVector_ (problem->getPropArity()),
	qedVector_ (problem->getPropArity()),
	scope_ (NULL),
	scopeUp_ (NULL),
	isVerified_ (false),
	isCompressed_ (false)
	{
		if (owner_ == NULL) {
			owner_ = this;
			Refiner :: init();
		}
	}

	Proof :: ~ Proof()
	{
		if (owner_ == this) {
			owner_ = NULL;
			Timing :: release();
			Refiner :: release();
		}
		deleteAggregateObject (comments_);
		deleteAggregateObject (scope_);

		const mdl :: proof :: Line*
			line = firstLine_;
		while (line != NULL) {
			const mdl :: proof :: Line*
				next = line->getNext();
			deleteAggregateObject (line);
			line = next;
		}
	}

	void
	Proof :: verifyStructure() const
	{
		index :: Step stepCount = 0;
		index :: Arity qedCount = 0;
		const mdl :: proof :: Line*
			line = firstLine_;
		while (line != NULL) {
			const mdl :: proof :: Step*
				step = dynamic_cast<const mdl :: proof :: Step*>(line);
			if (step != NULL) {
				assert (step->getIndex() == stepCount);
				for (index :: Arity i = 0; i < step->getUpArity(); ++ i) {
					const mdl :: proof :: Node* upNode = step->getUp (i);
					const mdl :: proof :: Step* upStep =
						dynamic_cast<const mdl :: proof :: Step*>(upNode);
					if (upStep != NULL) {
						const index :: Step index =
							step->getLink()->getReferences()->get (i)->getIndex();
						assert (upStep == stepVector_.getValue (index));
					}
				}
				++ stepCount;
			}
			const mdl :: proof :: Qed*
				qed = dynamic_cast<const mdl :: proof :: Qed*>(line);
			if (qed != NULL) {
				++ qedCount;
			}
			if (line->getNext() == NULL) {
				assert (line == lastLine_);
			}
			line = line->getNext();
		}
		assert (stepCount == stepVector_.getSize());
		assert (qedCount == qedVector_.getSize());

	}

	// mdl :: Proof implementation
	bool
	Proof :: isCompressed() const {
		return isCompressed_;
	}
	index :: Step
	Proof :: getLength() const {
		return stepVector_.getSize();
	}
	index :: Arity
	Proof :: getQedArity() const {
		return qedVector_.getSize();
	}
	void
	Proof :: addStep (mdl :: proof :: Step* step)
	{
		addLine (step);
		stepVector_.add (step);
	}
	void
	Proof :: addVariable (mdl :: proof :: Variable* variable) {
		addLine (variable);
	}
	void
	Proof :: addQed (mdl :: proof :: Qed* qed)
	{
		addLine (qed);
		qedVector_.add (qed);
	}
	mdl :: proof :: Step*
	Proof :: getStep (const index :: Step index)
	{
		if (index >= stepVector_.getSize()) {
			return NULL;
		}
		return stepVector_.getValue (index);
	}
	mdl :: proof :: Qed*
	Proof :: getQed (const index :: Arity i) {
		return qedVector_.getValue (i);
	}
	mdl :: proof :: Line*
	Proof :: getFirst() {
		return firstLine_;
	}
	mdl :: proof :: Line*
	Proof :: getLast() {
		return lastLine_;
	}
	const mdl :: proof :: Step*
	Proof :: getStep (const index :: Step index) const
	{
		if (index >= stepVector_.getSize()) {
			return NULL;
		}
		return stepVector_.getValue (index);
	}
	const mdl :: proof :: Qed*
	Proof :: getQed (const index :: Arity i) const {
		return qedVector_.getValue (i);
	}
	const mdl :: proof :: Line*
	Proof :: getFirst() const {
		return firstLine_;
	}
	const mdl :: proof :: Line*
	Proof :: getLast() const {
		return lastLine_;
	}

	// object :: Scoping implementation
	mdl :: proof :: Scope*
	Proof :: buildScope (mdl :: proof :: Scope* scope)
	{
		scopeUp_ = scope;
		scope_ = new proof :: scope :: Step (scope, this);
		mdl :: proof :: Scope* sc = scope_;

		mdl :: proof :: Line* line = firstLine_;
		while (line != NULL) {
			sc = line->buildScope (sc);
			if (line->getNext() == NULL) {
				lastLine_ = line;
			}
			line = line->getNext();
		}
		return sc;
	}
	void
	Proof :: setScope (mdl :: proof :: Scope* scope) {
		scope_ = scope;
	}
	mdl :: proof :: Scope*
	Proof :: getScope() {
		return scope_;
	}
	const mdl :: proof :: Scope*
	Proof :: getScope() const {
		return scope_;
	}

	// object :: Identifiable interface
	const Location&
	Proof :: getLocation() const {
		return Identifiable :: getLocation();
	}
	value :: Name
	Proof :: getName() const {
		return Identifiable :: getName();
	}
	void
	Proof :: translateName (String& string, const index :: Arity i) const {
		Identifiable :: translateName (string, i);
	}
	void
	Proof :: replicateName (String& string) const {
		Identifiable :: replicateName (string);
	}
	mdl :: Theory*
	Proof :: getTheory() {
		return Identifiable :: getTheory();
	}
	mdl :: Identificator*
	Proof :: getIdentificator() {
		return Identifiable :: getIdentificator();
	}
	const mdl :: Theory*
	Proof :: getTheory() const {
		return Identifiable :: getTheory();
	}
	const mdl :: Identificator*
	Proof :: getIdentificator() const {
		return Identifiable :: getIdentificator();
	}

	// object :: Verifiable implementation
	void
	Proof :: check()
	{
		isVerified_ = true;
		mdl :: proof :: Line* line = firstLine_;
		while (line != NULL) {
			proof :: Step* step =
				dynamic_cast<proof :: Step*>(line);
			if (step != NULL) {
				if (step->getClass() == mdl :: proof :: Step :: QUESTION) {
					isVerified_ = false;
				} else {
					line->check();
				}
			} else {
				line->check();
			}
			line = line->getNext();
		}
	}
	void
	Proof :: compress()
	{
		mdl :: Assertion* assertion = scope_->getAssertion();
		if (assertion->getName() == Config :: compressAssertion()) {
			compressExact();
		} else if (Config :: compressAssertion() == Table :: defaultName()){
			compressMass();
		}
	}
	void
	Proof :: reprove()
	{
		Proof* clearProof = new Proof();
		clearProof->buildScope (scopeUp_);
		mdl :: proof :: Line* line = firstLine_;
		index :: Step stepIndex = 0;
		while (line != NULL) {
			if (line->getSort() == mdl :: proof :: Line :: QED) {
				mdl :: proof :: Qed*
					qed = dynamic_cast<mdl :: proof :: Qed*>(line);
				mdl :: proof :: Provable*
					proposition = qed->getProp();
				mdl :: proof :: Step* step = qed->getStep();
				mdl :: proof :: Question*
					newQuestion = new form :: proof :: step :: Question
					(
						stepIndex,
						new array :: Expression (step->getExpression()),
						step
					);
				mdl :: proof :: Qed*
					newQed = new form :: proof :: Qed
					(
						proposition->getIndex(),
						stepIndex
					);
				clearProof->addStep (newQuestion);
				clearProof->addQed (newQed);
				++ stepIndex;
			}
			line = line->getNext();
		}
		bool success = true;
		try {
			clearProof->prove();
		} catch (Error* error) {
			success = false;
		}
		clearProof->commitSuicide();
	}
	void
	Proof :: prove()
	{
		Timing timing (this);
		const Time timeLimit = timing.calculateTimeLimit (false);
		mdl :: proof :: Line* line = firstLine_;
		timing.timer().start();
		while (line != NULL) {
			mdl :: proof :: Line* next = line->getNext();
			if (line->getSort() == mdl :: proof :: Line :: STEP) {
				mdl :: proof :: Step* step = dynamic_cast<mdl :: proof :: Step*>(line);
				if (step->getClass() == mdl :: proof :: Step :: QUESTION) {
					mdl :: proof :: Question*
						question = dynamic_cast<mdl :: proof :: Question*>(step);
					question->prove (timeLimit);
					if (question->isProved() && (question->getAnswer() == NULL)) {
						removeLine (line);
						line->commitSuicide();
					}
				}
			}
			line = next;
		}
		timing.timer().stop();
		timing.incrementProveActs();
		writeProvingLog (scope_->getAssertion(), timing);
		//check();
	}
	bool
	Proof :: isVerified() const {
		return isVerified_;
	}

	// object :: Buildable implementation
	void
	Proof :: build()
	{
		const mdl :: proof :: Line*
			line = firstLine_;
		while (line != NULL) {
			const_cast<mdl :: proof :: Line* const>(line)->build();
			line = line->getNext();
		}
	}

using nstd :: manipulator :: endLine;

	// object :: Writable implementation
	void
	Proof :: translate (String&) const {
	}
	void
	Proof :: replicate (String& string) const
	{
		if (!Config :: removeComments() && (comments_ != NULL)) {
			comments_->replicate (string);
		}
		string << Token :: openBrace_ << endLine;
		const mdl :: proof :: Line*
			line = firstLine_;
		while (line != NULL) {
			line->replicate (string);
			line = line->getNext();
		}
		string << location_.getIndent() << Token :: closeBrace_ << endLine;
	}
	bool
	Proof :: lookup() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return true;
		}
		const mdl :: proof :: Line*
			line = firstLine_;
		while (line != NULL) {
			if (line->lookup()) {
				return true;
			}
			line = line->getNext();
		}
		return false;
	}
	object :: Writable*
	Proof :: find()
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		}
		mdl :: proof :: Line*
			line = firstLine_;
		object :: Writable* object = NULL;
		while (line != NULL) {
			object = line->find();
			if (object != NULL) {
				return object;
			}
			line = line->getNext();
		}
		return NULL;
	}
	const object :: Writable*
	Proof :: find() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		}
		const mdl :: proof :: Line*
			line = firstLine_;
		const object :: Writable* object = NULL;
		while (line != NULL) {
			object = line->find();
			if (object != NULL) {
				return object;
			}
			line = line->getNext();
		}
		return NULL;
	}

	// object :: Object implementation
	void
	Proof :: commitSuicide() {
		delete this;
	}
	Size_t
	Proof :: getSizeOf() const  {
		return sizeof (Proof);
	}
	Size_t
	Proof :: getVolume() const
	{
		Size_t volume = 0;
		if (owner_ == this) {
			volume += Refiner :: getVolume();
		}
		volume += Identifiable :: getVolume();
		volume += stepVector_.getVolume();
		volume += qedVector_.getVolume();
		volume += getAggregateVolume (scope_);

		const mdl :: proof :: Line*
			line = firstLine_;
		while (line != NULL) {
			volume += getAggregateVolume (line);
			line = line->getNext();
		}
		return volume;
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Proof :: compressExact()
	{
		const mdl :: Assertion* assertion = scope_->getAssertion();
		const index :: Step initialLength = getLength();
		questionSelf();
		Timing timing (this);
		const Time timeLimit = timing.calculateTimeLimit (true);
		mdl :: proof :: Line* line = firstLine_;
		timing.timer().start();
		while (line != NULL) {
			mdl :: proof :: Line* next = line->getNext();
			if (line->getSort() == mdl :: proof :: Line :: STEP) {
				//const mdl :: proof :: Step*
				//	step = dynamic_cast<const mdl :: proof :: Step*>(line);
				//const_cast<mdl :: proof :: Step*>(step)->compress();
				compressStep (line, timeLimit);
			}
			line = next;
		}
		timing.timer().stop();
		const index :: Step compressedLength = getLength();
		writeExactCompressionLog
		(
			assertion,
			initialLength,
			compressedLength,
			timing
		);
		isCompressed_ = true;
	}
	void
	Proof :: compressMass()
	{
		const mdl :: Assertion* assertion = scope_->getAssertion();
		Refiner :: beforeCompression (this);
		if (!Refiner :: isCompressable (assertion)) {
			return;
		}
		questionSelf();
		Timing timing (this);
		const Time timeLimit = timing.calculateTimeLimit (false);
		mdl :: proof :: Line* line = firstLine_;
		timing.timer().start();
		while (line != NULL) {
			mdl :: proof :: Line* next = line->getNext();
			if (line->getSort() == mdl :: proof :: Line :: STEP) {
				mdl :: proof :: Step*
					step = dynamic_cast<mdl :: proof :: Step*>(line);
				step->compress();
				compressStep (line, timeLimit);
			}
			line = next;
		}
		timing.timer().stop();
		timing.incrementProveActs();
		Refiner :: afterCompression (this);
		writeMassCompressionLog (assertion);
		isCompressed_ = true;
	}

	void
	Proof :: addLine (mdl :: proof :: Line* line)
	{
		if (firstLine_ == NULL) {
			firstLine_ = line;
			lastLine_ = line;
			line->buildScope (scope_);
		} else {
			mdl :: proof :: Scope*
				scope = lastLine_->getScope();
			lastLine_->setNext (line);
			line->setPrev (lastLine_);
			lastLine_ = line;
			line->buildScope (scope);
		}
	}
	void
	Proof :: addVariableFirst (mdl :: proof :: Variable* variable)
	{
		mdl :: proof :: Line* firstLine = firstLine_;
		firstLine_ = variable;
		static_cast<mdl :: proof :: Line*>(variable)->setNext (firstLine);
		firstLine->setPrev (variable);
		/*if (firstLine_ == NULL) {
			firstLine_ = line;
			lastLine_ = line;
			line->buildScope (scope_);
		} else {
			mdl :: proof :: Scope*
				scope = lastLine_->getScope();
			lastLine_->setNext (line);
			line->setPrev (lastLine_);
			lastLine_ = line;
			line->buildScope (scope);
		}*/
	}
	void
	Proof :: replaceLine
	(
		mdl :: proof :: Line* oldLine,
		mdl :: proof :: Line* newLine
	)
	{
		if (firstLine_ == oldLine) {
			firstLine_ = newLine;
		}
		if (lastLine_ == oldLine) {
			lastLine_ = newLine;
		}
		if (oldLine->getPrev() != NULL) {
			newLine->setPrev (oldLine->getPrev());
			oldLine->getPrev()->setNext (newLine);
			oldLine->setPrev (NULL);
		}
		if (oldLine->getNext() != NULL) {
			newLine->setNext (oldLine->getNext());
			oldLine->getNext()->setPrev (newLine);
			oldLine->setNext (NULL);
		}
		if (oldLine->getSort() == mdl :: proof :: Line :: STEP) {
			mdl :: proof :: Step*
				oldStep = dynamic_cast<mdl :: proof :: Step*>(oldLine);
			mdl :: proof :: Step*
				newStep = dynamic_cast<mdl :: proof :: Step*>(newLine);
			stepVector_.getReference (oldStep->getIndex()) = newStep;
		}
	}
	void
	Proof :: insertLine (mdl :: proof :: Line* prev, mdl :: proof :: Line* line)
	{
		mdl :: proof :: Line*
			next = (prev == NULL) ? firstLine_: prev->getNext();
		if (prev == NULL) {
			firstLine_ = line;
		}
		if (lastLine_ == prev) {
			lastLine_ = line;
		}
		if (prev != NULL) {
			prev->setNext (line);
			line->setPrev (prev);
		}
		if (next != NULL) {
			next->setPrev (line);
			line->setNext (next);
		}
		if (line->getSort() == mdl :: proof :: Line :: STEP) {
			mdl :: proof :: Step*
				step = dynamic_cast<mdl :: proof :: Step*>(line);
			stepVector_.insert (step, step->getIndex());
			while (next != NULL) {
				next->incIndex (step->getIndex());
				next = next->getNext();
			}
		}
	}
	mdl :: proof :: Line*
	Proof :: removeLine (mdl :: proof :: Line* line)
	{
		mdl :: proof :: Line* next = line->getNext();
		mdl :: proof :: Line* prev = line->getPrev();
		if (firstLine_ == line) {
			firstLine_ = next;
		}
		if (lastLine_ == line) {
			lastLine_ = prev;
		}
		if (prev != NULL) {
			prev->setNext (next);
			line->setPrev (NULL);
		}
		if (next != NULL) {
			next->setPrev (prev);
			line->setNext (NULL);
		}
		if (line->getSort() == mdl :: proof :: Line :: STEP) {
			mdl :: proof :: Step*
				step = dynamic_cast<mdl :: proof :: Step*>(line);
			stepVector_.remove (step->getIndex());
			while (next != NULL) {
				next->decIndex (step->getIndex());
				next = next->getNext();
			}
		}
		return prev;
	}

	void
	Proof :: questionSelf()
	{
		mdl :: proof :: Line* line = firstLine_;
		while (line != NULL) {
			mdl :: proof :: Line* next = line->getNext();
			if (line->getSort() == mdl :: proof :: Line :: STEP) {
				mdl :: proof :: Step*
					step = dynamic_cast<mdl :: proof :: Step*>(line);
				mdl :: proof :: Question*
					question = step->questionSelf();
				replaceLine (step, question);
			}
			line = next;
		}
	}
	bool
	Proof :: compressRest (mdl :: proof :: Line* line, const Time timeLimit)
	{
		mdl :: proof :: Line* rest = line;
		while (rest != NULL) {
			mdl :: proof :: Line* next = rest->getNext();
			if (rest->getSort() == mdl :: proof :: Line :: STEP) {
				mdl :: proof :: Question*
					question = dynamic_cast<mdl :: proof :: Question*>(rest);
				question->compress (timeLimit);
				if (!question->isProved()) {
					return false;
				} /*else if (question->getGuess() == NULL) {
					removeLine (rest);
					const_cast<mdl :: proof :: Line*>(rest)->commitSuicide();
				}*/
			}
			rest = next;
		}
		return true;
	}
	void
	Proof :: confirmCompression (mdl :: proof :: Line* line)
	{
		mdl :: proof :: Line* rest = line;
		while (rest != NULL) {
			mdl :: proof :: Line* next = rest->getNext();
			if (rest->getSort() == mdl :: proof :: Line :: STEP) {
				mdl :: proof :: Question*
					question = dynamic_cast<mdl :: proof :: Question*>(rest);
				question->confirmGuess();
			}
			rest = next;
		}
	}
	void
	Proof :: rejectCompression (mdl :: proof :: Line* line)
	{
		mdl :: proof :: Line* rest = line;
		while (rest != NULL) {
			if (rest->getSort() == mdl :: proof :: Line :: STEP) {
				mdl :: proof :: Question*
					question = dynamic_cast<mdl :: proof :: Question*>(rest);
				question->rejectGuess();
			}
			rest = rest->getNext();
		}
	}
	void
	Proof :: compressStep (mdl :: proof :: Line* line, const Time timeLimit)
	{
		mdl :: proof :: Line* next = line->getNext();
		if (next->getSort() == mdl :: proof :: Line :: QED) {
			return;
		}
		mdl :: proof :: Question*
			question = dynamic_cast<mdl :: proof :: Question*>(line);

		mdl :: proof :: Line* prev = removeLine (question);

		if (!compressRest (next, timeLimit)) {
			rejectCompression (next);
			insertLine (prev, line);
		} else {
			confirmCompression (next);
			question->commitSuicide();
		}
	}

using manipulator :: tab;
using manipulator :: endLine;
using manipulator :: space;

	void
	Proof :: writeMassCompressionLog (const mdl :: Assertion* assertion)
	{
		if (Config :: verbosity() >= Config :: VERBOSE_MED) {
			static bool firstLine = true;
			if (firstLine) {
				Engine :: get()->log().message (Log :: COMPRESS) << "count:" << tab;
				Engine :: get()->log().message (Log :: COMPRESS) << "index:" << tab;
				Engine :: get()->log().message (Log :: COMPRESS) << "original:" << tab;
				Engine :: get()->log().message (Log :: COMPRESS) << "compressed:" << tab;
				Engine :: get()->log().message (Log :: COMPRESS) << "factor:" << tab;
				Engine :: get()->log().message (Log :: COMPRESS) << endLine;
				firstLine = false;
			}
			Engine :: get()->log().message (Log :: COMPRESS) << Refiner :: getCompressedCount() << tab;
			Engine :: get()->log().message (Log :: COMPRESS) << assertion->getIndex() << tab;
			Engine :: get()->log().message (Log :: COMPRESS) << Refiner :: getOriginalProofLength() << tab;
			Engine :: get()->log().message (Log :: COMPRESS) << Refiner :: getCompressedProofLength() << tab;
			Engine :: get()->log().message (Log :: COMPRESS) << Refiner :: getCompressionFactor() << tab;
			Engine :: get()->log().message (Log :: COMPRESS) << endLine;
		}
	}
	void
	Proof :: writeExactCompressionLog
	(
		const mdl :: Assertion* assertion,
		const index :: Step initialProofLength,
		const index :: Step compressedProofLength,
		const Timing& timing
	)
	{
		if (Config :: logCompression()) {
			const double compressionFactor =
					static_cast<double>(initialProofLength) /
					static_cast<double>(compressedProofLength);
			Engine :: get()->log().message (Log :: COMPRESS) << "assertion         ";
			Engine :: get()->log().message (Log :: COMPRESS) << Table :: names()->get (assertion->getName()) << endLine;
			Engine :: get()->log().message (Log :: COMPRESS) << "initial_length    ";
			Engine :: get()->log().message (Log :: COMPRESS) << initialProofLength << endLine;
			Engine :: get()->log().message (Log :: COMPRESS) << "compressed_length ";
			Engine :: get()->log().message (Log :: COMPRESS) << compressedProofLength << endLine;
			Engine :: get()->log().message (Log :: COMPRESS) << "factor            ";
			Engine :: get()->log().message (Log :: COMPRESS) << compressionFactor << endLine;
			Engine :: get()->log().message (Log :: COMPRESS) << "time              ";
			Engine :: get()->log().message (Log :: COMPRESS) << timing.getTimer().getSeconds() << endLine;
			Engine :: get()->log().message (Log :: COMPRESS) << endLine;
		}
	}
	void
	Proof :: writeProvingLog (const mdl :: Assertion* assertion, const Timing& timing)
	{
		if (Config :: logProving()) {
			Engine :: get()->log().message (Log :: PROVER) << "assertion ";
			Engine :: get()->log().message (Log :: PROVER) << Table :: names()->get (assertion->getName()) << endLine;
			Engine :: get()->log().message (Log :: PROVER) << "time      ";
			Engine :: get()->log().message (Log :: PROVER) << timing.getTimer().getSeconds() << endLine;
			Engine :: get()->log().message (Log :: PROVER) << endLine;
		}
	}

	/************************************
	 *		Static private attributes
	 ************************************/

	Proof* Proof :: owner_ = NULL;
}
}
}


