/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_Refactor.cpp                        */
/* Description:     refactoring options                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace auxiliary {
namespace config {

	/****************************
	 *		Public members
	 ****************************/

	Refactor :: RefactoringJob_
	Refactor :: getRefactoringJob()
	{
		if (rename()) {
			return RENAME;
		} else if (move()) {
			return MOVE;
		} else if (removeRedundantHypothesis()) {
			return REDUCE;
		} else if (removeRedundantProofSteps()) {
			return REDUCE;
		} else if (removeRedundantVariables()) {
			return REDUCE;
		} else if (removeRedundantAssertions()) {
			return REDUCE;
		} else {
			return DEFAULT_REFACTORING_JOB;
		}
	}

	inline bool
	Refactor :: rename() {
		return refactoringOptions_ [OPTION_RENAME]->getValue();
	}
	inline bool
	Refactor :: move() {
		return refactoringOptions_ [OPTION_MOVE]->getValue();
	}
	inline bool
	Refactor :: removeRedundantHypothesis() {
		return refactoringOptions_ [OPTION_REMOVE_REDUNDANT_HYPOTHESIS]->getValue();
	}
	inline bool
	Refactor :: removeRedundantProofSteps() {
		return refactoringOptions_ [OPTION_REMOVE_REDUNDANT_PROOF_STEPS]->getValue();
	}
	inline bool
	Refactor :: removeRedundantVariables() {
		return refactoringOptions_ [OPTION_REMOVE_REDUNDANT_VARIABLES]->getValue();
	}
	inline bool
	Refactor :: removeRedundantAssertions() {
		return refactoringOptions_ [OPTION_REMOVE_REDUNDANT_ASSERTIONS]->getValue();
	}

	inline bool
	Refactor :: deepRefactoring() {
		return refactoringOptions_ [OPTION_DEEP_REFACTORING]->getValue();
	}
	inline bool
	Refactor :: checkBeforeRefactoring() {
		return refactoringOptions_ [OPTION_CHECK_BEFORE_REFACTORING]->getValue();
	}

	inline vector :: String*
	Refactor :: refactorFrom() {
		return from_;
	}
	inline vector :: String*
	Refactor :: refactorTo() {
		return to_;
	}
	inline vector :: String*
	Refactor :: refactorId() {
		return id_;
	}

	template<class S>
	void
	Refactor :: showUsageMessage (S& os, const List& groupList)
	{
		if (groupList.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int j = 0; j < REFACTORING_OPTIONS_NUM; ++ j) {
				refactoringOptions_[j]->showUsageMessage (os);
			}
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	void
	Refactor :: showOptionValues (S& os, const List& groupList)
	{
		if (groupList.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int j = 0; j < REFACTORING_OPTIONS_NUM; ++ j) {
				refactoringOptions_[j]->showOptionValues (os);
			}
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	inline void
	Refactor :: showGroupName (S& os) {
		os << "\t" << optionGroupName_ << chars :: NEW_LINE;
	}

	/****************************
	 *		Protected members
	 ****************************/

	bool
	Refactor :: proceedStringOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		for (int j = 0; j < REFACTORING_OPTIONS_NUM; ++ j) {
			if (refactoringOptions_[j]->proceedStringOption (opt, argCount, argValues, i)) {
				switch (j) {
				case OPTION_REMOVE_REDUNDANT_ALL :
					refactoringOptions_ [OPTION_REMOVE_REDUNDANT_HYPOTHESIS]->value() = true;
					refactoringOptions_ [OPTION_REMOVE_REDUNDANT_PROOF_STEPS]->value() = true;
					refactoringOptions_ [OPTION_REMOVE_REDUNDANT_VARIABLES]->value() = true;
					refactoringOptions_ [OPTION_REMOVE_REDUNDANT_ASSERTIONS]->value() = true;
					break;
				case OPTION_FROM :
					from_->clear();
					from_->add (new mdl :: String (argValues [++ i]));
					break;
				case OPTION_FROM_BEGIN :
					proceedStringGroup
					(
						argCount, argValues, i,
						from_,
						refactoringOptions_[OPTION_FROM_BEGIN],
						refactoringOptions_[OPTION_FROM_END]
					);
					break;
				case OPTION_TO :
					to_->clear();
					to_->add (new mdl :: String (argValues [++ i]));
					break;
				case OPTION_TO_BEGIN :
					proceedStringGroup
					(
						argCount, argValues, i,
						to_,
						refactoringOptions_[OPTION_TO_BEGIN],
						refactoringOptions_[OPTION_TO_END]
					);
					break;
				case OPTION_ID :
					id_->clear();
					id_->add (new mdl :: String (argValues [++ i]));
					break;
				case OPTION_ID_BEGIN :
					proceedStringGroup
					(
						argCount, argValues, i,
						id_,
						refactoringOptions_[OPTION_ID_BEGIN],
						refactoringOptions_[OPTION_ID_END]
					);
					break;
				default : break;
				}
				return true;
			}
		}
		return false;
	}
	bool
	Refactor :: proceedOneCharOption (const char* opt, const int argCount, const char* argValues[], int& i) {
		return false;
	}

	bool
	Refactor :: isCorrect()
	{
		for (int j = 0; j < REFACTORING_OPTIONS_NUM; ++ j) {
			if (!refactoringOptions_[j]->isCorrect()) {
				return false;
			}
		}
		return true;
	}

	inline bool
	Refactor :: isConsistent()
	{
		if (!isConsistent_) {
			isConsistent_ = true;
			return false;
		}
		bool someIsChecked = false;
		for (int i = 0; i < REFACTORING_OPTIONS_NUM; ++ i) {
			if (refactoringOptions_ [i]->getValue()) {
				if (!someIsChecked) {
					someIsChecked = true;
				} else {
					std :: cout << "two different refactoring jobs are chosen." << std :: endl;
					return false;
				}
			}
		}
		return true;
	}

	inline void
	Refactor :: init ()
	{
		refactoringOptions_[OPTION_RENAME] = new option :: Bool (false, "rename",  "rename identificator(s).");
		refactoringOptions_[OPTION_MOVE]   = new option :: Bool (false, "move",    "move identificator(s) from one theory to another.");

		refactoringOptions_[OPTION_REMOVE_REDUNDANT_ALL] =
			new option :: Bool (false, "remove-redundancy",            "get rid of all redundancy.");
		refactoringOptions_[OPTION_REMOVE_REDUNDANT_HYPOTHESIS] =
			new option :: Bool (false, "remove-redundant-hypotheses",  "self explanatory.");
		refactoringOptions_[OPTION_REMOVE_REDUNDANT_PROOF_STEPS] =
			new option :: Bool (false, "remove-redundant-proof-steps", "self explanatory.");
		refactoringOptions_[OPTION_REMOVE_REDUNDANT_VARIABLES] =
			new option :: Bool (false, "remove-redundant-variables",   "self explanatory.");
		refactoringOptions_[OPTION_REMOVE_REDUNDANT_ASSERTIONS] =
			new option :: Bool (false, "remove-redundant-assertions",  "self explanatory.");

		refactoringOptions_[OPTION_FROM]       = new option :: Bool (false, "from",  "defines a unique 'from' identificator.");
		refactoringOptions_[OPTION_FROM_BEGIN] = new option :: Bool (false, "from[", "starts a group of 'from' identificators.");
		refactoringOptions_[OPTION_FROM_END]   = new option :: Bool (false, "from]", "ends a group of 'from' identificators.");

		refactoringOptions_[OPTION_TO]         = new option :: Bool (false, "to",    "defines a unique 'to' identificator.");
		refactoringOptions_[OPTION_TO_BEGIN]   = new option :: Bool (false, "to[",   "starts a group of 'to' identificators.");
		refactoringOptions_[OPTION_TO_END]     = new option :: Bool (false, "to]",   "ends a group of 'to' identificators.");

		refactoringOptions_[OPTION_ID]         = new option :: Bool (false, "id",   "defines a unique identificator.");
		refactoringOptions_[OPTION_ID_BEGIN]   = new option :: Bool (false, "id[",   "starts a group of identificators.");
		refactoringOptions_[OPTION_ID_END]     = new option :: Bool (false, "id]",   "ends a group of identificators.");

		refactoringOptions_[OPTION_DEEP_REFACTORING] = new option :: Bool (true, "deep-refactoring", "refactor all included files.");
		refactoringOptions_[OPTION_CHECK_BEFORE_REFACTORING] = new option :: Bool (true, "check-before-refactoring", "should be set to 'false' in case, when not correct source is being refactored.");

		from_ = new vector :: String (INITIAL_STRING_VECTOR_CAPACITY);
		to_   = new vector :: String (INITIAL_STRING_VECTOR_CAPACITY);
		id_   = new vector :: String (INITIAL_STRING_VECTOR_CAPACITY);
	}
	inline void
	Refactor :: release()
	{
		for (int i = 0; i < REFACTORING_OPTIONS_NUM; ++ i) {
			delete refactoringOptions_ [i];
			refactoringOptions_ [i] = NULL;
		}
		delete from_;
		from_ = NULL;
		delete to_;
		to_   = NULL;
		delete id_;
		id_ = NULL;
	}
	inline Size_t
	Refactor :: getVolume()
	{
		Size_t volume = 0;
		for (int i = 0; i < REFACTORING_OPTIONS_NUM; ++ i) {
			volume += object :: Object :: getAggregateVolume (refactoringOptions_ [i]);
		}
		volume += object :: Object :: getAggregateVolume (from_);
		volume += object :: Object :: getAggregateVolume (to_);
		volume += object :: Object :: getAggregateVolume (id_);
		return volume;
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Refactor :: proceedStringGroup
	(
		const int argCount,
		const char* argValues[],
		int& i,
		vector :: String* stringVector,
		const option :: Bool* groupBegin,
		const option :: Bool* groupEnd
	)
	{
		stringVector->clear();
		while (++ i < argCount) {
			const char* option = argValues [i];
			if (*option == '-') {
				++ option;
			}
			if (*option == '-') {
				++ option;
			}
			if (Config :: equalStrings (groupEnd->getString(), option)) {
				break;
			} else {
				stringVector->add (new mdl :: String (argValues [i]));
			}
		}
		if (i == argCount) {
			isConsistent_ = false;
			std :: cout << "incorrect option format: ";
			std :: cout << "\"" << groupBegin->getString() << "\" must be followed by";
			std :: cout << "\"" << groupEnd->getString() << "\"" << std :: endl;
		}
	}

	/*************************************
	 *		Private static attributes
	 *************************************/

	option :: Bool*   Refactor :: refactoringOptions_  [REFACTORING_OPTIONS_NUM];
	vector :: String* Refactor :: from_ = NULL;
	vector :: String* Refactor :: to_   = NULL;
	vector :: String* Refactor :: id_   = NULL;
	bool Refactor :: isConsistent_ = true;
	const char* Refactor :: optionGroupName_ = "refactoring";
}
}
}


