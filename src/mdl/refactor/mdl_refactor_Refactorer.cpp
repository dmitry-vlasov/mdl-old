/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_refactor_Refactorer.hpp                              */
/* Description:     class for the refactor                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_REFACTOR_REFACTORER_CPP_
#define MDL_REFACTOR_REFACTORER_CPP_

namespace mdl {
namespace refactor {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Refactorer :: Refactorer (Format& format) :
	format_ (format),
	subFormat_ (format_),
	redundantHypotheses_ (new redundant :: Hypotheses (format_)),
	redundantSteps_ (new redundant :: Steps (format_)),
	redundantVariables_ (new redundant :: Variables (format_)),
	duplicateHypothesis_ (0),
	unusedHypothesis_ (0),
	duplicateProofSteps_ (0),
	unusedProofSteps_ (0),
	unusedVariables_ (0)
	{
		if (refactor_ != NULL) {
			Error* error = new Error(Error :: SEMANTIC, "double instantiation of refactor");
			throw error;
		}
		refactor_ = this;
	}
	inline
	Refactorer :: ~ Refactorer ()
	{
		deleteAggregateObject (redundantHypotheses_);
		deleteAggregateObject (redundantSteps_);
		deleteAggregateObject (redundantVariables_);
	}

	void
	Refactorer :: refactor (mdl :: Source* source)
	{
		switch (Config :: getRefactoringJob()) {
		case Config :: RENAME :
			rename (source); break;
		case Config :: MOVE :
			move (source);   break;
		case Config :: REDUCE :
			reduce (source); break;
		case Config :: NO_REFACTORING :
		default : break; // do nothing
		}
		if (Config :: showRefactoring()) {
			showStatistics();
		}
	}

	void
	Refactorer  :: create (Format& format)
	{
		if (refactor_ == NULL) {
			refactor_ = new Refactorer (format);
		} else {
			clear();
		}
	}
	inline Refactorer*
	Refactorer  :: get() {
		return refactor_;
	}
	void
	Refactorer :: release()
	{
		if (refactor_ == NULL) {
			return;
		}
		refactor_->commitSuicide();
		refactor_ = NULL;
	}
	void
	Refactorer :: clear()
	{
		if (refactor_ == NULL) {
			return;
		}
		refactor_->duplicateHypothesis_ = 0;
		refactor_->unusedHypothesis_    = 0;
		refactor_->duplicateProofSteps_ = 0;
		refactor_->unusedProofSteps_    = 0;
		refactor_->unusedVariables_     = 0;
	}

using manipulator :: endLine;
using manipulator :: tab;

	// object :: Object implementation
	void
	Refactorer :: commitSuicide() {
		delete this;
	}
	Size_t
	Refactorer :: getVolume() const
	{
		Size_t volume = 0;
		volume += format_.getVolume();
		volume += subFormat_.getVolume();

		volume += getAggregateVolume (redundantHypotheses_);
		volume += getAggregateVolume (redundantSteps_);
		volume += getAggregateVolume (redundantVariables_);

		volume += getSizeOf();
		return volume;
	}
	Size_t
	Refactorer :: getSizeOf() const {
		return sizeof (Refactorer);
	}
	void
	Refactorer :: show (String& string) const
	{
		string << "Refactoring statistics:" << endLine;
		string << "=======================";
		string << "redundant hypotheses:" << endLine;
		string << tab << "duplicate: " << duplicateHypothesis_ << endLine;
		string << tab << "unused   : " << unusedHypothesis_ << endLine;
		string << "redundant proof steps:" << endLine;
		string << tab << "duplicate: " << duplicateProofSteps_ << endLine;
		string << tab << "unused   : " << unusedProofSteps_ << endLine;
		string << "redundant variables:" << endLine;
		string << tab << "unused   : " << unusedVariables_ << endLine;
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Refactorer :: totalStructureVerification() const
	{
		typedef form :: Theorem Theorem;
		for (index :: Assertion i = 0; i < Math :: assertions()->getTheoremNumber(); ++ i) {
			const mdl :: Assertion* assertion = Math :: assertions()->getTheorem (i);
			const Theorem* theorem = dynamic_cast<const Theorem*>(assertion);
			theorem->verifyStructure();
		}
	}

	void
	Refactorer :: rename (mdl :: Source* source)
	{

	}
	void
	Refactorer :: move (mdl :: Source* source)
	{

	}
	void
	Refactorer :: reduce (mdl :: Source* source)
	{
		format_.message() << "reducing";
		format_.showStart();
		if (Config :: refactorId()->isEmpty()) {
			for (index :: Assertion i = 0; i < Math :: assertions()->getTheoremNumber(); ++ i) {
				mdl :: Assertion* assertion = Math :: assertions()->getTheorem (i);
				mdl :: Theorem* theorem = dynamic_cast<mdl :: Theorem*>(assertion);
				subFormat_.message() << "refactoring ";
				theorem->replicateName (subFormat_.message());
				subFormat_.showStart();
				reduce (theorem);
				subFormat_.showFinal();
			}
		} else {
			for (value :: Integer i = 0; i < Config :: refactorId()->getSize(); ++ i) {
				const String* idString = Config :: refactorId()->getValue (i);
				subFormat_.message() << "refactoring " << *idString;
				subFormat_.showStart();
				mdl :: Identificator* id = new form :: Identificator (*idString);
				index :: Assertion index = Math :: theories()->getRoot()->getIndex (id);
				id->commitSuicide();
				if (index == index :: undefined :: ASSERTION) {
					subFormat_.message() << "failed: " << *idString << " is not found";
					subFormat_.showFinal();
					continue;
				}
				mdl :: Assertion* assertion = Math :: assertions()->getForm (index);
				mdl :: Theorem* theorem = dynamic_cast<mdl :: Theorem*>(assertion);
				reduce (theorem);
				subFormat_.showFinal();
			}
		}
	}

	void
	Refactorer :: reduce (mdl :: Theorem* theorem)
	{
		if (Config  :: removeRedundantProofSteps()) {
			while (redundantSteps_->removeDuplicateSteps (theorem)) {
				++ duplicateProofSteps_;
			}
			while (redundantSteps_->removeUnusedSteps (theorem)) {
				++ unusedProofSteps_;
			}
		}
		if (Config  :: removeRedundantHypothesis()) {
			while (redundantHypotheses_->removeDuplicateHypothesis (theorem)) {
				++ duplicateHypothesis_;
			}
			while (redundantHypotheses_->removeUnusedHypothesis (theorem)) {
				++ unusedHypothesis_;
			}
		}
		bool reducing = true;
		while (reducing) {
			reducing = false;
			if (Config  :: removeRedundantHypothesis() &&
				redundantHypotheses_->removeUnusedHypothesis (theorem)) {
				reducing = true;
				++ unusedHypothesis_;
			}
			if (Config  :: removeRedundantHypothesis() &&
				redundantHypotheses_->removeDuplicateHypothesis (theorem)) {
				reducing = true;
				++ duplicateHypothesis_;
			}
			if (Config  :: removeRedundantProofSteps() &&
				redundantSteps_->removeUnusedSteps (theorem)) {
				reducing = true;
				++ unusedProofSteps_;
			}
			if (Config  :: removeRedundantProofSteps() &&
				redundantSteps_->removeDuplicateSteps (theorem)) {
				++ duplicateProofSteps_;
				reducing = true;
			}
		}

		// Final step: if there are redundant hypothesis, some variables may
		// occur unused. We need to remove them to get correct translation to smm.
		//
		if (Config  :: removeRedundantHypothesis() ||
			Config  :: removeRedundantVariables()) {
			unusedVariables_ += redundantVariables_->removeUnusedVariables (theorem);
		}
		#ifdef DEBUG_REFACTORING
		totalStructureVerification();
		#endif
	}

	void
	Refactorer :: showStatistics()
	{
		format_.message() << "Refactoring statistics:";
		format_.showMessage();
		format_.message() << "=======================";
		format_.showMessage();
		format_.message() << "hypotheses:";
		format_.showMessage();
		format_.message() << tab << "duplicate: " << duplicateHypothesis_;
		format_.showMessage();
		format_.message() << tab << "unused   : " << unusedHypothesis_;
		format_.showMessage();
		format_.message() << "proof steps:";
		format_.showMessage();
		format_.message() << tab << "duplicate: " << duplicateProofSteps_;
		format_.showMessage();
		format_.message() << tab << "unused   : " << unusedProofSteps_;
		format_.showMessage();
		format_.message() << "redundant variables:";
		format_.showMessage();
		format_.message() << tab << "unused   : " << unusedVariables_;
		format_.showMessage();
	}

	/********************************
	 *		Static private members
	 ********************************/

	Refactorer* Refactorer :: refactor_ = NULL;
}
}

#endif /*MDL_REFACTOR_REFACTORER_CPP_*/
