/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_refactor_redundant_Steps.cpp                         */
/* Description:     remove redundant proof steps                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_REFACTOR_REDUNDANT_STEPS_CPP_
#define MDL_REFACTOR_REDUNDANT_STEPS_CPP_

namespace mdl {
namespace refactor {
namespace redundant {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Steps :: Steps (Format& format) :
	format_ (format, true),
	subFormat_ (format_, true)
	{
	}
	inline
	Steps :: ~ Steps () {
	}

	void
	Steps :: refactor (mdl :: Source* source)
	{
		if (Config :: deepRefactoring()) {
			for (index :: Assertion i = 0; i < Math :: assertions()->getTheoremNumber(); ++ i) {
				mdl :: Assertion* assertion = Math :: assertions()->getTheorem (i);
				Theorem* theorem = dynamic_cast<Theorem*>(assertion);
				vector :: Proof& proofVector = theorem->getProofVector();
				for (value :: Integer j = 0; j < proofVector.getSize(); ++ j) {
					mdl :: Proof* proof = proofVector.getValue (j);
					BlockProof_* blockProof = dynamic_cast<BlockProof_*>(proof);
					while (removeUnusedSteps (blockProof->proof_));
					while (removeDuplicateSteps (blockProof->proof_));
				}
			}
		} else {
			// not done yet
		}
	}

	bool
	Steps :: removeUnusedSteps (mdl :: Proof* proofInterface)
	{
		Proof_* proof = dynamic_cast<Proof_*>(proofInterface);
		if (proof == NULL) {
			BlockProof_* blockProof = dynamic_cast<BlockProof_*>(proofInterface);
			proof = dynamic_cast<Proof_*>(blockProof->proof_);
		}

		// Array which indicates, which hypotheses are used in proofs.
		const index :: Step length = proof->getLength();
		bool used [length];
		for (index :: Step i = 0; i < length; ++ i) {
			used [i] = false;
		}
		collectUsedSteps_tree (proof, used);
		index :: Step unused = index :: undefined :: STEP;
		if (findUnusedStep (used, length, unused)) {
			removeUnusedStepFromProof (proof, unused);
			removeUnusedStepFromReferences (proof, unused);
			removeUnusedStepFromQed (proof, unused);
			return true;
		} else {
			return false;
		}
	}
	bool
	Steps :: removeDuplicateSteps (mdl :: Proof* proofInterface)
	{
		Proof_* proof = dynamic_cast<Proof_*>(proofInterface);
		if (proof == NULL) {
			BlockProof_* blockProof = dynamic_cast<BlockProof_*>(proofInterface);
			proof = dynamic_cast<Proof_*>(blockProof->proof_);
		}
		index :: Step original = index :: undefined :: ARITY;
		index :: Step duplicate = index :: undefined :: ARITY;
		if (findDuplicateSteps (proof, original, duplicate)) {
			removeDuplicateStepFromProof (proof, duplicate);
			removeDuplicateStepFromReferences (proof, original, duplicate);
			removeDuplicateStepFromQed (proof, original, duplicate);
			return true;
		} else {
			return false;
		}
	}
	bool
	Steps :: removeUnusedSteps (mdl :: Theorem* theorem)
	{
		bool result = false;
		vector :: Proof& proofVector = theorem->getProofVector();
		for (value :: Integer i = 0; i < proofVector.getSize(); ++ i) {
			mdl :: Proof* proof = proofVector.getValue (i);
			if (removeUnusedSteps (proof)) {
				result = true;
			}
		}
		return result;
	}
	bool
	Steps :: removeDuplicateSteps (mdl :: Theorem* theorem)
	{
		bool result = false;
		vector :: Proof& proofVector = theorem->getProofVector();
		for (value :: Integer i = 0; i < proofVector.getSize(); ++ i) {
			mdl :: Proof* proof = proofVector.getValue (i);
			if (removeDuplicateSteps (proof)) {
				result = true;
			}
		}
		return result;
	}

	// object :: Object implementation
	void
	Steps :: commitSuicide() {
		delete this;
	}
	Size_t
	Steps :: getVolume() const
	{
		Size_t volume = 0;
		volume += format_.getVolume();
		volume += subFormat_.getVolume();
		return volume;
	}
	Size_t
	Steps :: getSizeOf() const {
		return sizeof (Steps);
	}
	void
	Steps :: show (String& string) const
	{
	}

	/****************************
	 *		Private members
	 ****************************/

	// This method is dumb: it does not get all unused.
	void
	Steps :: collectUsedSteps_plain (const mdl :: Proof* proof, bool used[])
	{
		for (index :: Step i = 0; i < proof->getLength(); ++ i) {
			const mdl :: proof :: Step* step = proof->getStep (i);
			const mdl :: proof :: Link* link = step->getLink();
			const mdl :: proof :: References* references = link->getReferences();
			for (index :: Arity j = 0; j < references->getArity(); ++ j) {
				const mdl :: proof :: Reference* reference = references->get (j);
				if (reference->getKind() == Token :: STEP) {
					used [reference->getIndex()] = true;
				}
			}
		}
		for (index :: Arity i = 0; i < proof->getQedArity(); ++ i) {
			const mdl :: proof :: Qed* qed = proof->getQed (i);
			used [qed->getIndexStep()] = true;
		}
	}

	// This method is smart: it gets all unused.
	void
	Steps :: collectUsedSteps_tree (const mdl :: Proof* proof, bool used[])
	{
		for (index :: Arity i = 0; i < proof->getQedArity(); ++ i) {
			const mdl :: proof :: Qed* qed = proof->getQed (i);
			const mdl :: proof :: Step* step = qed->getStep();
			collectUsedSteps_step (step, used);
		}
	}
	void
	Steps :: collectUsedSteps_step (const mdl :: proof :: Step* step, bool used[])
	{
		used [step->getIndex()] = true;
		for (index :: Arity i = 0; i < step->getUpArity(); ++ i) {
			const mdl :: proof :: Node* upNode = step->getUp (i);
			const mdl :: proof :: Step* upStep = dynamic_cast<const mdl :: proof :: Step*>(upNode);
			if (upStep != NULL) {
				collectUsedSteps_step (upStep, used);
			}
		}
	}

	bool
	Steps :: findUnusedStep (bool used[], const index :: Step length, index :: Step& unused) const
	{
		for (index :: Step j = 0; j < length; ++ j) {
			const index :: Step i = length - j - 1;
			if (!used[i]) {
				unused = i;
				return true;
			}
		}
		return false;
	}
	void
	Steps :: removeUnusedStepFromProof (Proof_* proof, const index :: Step unused)
	{
		mdl :: proof :: Step* unusedStep = proof->stepVector_.getValue (unused);
		mdl :: proof :: Line* prevLine = unusedStep->getPrev();
		mdl :: proof :: Line* nextLine = unusedStep->getNext();
		if (prevLine != NULL) {
			prevLine->setNext (nextLine);
		}
		if (nextLine != NULL) {
			nextLine->setPrev (prevLine);
		}
		if (unusedStep == proof->firstLine_) {
			proof->firstLine_ = nextLine;
		}
		if (unusedStep == proof->lastLine_) {
			proof->lastLine_ = prevLine;
		}
		unusedStep->commitSuicide();
		proof->stepVector_.getReference (unused) = NULL;
		proof->stepVector_.remove (unused);
	}
	void
	Steps :: removeUnusedStepFromReferences (mdl :: Proof* proof, const index :: Step unused)
	{
		for (index :: Step i = 0; i < proof->getLength(); ++ i) {
			Step_* step = dynamic_cast<Step_*>(proof->getStep (i));
			if (step->getIndex() > unused) {
				-- step->index_;
			}
			mdl :: proof :: Link* link = step->getLink();
			References_* references = dynamic_cast<References_*>(link->getReferences());
			for (index :: Arity j = 0; j < references->getArity(); ++ j) {
				Reference_* reference = dynamic_cast<Reference_*>(references->get (j));
				if (reference->getKind() == Token :: STEP) {
					if (reference->getIndex() > unused) {
						-- reference->index_;
						if (reference->getNode() != NULL) {
							reference->build (step->getScope());
						}
					}
				}
			}
		}
	}
	void
	Steps :: removeUnusedStepFromQed (mdl :: Proof* proof, const index :: Step unused)
	{
		for (index :: Arity i = 0; i < proof->getQedArity(); ++ i) {
			Qed_* qed = dynamic_cast<Qed_*>(proof->getQed (i));
			const mdl :: proof :: Step* step = qed->getStep();
			qed->indexStep_ = step->getIndex();
		}
	}

	bool
	Steps :: findDuplicateSteps
	(
		const mdl :: Proof* proof,
		index :: Step& original,
		index :: Step& duplicate
	)
	{
		for (index :: Step i = 0; i < proof->getLength(); ++ i) {
			const array :: Expression*
				step_1 = proof->getStep (i)->getExpression();
			for (index :: Step j = i + 1; j < proof->getLength(); ++ j) {
				const array :: Expression*
					step_2 = proof->getStep (j)->getExpression();
				if (step_1->isEqual (step_2)) {
					original  = i;
					duplicate = j;
					return true;
				}
			}
		}
		return false;
	}
	void
	Steps :: removeDuplicateStepFromProof
	(
		Proof_* proof,
		const index :: Step duplicate
	)
	{
		mdl :: proof :: Step* duplicateStep = proof->stepVector_.getValue (duplicate);
		mdl :: proof :: Line* prevLine = duplicateStep->getPrev();
		mdl :: proof :: Line* nextLine = duplicateStep->getNext();
		if (prevLine != NULL) {
			prevLine->setNext (nextLine);
		}
		if (nextLine != NULL) {
			nextLine->setPrev (prevLine);
		}
		if (duplicateStep == proof->firstLine_) {
			proof->firstLine_ = nextLine;
		}
		if (duplicateStep == proof->lastLine_) {
			proof->lastLine_ = prevLine;
		}
		duplicateStep->commitSuicide();
		proof->stepVector_.getReference (duplicate) = NULL;
		proof->stepVector_.remove (duplicate);
	}
	void
	Steps :: removeDuplicateStepFromReferences
	(
		mdl :: Proof* proof,
		const index :: Step original,
		const index :: Step duplicate
	)
	{
		for (index :: Step i = 0; i < proof->getLength(); ++ i) {
			Step_* step = dynamic_cast<Step_*>(proof->getStep (i));
			if (step->getIndex() > duplicate) {
				-- step->index_;
			}
			mdl :: proof :: Link* link = step->getLink();
			References_* references = dynamic_cast<References_*>(link->getReferences());
			for (index :: Arity j = 0; j < references->getArity(); ++ j) {
				Reference_* reference = dynamic_cast<Reference_*>(references->get (j));
				if (reference->getKind() == Token :: STEP) {
					if (reference->getIndex() == duplicate) {
						reference->index_ = original;
						if (reference->getNode() != NULL) {
							reference->build (step->getScope());
						}
					}
					if (reference->getIndex() > duplicate) {
						-- reference->index_;
						if (reference->getNode() != NULL) {
							reference->build (step->getScope());
						}
					}
				}
			}
		}
	}
	void
	Steps :: removeDuplicateStepFromQed
	(
		mdl :: Proof* proof,
		const index :: Step original,
		const index :: Step duplicate
	)
	{
		for (index :: Arity i = 0; i < proof->getQedArity(); ++ i) {
			Qed_* qed = dynamic_cast<Qed_*>(proof->getQed (i));
			const mdl :: proof :: Step* step = qed->getStep();
			if (qed->getIndexStep() == duplicate) {
				qed->indexStep_ = original;
				qed->buildScope (qed->getScope());
			} else {
				qed->indexStep_ = step->getIndex();
			}
		}
	}
}
}
}

#endif /*MDL_REFACTOR_REDUNDANT_STEPS_CPP_*/
