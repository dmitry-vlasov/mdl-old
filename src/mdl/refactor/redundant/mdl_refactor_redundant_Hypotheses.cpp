/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_refactor_redundant_Hypptheses.hpp                    */
/* Description:     remove redundant hypotheses                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_REFACTOR_REDUNDANT_HYPOTHESES_CPP_
#define MDL_REFACTOR_REDUNDANT_HYPOTHESES_CPP_

namespace mdl {
namespace refactor {
namespace redundant {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Hypotheses :: Hypotheses (Format& format) :
	format_ (format, true),
	subFormat_ (format_, true)
	{
	}
	inline
	Hypotheses :: ~ Hypotheses () {
	}

using manipulator :: endLine;

	void
	Hypotheses :: refactor (mdl :: Source* source)
	{
		if (Config :: refactorId()->isEmpty()) {
			for (index :: Assertion i = 0; i < Math :: assertions()->getTheoremNumber(); ++ i) {
				mdl :: Assertion* assertion = Math :: assertions()->getTheorem (i);
				Theorem_* theorem = dynamic_cast<Theorem_*>(assertion);
				format_.message() << "refactoring ";
				theorem->replicateName (format_.message());
				format_.showStart();
				while (removeUnusedHypothesis (theorem) || removeDuplicateHypothesis (theorem));
				format_.showFinal();
			}
		} else {
			for (value :: Integer i = 0; i < Config :: refactorId()->getSize(); ++ i) {
				const String* idString = Config :: refactorId()->getValue (i);
				format_.message() << "refactoring " << *idString;
				format_.showStart();
				mdl :: Identificator* id = new form :: Identificator (*idString);
				index :: Assertion index = Math :: theories()->getRoot()->getIndex (id);
				id->commitSuicide();
				if (index == index :: undefined :: ASSERTION) {
					format_.message() << "failed: " << *idString << " is not found";
					format_.showFinal();
					continue;
				}
				mdl :: Assertion* assertion = Math :: assertions()->getForm (index);
				Theorem_* theorem = dynamic_cast<Theorem_*>(assertion);
				while (removeUnusedHypothesis (theorem) || removeDuplicateHypothesis (theorem));
				format_.showFinal();
			}
		}
	}

	bool
	Hypotheses :: removeUnusedHypothesis (mdl :: Theorem* theoremInterface)
	{
		Theorem_* theorem = dynamic_cast<Theorem_*>(theoremInterface);
		// Array which indicates, which hypotheses are used in proofs.
		const index :: Arity arity = theorem->getHypArity();
		bool used [arity];
		for (index :: Arity i = 0; i < arity; ++ i) {
			used [i] = false;
		}
		collectUsedHypotheses (theorem, used);
		index :: Arity unused = index :: undefined :: ARITY;
		if (findUnusedHypothesis (used, arity, unused)) {
			removeUnusedHypothesisFromTheorem (theorem, unused);
			removeUnusedHypothesisFromReferences (theorem, unused);
			removeHypothesisFromOtherTheorems (theorem, unused);
			return true;
		} else {
			return false;
		}
	}
	bool
	Hypotheses :: removeDuplicateHypothesis (mdl :: Theorem* theoremInterface)
	{
		Theorem_* theorem = dynamic_cast<Theorem_*>(theoremInterface);
		index :: Arity original = index :: undefined :: ARITY;
		index :: Arity duplicate = index :: undefined :: ARITY;
		if (findDuplicateHypotheses (theorem, original, duplicate)) {
			removeDuplicateHypothesisFromTheorem (theorem, duplicate);
			removeDuplicateHypothesisFromReferences (theorem, original, duplicate);
			removeHypothesisFromOtherTheorems (theorem, duplicate);
			return true;
		} else {
			return false;
		}
	}

	// object :: Object implementation
	void
	Hypotheses :: commitSuicide() {
		delete this;
	}
	Size_t
	Hypotheses :: getVolume() const
	{
		Size_t volume = 0;
		volume += format_.getVolume();
		volume += subFormat_.getVolume();
		return volume;
	}
	Size_t
	Hypotheses :: getSizeOf() const {
		return sizeof (Hypotheses);
	}
	void
	Hypotheses :: show (String& string) const
	{
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Hypotheses :: collectUsedHypotheses (const mdl :: Theorem* theorem, bool used[])
	{
		const vector :: Proof& proofVector = theorem->getProofVector();
		for (value :: Integer i = 0; i < proofVector.getSize(); ++ i) {
			const mdl :: Proof* proof = proofVector.getValue (i);
			collectUsedHypotheses (proof, used);
		}
	}
	void
	Hypotheses :: collectUsedHypotheses (const mdl :: Proof* proof, bool used[])
	{
		for (index :: Step i = 0; i < proof->getLength(); ++ i) {
			const mdl :: proof :: Step* step = proof->getStep (i);
			const mdl :: proof :: Link* link = step->getLink();
			const mdl :: proof :: References* references = link->getReferences();
			for (index :: Arity j = 0; j < references->getArity(); ++ j) {
				const mdl :: proof :: Reference* reference = references->get (j);
				if (reference->getKind() == Token :: HYP) {
					used [reference->getIndex()] = true;
				}
			}
		}
	}
	bool
	Hypotheses :: findUnusedHypothesis (bool used[], const index :: Arity arity, index :: Arity& unused) const
	{
		for (index :: Arity j = 0; j < arity; ++ j) {
			const index :: Arity i = arity - j - 1;
			if (!used[i]) {
				unused = i;
				return true;
			}
		}
		return false;
	}
	void
	Hypotheses :: removeUnusedHypothesisFromTheorem (Theorem_* theorem, const index :: Arity unused)
	{
		typedef
			form :: header :: statement :: Hypothesis
			Hypothesis;
		for (index :: Arity i = unused + 1; i < theorem->getHypArity(); ++ i) {
			Hypothesis* hyp = dynamic_cast<Hypothesis*>(theorem->hypothesisVector_.getValue (i));
			-- hyp->index_;
		}
		theorem->hypothesisVector_.getValue (unused)->commitSuicide();
		theorem->hypothesisVector_.getReference (unused) = NULL;
		theorem->hypothesisVector_.remove (unused);
	}
	void
	Hypotheses :: removeUnusedHypothesisFromReferences (Theorem_* theorem, const index :: Arity unused)
	{
		vector :: Proof& proofVector = theorem->getProofVector();
		for (value :: Integer i = 0; i < proofVector.getSize(); ++ i) {
			mdl :: Proof* proof = proofVector.getValue (i);
			removeUnusedHypothesisFromReferences (proof, unused);
		}
	}
	void
	Hypotheses :: removeUnusedHypothesisFromReferences (mdl :: Proof* proof, const index :: Arity unused)
	{
		for (index :: Step i = 0; i < proof->getLength(); ++ i) {
			mdl :: proof :: Step* step = proof->getStep (i);
			mdl :: proof :: Link* link = step->getLink();
			References_* references = dynamic_cast<References_*>(link->getReferences());
			for (index :: Arity j = 0; j < references->getArity(); ++ j) {
				Reference_* reference = dynamic_cast<Reference_*>(references->get (j));
				if (reference->getKind() == Token :: HYP) {
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

	bool
	Hypotheses :: findDuplicateHypotheses
	(
		const mdl :: Theorem* theorem,
		index :: Arity& original,
		index :: Arity& duplicate
	)
	{
		for (index :: Arity i = 0; i < theorem->getHypArity(); ++ i) {
			const array :: Expression*
				hypothesis_1 = theorem->getHypothesis (i)->getExpression();
			for (index :: Arity j = i + 1; j < theorem->getHypArity(); ++ j) {
				const array :: Expression*
					hypothesis_2 = theorem->getHypothesis (j)->getExpression();
				if (hypothesis_1->isEqual (hypothesis_2)) {
					original  = i;
					duplicate = j;
					return true;
				}
			}
		}
		return false;
	}
	void
	Hypotheses :: removeDuplicateHypothesisFromTheorem
	(
		Theorem_* theorem,
		const index :: Arity duplicate
	)
	{
		theorem->hypothesisVector_.getValue (duplicate)->commitSuicide();
		theorem->hypothesisVector_.getReference (duplicate) = NULL;
		theorem->hypothesisVector_.remove (duplicate);
	}
	void
	Hypotheses :: removeDuplicateHypothesisFromReferences
	(
		Theorem_* theorem,
		const index :: Arity original,
		const index :: Arity duplicate
	)
	{
		vector :: Proof& proofVector = theorem->getProofVector();
		for (value :: Integer i = 0; i < proofVector.getSize(); ++ i) {
			mdl :: Proof* proof = proofVector.getValue (i);
			removeDuplicateHypothesisFromReferences (proof, original, duplicate);
		}
	}
	void
	Hypotheses :: removeDuplicateHypothesisFromReferences
	(
		mdl :: Proof* proof,
		const index :: Arity original,
		const index :: Arity duplicate
	)
	{
		for (index :: Step i = 0; i < proof->getLength(); ++ i) {
			mdl :: proof :: Step* step = proof->getStep (i);
			mdl :: proof :: Link* link = step->getLink();
			References_* references = dynamic_cast<References_*>(link->getReferences());
			index :: Arity duplicateIndex = index :: undefined :: ARITY;
			for (index :: Arity j = 0; j < references->getArity(); ++ j) {
				Reference_* reference = dynamic_cast<Reference_*>(references->get (j));
				if (reference->getKind() == Token :: HYP) {
					if (reference->getIndex() == duplicate) {
						reference->index_ = original;
						duplicateIndex = j;
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
			references->build (step->getScope());
		}
	}

	void
	Hypotheses :: removeHypothesisFromOtherTheorems
	(
		const mdl :: Assertion* refactored,
		const index :: Arity redundant
	)
	{
		for (index :: Assertion i = 0; i < Math :: assertions()->getTheoremNumber(); ++ i) {
			mdl :: Assertion* assertion = Math :: assertions()->getTheorem (i);
			Theorem_* theorem = dynamic_cast<Theorem_*>(assertion);
			vector :: Proof& proofVector = theorem->getProofVector();
			for (value :: Integer i = 0; i < proofVector.getSize(); ++ i) {
				mdl :: Proof* proof = proofVector.getValue (i);
				removeHypothesisFromProof (proof, refactored, redundant);
			}
		}
	}
	void
	Hypotheses :: removeHypothesisFromProof
	(
		mdl :: Proof* proof,
		const mdl :: Assertion* assertion ,
		const index :: Arity redundantHypIndex
	)
	{
		for (index :: Step i = 0; i < proof->getLength(); ++ i) {
			mdl :: proof :: Step* step = proof->getStep (i);
			mdl :: proof :: Link* link = step->getLink();
			if (link->getAssertion() != assertion) {
				continue;
			}
			References_* references = dynamic_cast<References_*>(link->getReferences());
			mdl :: proof :: Reference*
				redundantReference = references->referenceVector_.getValue (redundantHypIndex);
			redundantReference->commitSuicide();
			references->referenceVector_.remove (redundantHypIndex);
			references->build (step->getScope());
		}
	}
}
}
}

#endif /*MDL_REFACTOR_REDUNDANT_HYPOTHESES_CPP_*/
