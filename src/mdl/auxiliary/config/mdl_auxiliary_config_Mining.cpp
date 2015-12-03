/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_Mining.cpp                          */
/* Description:     Mining :: class for mdl source mining                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_CONFIG_MINING_CPP_
#define MDL_AUXILIARY_CONFIG_MINING_CPP_

namespace mdl {
namespace auxiliary {
namespace config {

	/****************************
	 *		Public members
	 ****************************/

	// lookup position
	inline bool
	Mining :: lookupDefinition() {
		return lookupOptions_[LOOKUP_DEFINITION]->getValue();
	}
	inline bool
	Mining :: lookupLocation() {
		return lookupOptions_[LOOKUP_LOCATION]->getValue();
	}
	inline bool
	Mining :: lookup() {
		return (lookupDefinition() || lookupLocation());
	}

	// mining options
	inline container :: Bit
	Mining :: getMiningOptions() {
		return miningOptions_;
	}
	inline Mining :: MiningMode_
	Mining :: getMiningMode() {
		return miningMode_;
	}
	inline bool
	Mining :: mine() {
		return (miningMode_ != MINE_NOTHING);
	}

	// parse only definitions
	inline bool
	Mining :: shallowParsing() {
		return (mine() || lookup());
	}
	// parse only current file
	inline bool
	Mining :: localParsing() {
		return (miningMode_ == MINE_OUTLINE);
	}

	template<class S>
	void
	Mining :: showUsageMessage (S& os, const List& groupList)
	{
		if (groupList.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int i = 0; i < LOOKUP_OPTIONS_NUM; ++ i) {
				lookupOptions_ [i]->showUsageMessage (os);
			}
			os << chars :: NEW_LINE;
			for (int i = 0; i < MINE_MODE_NUM; ++ i) {
				mineModes_ [i]->showUsageMessage (os);
			}
			os << chars :: NEW_LINE;
			for (int i = 0; i < MINE_OPTIONS_NUM; ++ i) {
				mineOptions_ [i]->showUsageMessage (os);
			}
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	void
	Mining :: showOptionValues (S& os, const List& groupList)
	{
		if (groupList.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int i = 0; i < LOOKUP_OPTIONS_NUM; ++ i) {
				lookupOptions_ [i]->showOptionValues (os);
			}
			os << chars :: NEW_LINE;
			for (int i = 0; i < MINE_MODE_NUM; ++ i) {
				mineModes_ [i]->showOptionValues (os);
			}
			os << chars :: NEW_LINE;
			for (int i = 0; i < MINE_OPTIONS_NUM; ++ i) {
				mineOptions_ [i]->showOptionValues (os);
			}
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	inline void
	Mining :: showGroupName (S& os) {
		os << "\t" << optionGroupName_ << chars :: NEW_LINE;
	}

	/****************************
	 *		Protected members
	 ****************************/

	bool
	Mining :: proceedStringOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		for (int j = 0; j < LOOKUP_OPTIONS_NUM; ++ j) {
			if (lookupOptions_[j]->proceedStringOption (opt, argCount, argValues, i)) {
				return true;
			}
		}
		for (int j = 0; j < MINE_MODE_NUM; ++ j) {
			if (mineModes_[j]->proceedStringOption (opt, argCount, argValues, i)) {
				miningMode_ = static_cast<MiningMode_>(j);
				return true;
			}
		}
		for (int j = 0; j < MINE_OPTIONS_NUM; ++ j) {
			if (mineOptions_[j]->proceedStringOption (opt, argCount, argValues, i)) {
				miningOptions_.setValue (j);
				if (mineOptions_ [MINE_ALL]->getValue()) {
					for (int k = 0; k < MINE_OPTIONS_NUM; ++ k) {
						mineOptions_ [k]->value() = true;
						miningOptions_.setValue (k);
					}
				}
				return true;
			}
		}
		return false;
	}
	bool
	Mining :: proceedOneCharOption (const char* opt, const int argCount, const char* argValues[], int& i) {
		return false;
	}

	bool
	Mining :: isCorrect()
	{
		for (int i = 0; i < LOOKUP_OPTIONS_NUM; ++ i) {
			if (!lookupOptions_ [i]->isCorrect()) {
				return false;
			}
		}
		for (int i = 0; i < MINE_MODE_NUM; ++ i) {
			if (!mineModes_ [i]->isCorrect()) {
				return false;
			}
		}
		for (int i = 0; i < MINE_OPTIONS_NUM; ++ i) {
			if (!mineOptions_ [i]->isCorrect()) {
				return false;
			}
		}
		return true;
	}

	inline bool
	Mining :: isConsistent()
	{
		bool someIsChecked = false;
		for (int i = 0; i < LOOKUP_OPTIONS_NUM; ++ i) {
			if (lookupOptions_ [i]->getValue()) {
				if (!someIsChecked) {
					someIsChecked = true;
				} else {
					std :: cout << "two different actions are chosen." << std :: endl;
					return false;
				}
			}
		}
		for (int i = 0; i < MINE_MODE_NUM; ++ i) {
			if (mineModes_ [i]->getValue()) {
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
	inline bool
	Mining :: someActionIsChosen()
	{
		for (int i = 0; i < LOOKUP_OPTIONS_NUM; ++ i) {
			if (lookupOptions_ [i]->getValue()) {
				return true;
			}
		}
		for (int i = 0; i < MINE_MODE_NUM; ++ i) {
			if (mineModes_ [i]->getValue()) {
				return true;
			}
		}
		return false;
	}

	inline void
	Mining :: init ()
	{
		lookupOptions_ [LOOKUP_DEFINITION] = new option :: Bool (false, "lookup-definition", "find the definition of an object and put in into std :: cout.");
		lookupOptions_ [LOOKUP_LOCATION]   = new option :: Bool (false, "lookup-location",   "find the location of an object and put in into std :: cout.");

		mineModes_ [MINE_OUTLINE]     = new option :: Bool (false, "mine-outline",     "mine outline and put as XML in into std :: cout.");
		mineModes_ [MINE_TYPE_SYSTEM] = new option :: Bool (false, "mine-type-system", "mine type system and put as XML in into std :: cou.t");
		mineModes_ [MINE_STRUCTURE]   = new option :: Bool (false, "mine-structure",   "mine global structure and put as XML in into std :: cout.");

		mineOptions_ [MINE_IMPORTS]     = new option :: Bool (false, "mine-imports",     "imports are considered.");
		mineOptions_ [MINE_CONSTANTS]   = new option :: Bool (false, "mine-constants",   "constants are considered.");
		mineOptions_ [MINE_AXIOMS]      = new option :: Bool (false, "mine-axioms",      "axioms are considered.");
		mineOptions_ [MINE_DEFINITIONS] = new option :: Bool (false, "mine-definitions", "definitions are considered.");
		mineOptions_ [MINE_RULES]       = new option :: Bool (false, "mine-rules",       "rules are considered.");
		mineOptions_ [MINE_TYPES]       = new option :: Bool (false, "mine-types",       "types are considered.");
		mineOptions_ [MINE_THEORIES]    = new option :: Bool (false, "mine-theories",    "theories are considered.");
		mineOptions_ [MINE_THEOREMS]    = new option :: Bool (false, "mine-theorems",    "theorems are considered.");
		mineOptions_ [MINE_PROBLEMS]    = new option :: Bool (false, "mine-problems",    "problems are considered.");
		mineOptions_ [MINE_ALL]         = new option :: Bool (false, "mine-all",         "all kinds of objects are considered");
	}
	inline void
	Mining :: release()
	{
		for (int i = 0; i < LOOKUP_OPTIONS_NUM; ++ i) {
			if (lookupOptions_ [i] != NULL) {
				delete lookupOptions_ [i];
				lookupOptions_ [i] = NULL;
			}
		}
		for (int i = 0; i < MINE_MODE_NUM; ++ i) {
			if (mineModes_ [i] != NULL) {
				delete mineModes_ [i];
				mineModes_ [i] = NULL;
			}
		}
		for (int i = 0; i < MINE_OPTIONS_NUM; ++ i) {
			if (mineOptions_ [i] != NULL) {
				delete mineOptions_ [i];
				mineOptions_ [i] = NULL;
			}
		}
	}
	inline Size_t
	Mining :: getVolume()
	{
		Size_t volume = 0;
		for (int i = 0; i < LOOKUP_OPTIONS_NUM; ++ i) {
			volume += object :: Object :: getAggregateVolume (lookupOptions_ [i]);
		}
		for (int i = 0; i < MINE_OPTIONS_NUM; ++ i) {
			volume += object :: Object :: getAggregateVolume (mineOptions_ [i]);
		}
		for (int i = 0; i < MINE_MODE_NUM; ++ i) {
			volume += object :: Object :: getAggregateVolume (mineModes_ [i]);
		}
		return volume;
	}

	/*************************************
	 *		Private static attributes
	 *************************************/

	container :: Bit Mining :: miningOptions_;
	Mining :: MiningMode_ Mining :: miningMode_ = Mining :: DEFAULT_MINING;

	option :: Bool* Mining :: lookupOptions_ [LOOKUP_OPTIONS_NUM];
	option :: Bool* Mining :: mineModes_ [MINE_MODE_NUM];
	option :: Bool* Mining :: mineOptions_ [MINE_OPTIONS_NUM];

	const char* Mining :: optionGroupName_ = "mining";
}
}
}

#endif /*MDL_AUXILIARY_CONFIG_MINING_CPP_*/
