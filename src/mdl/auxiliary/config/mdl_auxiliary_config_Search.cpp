/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_Search.cpp                          */
/* Description:     static class for mdl prover search mode                  */
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

	// proof search options
	Search :: SearchMode_
	Search :: searchMode()
	{
		for (int i = 0; i < SEARCH_MODE_NUM; ++ i) {
			if (searchModes_ [i]->getValue()) {
				return static_cast<SearchMode_>(i);
			}
		}
		return DEFAULT_SEARCH;
	}

	Search :: GrowUpMode_
	Search :: growUpMode()
	{
		for (int i = 0; i < GROW_UP_MODE_NUM; ++ i) {
			if (growUpModes_ [i]->getValue()) {
				return static_cast<GrowUpMode_>(i);
			}
		}
		return DEFAULT_GROW_UP;
	}

	Search :: GrowDownMode_
	Search :: growDownMode()
	{
		for (int i = 0; i < GROW_DOWN_MODE_NUM; ++ i) {
			if (growDownModes_ [i]->getValue()) {
				return static_cast<GrowDownMode_>(i);
			}
		}
		return DEFAULT_GROW_DOWN;
	}

	inline bool
	Search :: growCompleteTree() {
		return searchOptions_ [GROW_COMPLETE_TREE]->getValue();
	}
	inline option :: Bool&
	Search :: debugSearchOption (const SearchOption_ option) {
		return *searchOptions_ [option];
	}

	inline value :: Integer
	Search :: growUpLimit() {
		return searchFactors_ [GROW_UP_LIMIT]->getValue();
	}
	inline value :: Integer
	Search :: growDownLimit() {
		return searchFactors_ [GROW_DOWN_LIMIT]->getValue();
	}
	inline option :: Integer&
	Search :: searchFactorOption (const SearchFactor_ option) {
		return *searchFactors_ [option];
	}

	template<class S>
	void
	Search :: showUsageMessage (S& os, const List& groupList)
	{
		if (groupList.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int i = 0; i < SEARCH_MODE_NUM; ++ i) {
				searchModes_ [i]->showUsageMessage (os);
			}
			os << chars :: NEW_LINE;
			for (int i = 0; i < GROW_UP_MODE_NUM; ++ i) {
				growUpModes_ [i]->showUsageMessage (os);
			}
			for (int i = 0; i < GROW_DOWN_MODE_NUM; ++ i) {
				growDownModes_ [i]->showUsageMessage (os);
			}
			os << chars :: NEW_LINE;
			for (int i = 0; i < SEARCH_OPTION_NUM; ++ i) {
				searchOptions_ [i]->showUsageMessage (os);
			}
			for (int i = 0; i < SEARCH_FACTOR_NUM; ++ i) {
				searchFactors_ [i]->showUsageMessage (os);
			}
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	void
	Search :: showOptionValues (S& os, const List& groupList)
	{
		if (groupList.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int i = 0; i < SEARCH_MODE_NUM; ++ i) {
				searchModes_ [i]->showOptionValues (os);
			}
			os << chars :: NEW_LINE;
			for (int i = 0; i < GROW_UP_MODE_NUM; ++ i) {
				growUpModes_ [i]->showOptionValues (os);
			}
			for (int i = 0; i < GROW_DOWN_MODE_NUM; ++ i) {
				growDownModes_ [i]->showOptionValues (os);
			}
			os << chars :: NEW_LINE;
			for (int i = 0; i < SEARCH_OPTION_NUM; ++ i) {
				searchOptions_ [i]->showOptionValues (os);
			}
			for (int i = 0; i < SEARCH_FACTOR_NUM; ++ i) {
				searchFactors_ [i]->showOptionValues (os);
			}
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	inline void
	Search :: showGroupName (S& os) {
		os << "\t" << optionGroupName_ << chars :: NEW_LINE;
	}

	/****************************
	 *		Protected members
	 ****************************/

	bool
	Search :: proceedStringOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		for (int j = 0; j < SEARCH_MODE_NUM; ++ j) {
			if (searchModes_[j]->proceedStringOption (opt, argCount, argValues, i)) {
				if (searchModes_ [j]->getValue()) {
					for (int k = 0; k < SEARCH_MODE_NUM; k ++) {
						if (k != j) {
							searchModes_ [k]->value() = false;
						}
					}
				}
				return true;
			}
		}
		for (int j = 0; j < GROW_UP_MODE_NUM; ++ j) {
			if (growUpModes_[j]->proceedStringOption (opt, argCount, argValues, i)) {
				if (growUpModes_ [j]->getValue()) {
					for (int k = 0; k < GROW_UP_MODE_NUM; k ++) {
						if (k != j) {
							growUpModes_ [k]->value() = false;
						}
					}
				}
				return true;
			}
		}
		for (int j = 0; j < GROW_DOWN_MODE_NUM; ++ j) {
			if (growDownModes_[j]->proceedStringOption (opt, argCount, argValues, i)) {
				if (growDownModes_ [j]->getValue()) {
					for (int k = 0; k < GROW_DOWN_MODE_NUM; k ++) {
						if (k != j) {
							growDownModes_ [k]->value() = false;
						}
					}
				}
				return true;
			}
		}
		for (int j = 0; j < SEARCH_OPTION_NUM; ++ j) {
			if (searchOptions_[j]->proceedStringOption (opt, argCount, argValues, i)) {
				return true;
			}
		}
		for (int j = 0; j < SEARCH_FACTOR_NUM; ++ j) {
			if (searchFactors_[j]->proceedStringOption (opt, argCount, argValues, i)) {
				return true;
			}
		}
		return false;
	}
	bool
	Search :: proceedOneCharOption (const char* opt, const int argCount, const char* argValues[], int& i) {
		return false;
	}

	bool
	Search :: isCorrect()
	{
		bool result = true;
		int count = 0;
		for (int i = 0; i < SEARCH_MODE_NUM; ++ i) {
			if (!searchModes_ [i]->isCorrect()) {
				return false;
			}
			if (searchModes_[i]->getValue()) {
				++ count;
			}
		}
		result = result && (count <= 1);
		count = 0;
		for (int i = 0; i < GROW_UP_MODE_NUM; ++ i) {
			if (!growUpModes_ [i]->isCorrect()) {
				return false;
			}
			if (growUpModes_[i]->getValue()) {
				++ count;
			}
		}
		result = result && (count <= 1);
		count = 0;
		for (int i = 0; i < GROW_DOWN_MODE_NUM; ++ i) {
			if (!growDownModes_ [i]->isCorrect()) {
				return false;
			}
			if (growDownModes_[i]->getValue()) {
				++ count;
			}
		}
		for (int i = 0; i < SEARCH_OPTION_NUM; ++ i) {
			if (!searchOptions_ [i]->isCorrect()) {
				return false;
			}
		}
		for (int i = 0; i < SEARCH_FACTOR_NUM; ++ i) {
			if (!searchFactors_ [i]->isCorrect()) {
				return false;
			}
		}
		return result;
	}

	void
	Search :: init ()
	{
		searchModes_ [MINIMAL_SEARCH]    = new option :: Bool (false, "minimal-search",    "use greedy search for the proof.");
		searchModes_ [OPTIMAL_SEARCH]    = new option :: Bool (false, "optimal-search",    "search for the reasonably shorter proof.");
		searchModes_ [MAXIMAL_SEARCH]    = new option :: Bool (false, "maximal-search",    "search for the shortest proof of a minimal depth.");

		growUpModes_   [GROW_UP_UNRESTRICTED] = new option :: Bool (false, "grow-up-unrestricted", "default grow up mode.");
		growUpModes_   [GROW_UP_DETERMINED]   = new option :: Bool (false, "grow-up-determined",   "testing mode: used to test the building down tree.");
		growDownModes_ [GROW_DOWN_DELAYED]    = new option :: Bool (false, "grow-down-delayed",    "default grow down mode.");
		growDownModes_ [GROW_DOWN_IMMEDIATE]  = new option :: Bool (false, "grow-down-immediate",  "testing mode.");
		growDownModes_ [GROW_DOWN_DETERMINED] = new option :: Bool (false, "grow-down-determined", "testing mode.");
		searchOptions_ [GROW_COMPLETE_TREE]  = new option :: Bool (false, "grow-complete-tree",  "testing mode: used to test the building down tree.");

		searchFactors_ [GROW_UP_LIMIT] = new option :: Integer
		(
			value :: undefined :: INTEGER,
			"grow-up-limit",
			"testing mode: grow up at most <int> nodes."
		);
		searchFactors_ [GROW_DOWN_LIMIT] = new option :: Integer
		(
			value :: undefined :: INTEGER,
			"grow-down-limit",
			"testing mode: grow down at most <int> nodes."
		);
	}
	void
	Search :: release()
	{
		for (int i = 0; i < SEARCH_MODE_NUM; ++ i) {
			delete searchModes_ [i];
			searchModes_ [i] = NULL;
		}
		for (int i = 0; i < GROW_UP_MODE_NUM; ++ i) {
			delete growUpModes_ [i];
			growUpModes_ [i] = NULL;
		}
		for (int i = 0; i < GROW_DOWN_MODE_NUM; ++ i) {
			delete growDownModes_ [i];
			growDownModes_ [i] = NULL;
		}
		for (int i = 0; i < SEARCH_OPTION_NUM; ++ i) {
			delete searchOptions_ [i];
			searchOptions_ [i] = NULL;
		}
		for (int i = 0; i < SEARCH_FACTOR_NUM; ++ i) {
			delete searchFactors_ [i];
			searchFactors_ [i] = NULL;
		}
	}
	Size_t
	Search :: getVolume()
	{
		Size_t volume = 0;
		for (int i = 0; i < SEARCH_MODE_NUM; ++ i) {
			volume += object :: Object :: getAggregateVolume (searchModes_ [i]);
		}
		for (int i = 0; i < GROW_UP_MODE_NUM; ++ i) {
			volume += object :: Object :: getAggregateVolume (growUpModes_ [i]);
		}
		for (int i = 0; i < GROW_DOWN_MODE_NUM; ++ i) {
			volume += object :: Object :: getAggregateVolume (growDownModes_ [i]);
		}
		for (int i = 0; i < SEARCH_OPTION_NUM; ++ i) {
			volume += object :: Object :: getAggregateVolume (searchOptions_ [i]);
		}
		for (int i = 0; i < SEARCH_FACTOR_NUM; ++ i) {
			volume += object :: Object :: getAggregateVolume (searchFactors_ [i]);
		}
		return volume;
	}

	/*************************************
	 *		Private static attributes
	 *************************************/

	option :: Bool*    Search :: searchModes_   [SEARCH_MODE_NUM];
	option :: Bool*    Search :: growUpModes_   [GROW_UP_MODE_NUM];
	option :: Bool*    Search :: growDownModes_ [GROW_DOWN_MODE_NUM];
	option :: Bool*    Search :: searchOptions_ [SEARCH_OPTION_NUM];
	option :: Integer* Search :: searchFactors_ [SEARCH_FACTOR_NUM];
	const char* Search :: optionGroupName_ = "search";
}
}
}


