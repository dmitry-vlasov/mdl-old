/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_Mode.cpp                            */
/* Description:     static class for mdl run mode                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_CONFIG_MODE_CPP_
#define MDL_AUXILIARY_CONFIG_MODE_CPP_

namespace mdl {
namespace auxiliary {
namespace config {

	/****************************
	 *		Public members
	 ****************************/

	inline bool
	Mode :: interactive() {
		return interactiveOption_->getValue();
	}

	// run mode flags
	inline bool
	Mode :: runOnefold() {
		return runOptions_ [RUN_ONEFOLD]->getValue();
	}
	inline bool
	Mode :: runServer() {
		return runOptions_ [RUN_SERVER]->getValue();
	}
	inline bool
	Mode :: runConsole() {
		return runOptions_ [RUN_CONSOLE]->getValue();
	}

	// work mode flags
	inline bool
	Mode :: check() {
		return modeOptions_ [CHECK]->getValue();
	}
	inline bool
	Mode :: translate() {
		return modeOptions_ [TRANSLATE]->getValue();
	}
	inline bool
	Mode :: prove() {
		return modeOptions_ [PROVE]->getValue();
	}
	inline bool
	Mode :: compress() {
		return modeOptions_ [COMPRESS]->getValue();
	}
	inline bool
	Mode :: reprove() {
		return modeOptions_ [REPROVE]->getValue();
	}
	inline bool
	Mode :: learn() {
		return modeOptions_ [LEARN]->getValue();
	}
	inline bool
	Mode :: tune() {
		return modeOptions_ [TUNE]->getValue();
	}
	inline bool
	Mode :: benchmark() {
		return modeOptions_ [BENCHMARK]->getValue();
	}
	inline bool
	Mode :: refactor() {
		return modeOptions_ [REFACTOR]->getValue();
	}

	inline value :: Name
	Mode :: experience()
	{
		if (names_ [EXPERIENCE_NAME] == value :: undefined :: NAME) {
			const nstd :: String<>&
				string = nameOptions_[EXPERIENCE_NAME]->value();
			names_ [EXPERIENCE_NAME] = Table :: names()->add (string);
		}
		return names_ [EXPERIENCE_NAME];
	}
	inline value :: Name
	Mode :: excludeAssertion()
	{
		if (names_ [EXCLUDED_ASSERTION_NAME] == value :: undefined :: NAME) {
			const nstd :: String<>&
				string = nameOptions_[EXCLUDED_ASSERTION_NAME]->value();
			names_ [EXCLUDED_ASSERTION_NAME] = Table :: names()->add (string);
		}
		return names_ [EXCLUDED_ASSERTION_NAME];
	}
	inline value :: Name
	Mode :: compressAssertion()
	{
		if (names_ [COMPRESS_ASSERTION_NAME] == value :: undefined :: NAME) {
			const nstd :: String<>&
				string = nameOptions_[COMPRESS_ASSERTION_NAME]->value();
			names_ [COMPRESS_ASSERTION_NAME] = Table :: names()->add (string);
		}
		return names_ [COMPRESS_ASSERTION_NAME];
	}
	inline value :: Name
	Mode :: refinedRule()
	{
		if (names_ [REFINED_RULE_NAME] == value :: undefined :: NAME) {
			const nstd :: String<>&
				string = nameOptions_[REFINED_RULE_NAME]->value();
			names_ [REFINED_RULE_NAME] = Table :: names()->add (string);
		}
		return names_ [REFINED_RULE_NAME];
	}
	inline value :: Name
	Mode :: refinedType()
	{
		if (names_ [REFINED_TYPE_NAME] == value :: undefined :: NAME) {
			const nstd :: String<>&
				string = nameOptions_[REFINED_TYPE_NAME]->value();
			names_ [REFINED_TYPE_NAME] = Table :: names()->add (string);
		}
		return names_ [REFINED_TYPE_NAME];
	}

	inline value :: Integer
	Mode :: getCompressionFactor() {
		return compressionFactor_->getValue();
	}

	template<class S>
	void
	Mode :: showUsageMessage (S& os, const List& groupList)
	{
		if (groupList.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int j = 0; j < RUN_NUM; ++ j) {
				runOptions_[j]->showUsageMessage (os);
			}
			interactiveOption_->showUsageMessage (os);
			os << chars :: NEW_LINE;
			modeOptions_[CHECK]->showUsageMessage (os);
			modeOptions_[TRANSLATE]->showUsageMessage (os);
			modeOptions_[PROVE]->showUsageMessage (os);
			modeOptions_[COMPRESS]->showUsageMessage (os);
			compressionFactor_->showUsageMessage (os);
			modeOptions_[REPROVE]->showUsageMessage (os);
			modeOptions_[LEARN]->showUsageMessage (os);
			modeOptions_[TUNE]->showUsageMessage (os);
			modeOptions_[BENCHMARK]->showUsageMessage (os);
			modeOptions_[REFACTOR]->showUsageMessage (os);
			for (int j = 0; j < NAME_NUM; ++ j) {
				nameOptions_[j]->showUsageMessage (os);
			}
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	void
	Mode :: showOptionValues (S& os, const List& groupList)
	{
		if (groupList.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int j = 0; j < RUN_NUM; ++ j) {
				runOptions_[j]->showOptionValues (os);
			}
			interactiveOption_->showOptionValues (os);
			os << chars :: NEW_LINE;
			modeOptions_[CHECK]->showOptionValues (os);
			modeOptions_[TRANSLATE]->showOptionValues (os);
			modeOptions_[PROVE]->showOptionValues (os);
			modeOptions_[COMPRESS]->showOptionValues (os);
			compressionFactor_->showOptionValues (os);
			modeOptions_[REPROVE]->showOptionValues (os);
			modeOptions_[LEARN]->showOptionValues (os);
			modeOptions_[TUNE]->showOptionValues (os);
			modeOptions_[BENCHMARK]->showOptionValues (os);
			modeOptions_[REFACTOR]->showOptionValues (os);
			for (int j = 0; j < NAME_NUM; ++ j) {
				nameOptions_[j]->showOptionValues (os);
			}
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	inline void
	Mode :: showGroupName (S& os) {
		os << "\t" << optionGroupName_ << chars :: NEW_LINE;
	}

	/****************************
	 *		Protected members
	 ****************************/

	bool
	Mode :: proceedStringOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		if (!someRunIsChosen()) {
			for (int j = 0; j < RUN_NUM; ++ j) {
				if (runOptions_[j]->proceedStringOption (opt, argCount, argValues, i)) {
					return true;
				}
			}
		}
		for (int j = 0; j < MODE_NUM; ++ j) {
			if (modeOptions_[j]->proceedStringOption (opt, argCount, argValues, i)) {
				return true;
			}
		}
		for (int j = 0; j < NAME_NUM; ++ j) {
			if (nameOptions_[j]->proceedStringOption (opt, argCount, argValues, i)) {
				return true;
			}
		}
		if (compressionFactor_->proceedStringOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (interactiveOption_->proceedStringOption (opt, argCount, argValues, i)) {
			return true;
		}
		return false;
	}
	bool
	Mode :: proceedOneCharOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		if (!someRunIsChosen()) {
			for (int j = 0; j < RUN_NUM; ++ j) {
				if (runOptions_[j]->proceedOneCharOption (opt, argCount, argValues, i)) {
					return true;
				}
			}
		}
		for (int j = 0; j < MODE_NUM; ++ j) {
			if (modeOptions_[j]->proceedOneCharOption (opt, argCount, argValues, i)) {
				return true;
			}
		}
		for (int j = 0; j < NAME_NUM; ++ j) {
			if (nameOptions_[j]->proceedOneCharOption (opt, argCount, argValues, i)) {
				return true;
			}
		}
		if (interactiveOption_->proceedOneCharOption (opt, argCount, argValues, i)) {
			return true;
		}
		return false;
	}

	bool
	Mode :: isCorrect()
	{
		for (int j = 0; j < RUN_NUM; ++ j) {
			if (!runOptions_[j]->isCorrect()) {
				return false;
			}
		}
		for (int j = 0; j < MODE_NUM; ++ j) {
			if (!modeOptions_[j]->isCorrect()) {
				return false;
			}
		}
		for (int j = 0; j < NAME_NUM; ++ j) {
			if (!nameOptions_[j]->isCorrect()) {
				return false;
			}
		}
		if (!interactiveOption_->isCorrect()) {
			return false;
		}
		return true;
	}

	inline bool
	Mode :: isConsistent()
	{
		bool someIsChecked = false;
		for (int i = 0; i < RUN_NUM; ++ i) {
			if (runOptions_ [i]->getValue()) {
				if (!someIsChecked) {
					someIsChecked = true;
				} else {
					std :: cout << "two different run modes are chosen." << std :: endl;
					return false;
				}
			}
		}
		if (runOptions_[RUN_SERVER]->getValue() ||
			runOptions_[RUN_CONSOLE]->getValue()) {
			Config :: setUpdate (true);
			Config :: setInExternalConfig (true);
		}
		// Set up the default run mode
		if (!someRunIsChosen() && !Config :: getUpdate()) {
			runOptions_[DEFAULT_RUN]->value() = true;
		}
		if (runOptions_[RUN_ONEFOLD]->getValue() && interactiveOption_->getValue()) {
			return false;
		}
		someIsChecked = false;
		for (int i = 0; i < MODE_NUM; ++ i) {
			if (modeOptions_ [i]->getValue()) {
				if (!someIsChecked) {
					someIsChecked = true;
				} else {
					std :: cout << "two different actions are chosen." << std :: endl;
					return false;
				}
			}
		}
		return true;
	}
	bool
	Mode :: someRunIsChosen()
	{
		for (int i = 0; i < RUN_NUM; ++ i) {
			if (runOptions_ [i]->getValue()) {
				return true;
			}
		}
		return false;
	}
	bool
	Mode :: someModeIsChosen()
	{
		for (int i = 0; i < MODE_NUM; ++ i) {
			if (modeOptions_ [i]->getValue()) {
				return true;
			}
		}
		return false;
	}

	inline void
	Mode :: init ()
	{
		runOptions_[RUN_ONEFOLD]     = new option :: Bool (false, "one-fold",  "run mdl once for a single job.");
		runOptions_[RUN_SERVER]      = new option :: Bool (false, "server",    "run mdl as server.", 's');
		runOptions_[RUN_CONSOLE]     = new option :: Bool (false, "console",   "run mdl as server.", 'c');

		modeOptions_[CHECK]       = new option :: Bool (false, "check",     "check the specified file.");
		modeOptions_[TRANSLATE]   = new option :: Bool (false, "translate", "translate the specified file to smm.", 't');
		modeOptions_[PROVE]       = new option :: Bool (false, "prove",     "prove to the specified file.", 'p');
		modeOptions_[COMPRESS]    = new option :: Bool (false, "compress",  "compress all proofs.");
		modeOptions_[REPROVE]     = new option :: Bool (false, "reprove",   "reprove all proofs.");
		modeOptions_[LEARN]       = new option :: Bool (false, "learn",     "let the prover to learn form the source.");
		modeOptions_[TUNE]        = new option :: Bool (false, "tune",      "tune the learning gear of the prover.");
		modeOptions_[BENCHMARK]   = new option :: Bool (false, "benchmark", "benchmark the tuning gear.");
		modeOptions_[REFACTOR]    = new option :: Bool (false, "refactor",  "refactor source.");

		nameOptions_[EXPERIENCE_NAME] = new option :: String ("_default_Name_", "experience", "let the prover use <string> experience for learning/proving.");
		nameOptions_[EXCLUDED_ASSERTION_NAME] =
			new option :: String ("_default_Name_", "exclude-assertion", "exclude the assertion from learning/proving.");
		nameOptions_[COMPRESS_ASSERTION_NAME] =
			new option :: String ("_default_Name_", "compress-assertion", "compress the exact assertion proof(s).");
		nameOptions_[REFINED_RULE_NAME] =
			new option :: String ("_default_Name_", "refined-rule", "rule to be refined.");
		nameOptions_[REFINED_TYPE_NAME] =
			new option :: String ("_default_Name_", "refined-type", "type to be refined.");
		compressionFactor_ = new option :: Integer (DEFAULT_COMPRESSION_FACTOR, "compress-one-of", "compress the proof for one of <int> theorems.");
		interactiveOption_ = new option :: Bool (false, "interactive",  "run mdl server/console in an interactive mode.");
		for (value :: Integer i = 0; i < NAME_NUM; ++ i) {
			names_ [i] = value :: undefined :: NAME;
		}
	}
	inline void
	Mode :: release()
	{
		for (int i = 0; i < RUN_NUM; ++ i) {
			delete runOptions_ [i];
			runOptions_ [i] = NULL;
		}
		for (int i = 0; i < MODE_NUM; ++ i) {
			delete modeOptions_ [i];
			modeOptions_ [i] = NULL;
		}
		for (int i = 0; i < NAME_NUM; ++ i) {
			delete nameOptions_ [i];
			nameOptions_ [i] = NULL;
		}
		if (compressionFactor_ != NULL) {
			delete compressionFactor_;
			compressionFactor_ = NULL;
		}
		if (interactiveOption_ != NULL) {
			delete interactiveOption_;
			interactiveOption_ = NULL;
		}
	}
	inline Size_t
	Mode :: getVolume()
	{
		Size_t volume = 0;
		for (int i = 0; i < RUN_NUM; ++ i) {
			volume += object :: Object :: getAggregateVolume (runOptions_ [i]);
		}
		for (int i = 0; i < MODE_NUM; ++ i) {
			volume += object :: Object :: getAggregateVolume (modeOptions_ [i]);
		}
		for (int i = 0; i < NAME_NUM; ++ i) {
			volume += object :: Object :: getAggregateVolume (nameOptions_ [i]);
		}
		if (compressionFactor_ != NULL) {
			volume += object :: Object :: getAggregateVolume (compressionFactor_);
		}
		if (interactiveOption_ != NULL) {
			volume += object :: Object :: getAggregateVolume (interactiveOption_);
		}
		return volume;
	}

	/*************************************
	 *		Private static attributes
	 *************************************/

	option :: Bool*    Mode :: runOptions_  [RUN_NUM];
	option :: Bool*    Mode :: modeOptions_ [MODE_NUM];
	option :: String*  Mode :: nameOptions_ [NAME_NUM];
	option :: Integer* Mode :: compressionFactor_ = NULL;
	option :: Bool*    Mode :: interactiveOption_ = NULL;

	value :: Name Mode :: names_ [NAME_NUM];

	const char* Mode :: optionGroupName_ = "mode";
}
}
}

#endif /*MDL_AUXILIARY_CONFIG_MODE_CPP_*/
