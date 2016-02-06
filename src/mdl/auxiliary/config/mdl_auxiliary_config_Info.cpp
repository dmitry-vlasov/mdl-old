/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_Info.cpp                            */
/* Description:     static class for mdl prover info parameters              */
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

	// general info output options
	option :: Bool&
	Info :: infoOption (InfoOption_ index) {
		return *infoOptions_ [index];
	}
	inline bool
	Info :: showStatistics() {
		return infoOptions_ [SHOW_STATISTICS]->getValue();
	}
	inline bool
	Info :: showTimings() {
		return infoOptions_ [SHOW_TIMINGS]->getValue();
	}
	inline bool
	Info :: showMath() {
		return infoOptions_ [SHOW_MATH]->getValue();
	}
	inline bool
	Info :: showVolume() {
		return infoOptions_ [SHOW_VOLUME]->getValue();
	}
	inline bool
	Info :: showRefactoring() {
		return infoOptions_ [SHOW_REFACTORING]->getValue();
	}

	// logging output options
	inline bool
	Info :: logProving() {
		return logOptions_ [LOG_PROVING]->getValue();
	}
	inline bool
	Info :: logCompression() {
		return logOptions_ [LOG_COMPRESSION]->getValue();
	}

	// interactive proving info options
	Info :: TreeInfo_
	Info :: infoTree ()
	{
		for (int i = 0; i < TREE_OPTIONS_NUM; ++ i) {
			if (treeOptions_ [i]->getValue()) {
				return static_cast<TreeInfo_>(i);
			}
		}
		return SHOW_TREE_DEFAULT;
	}
	inline bool
	Info :: infoTree (const TreeInfo_ i) {
		return treeOptions_ [i]->getValue();
	}
	inline int
	Info :: infoLevel() {
		return infoLevelOption_->getValue();
	}

	// info output format
	Info :: ShowMode_
	Info :: showMode ()
	{
		for (int i = 0; i < MODE_OPTIONS_NUM; ++ i) {
			if (modeOptions_ [i]->getValue()) {
				return static_cast<ShowMode_>(i);
			}
		}
		return SHOW_MODE_DEFAULT;
	}
	inline bool
	Info :: showHumanReadable() {
		return modeOptions_ [SHOW_MODE_HUMAN]->getValue();
	}
	inline bool
	Info :: showXML() {
		return modeOptions_ [SHOW_MODE_XML]->getValue();
	}
	inline bool
	Info :: showGML() {
		return modeOptions_ [SHOW_MODE_GML]->getValue();
	}

	template<class S>
	void
	Info :: showUsageMessage (S& os, const List& groupList)
	{
		if (groupList.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int i = 0; i < INFO_OPTIONS_NUM; ++ i) {
				infoOptions_ [i]->showUsageMessage (os);
			}
			for (int i = 0; i < LOG_OPTIONS_NUM; ++ i) {
				logOptions_ [i]->showUsageMessage (os);
			}
			for (int i = 0; i < TREE_OPTIONS_NUM; ++ i) {
				treeOptions_ [i]->showUsageMessage (os);
			}
			for (int i = 0; i < MODE_OPTIONS_NUM; ++ i) {
				modeOptions_ [i]->showUsageMessage (os);
			}
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	void
	Info :: showOptionValues (S& os, const List& groupList)
	{
		if (groupList.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int i = 0; i < INFO_OPTIONS_NUM; ++ i) {
				infoOptions_ [i]->showOptionValues (os);
			}
			for (int i = 0; i < LOG_OPTIONS_NUM; ++ i) {
				logOptions_ [i]->showOptionValues (os);
			}
			for (int i = 0; i < TREE_OPTIONS_NUM; ++ i) {
				treeOptions_ [i]->showOptionValues (os);
			}
			for (int i = 0; i < MODE_OPTIONS_NUM; ++ i) {
				modeOptions_ [i]->showOptionValues (os);
			}
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	inline void
	Info :: showGroupName (S& os) {
		os << "\t" << optionGroupName_ << chars :: NEW_LINE;
	}

	/****************************
	 *		Protected members
	 ****************************/

	bool
	Info :: proceedStringOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		for (int j = 0; j < INFO_OPTIONS_NUM; ++ j) {
			if (infoOptions_[j]->proceedStringOption (opt, argCount, argValues, i)) {
				if (infoOptions_ [SHOW_ALL]->getValue()) {
					for (int k = 0; k < INFO_OPTIONS_NUM; ++ k) {
						infoOptions_ [k]->value() = true;
					}
				}
				return true;
			}
		}
		for (int j = 0; j < LOG_OPTIONS_NUM; ++ j) {
			if (logOptions_[j]->proceedStringOption (opt, argCount, argValues, i)) {
				if (logOptions_ [LOG_ALL]->getValue()) {
					for (int k = 0; k < LOG_OPTIONS_NUM; ++ k) {
						logOptions_ [k]->value() = true;
					}
				}
				return true;
			}
		}
		for (int j = 0; j < TREE_OPTIONS_NUM; ++ j) {
			if (treeOptions_[j]->proceedStringOption (opt, argCount, argValues, i)) {
				for (int k = 0; k < TREE_OPTIONS_NUM; ++ k) {
					if (k != j) {
						treeOptions_[k]->value() = false;
					}
				}
				return true;
			}
		}
		for (int j = 0; j < MODE_OPTIONS_NUM; ++ j) {
			if (modeOptions_[j]->proceedStringOption (opt, argCount, argValues, i)) {
				for (int k = 0; k < MODE_OPTIONS_NUM; ++ k) {
					if (k != j) {
						modeOptions_[k]->value() = false;
					}
				}
				return true;
			}
		}
		return false;
	}
	bool
	Info :: proceedOneCharOption (const char* opt, const int argCount, const char* argValues[], int& i) {
		return false;
	}

	bool
	Info :: isCorrect()
	{
		for (int i = 0; i < INFO_OPTIONS_NUM; ++ i) {
			if (!infoOptions_ [i]->isCorrect()) {
				return false;
			}
		}
		for (int i = 0; i < LOG_OPTIONS_NUM; ++ i) {
			if (!logOptions_ [i]->isCorrect()) {
				return false;
			}
		}
		for (int i = 0; i < TREE_OPTIONS_NUM; ++ i) {
			if (!treeOptions_ [i]->isCorrect()) {
				return false;
			}
		}
		for (int i = 0; i < MODE_OPTIONS_NUM; ++ i) {
			if (!modeOptions_ [i]->isCorrect()) {
				return false;
			}
		}
		return true;
	}

	inline void
	Info :: init ()
	{
		infoOptions_ [SHOW_STATISTICS] = new option :: Bool (false, "info-stat",        "show all statistics.");
		infoOptions_ [SHOW_TIMINGS]    = new option :: Bool (false, "info-timing",      "show thorough timing info.");
		infoOptions_ [SHOW_MATH]       = new option :: Bool (false, "info-math",        "show thorough math info.");
		infoOptions_ [SHOW_VOLUME]     = new option :: Bool (false, "info-volume",      "show thorough volume info.");
		infoOptions_ [SHOW_REFACTORING]= new option :: Bool (false, "info-refactoring", "show refactoring statistics.");
		infoOptions_ [SHOW_ALL]        = new option :: Bool (false, "info-all",         "show all thorough info.");

		logOptions_ [LOG_PROVING]     = new option :: Bool (false, "log-proving",     "switch logging on while proving.");
		logOptions_ [LOG_COMPRESSION] = new option :: Bool (false, "log-compression", "switch logging on while compression.");
		logOptions_ [LOG_ALL]         = new option :: Bool (false, "log-all",         "switch all logging on.");

		treeOptions_ [SHOW_TREE_NODE]     = new option :: Bool (false, "info-tree-node",     "show info about a prover tree node, which index is set up with the '--index' option.");
		treeOptions_ [SHOW_TREE_EVIDENCE] = new option :: Bool (false, "info-tree-evidence", "show info about an evidence node, which index is set up with the '--index' option.");
		treeOptions_ [SHOW_TREE_UP]       = new option :: Bool (false, "info-tree-up",       "show info about an up tree.");
		treeOptions_ [SHOW_TREE_DOWN]     = new option :: Bool (false, "info-tree-down",     "show info about a down tree.");
		treeOptions_ [SHOW_TREE_TIMING]   = new option :: Bool (false, "info-tree-timing",   "show prover timings.");
		treeOptions_ [SHOW_TREE]          = new option :: Bool (false, "info-tree",          "show info about a tree in general.");
		treeOptions_ [SHOW_TREE_SPROUT]   = new option :: Bool (false, "info-tree-sprout",   "show info about new nodes, added to a tree.");

		infoLevelOption_ = new option :: Integer (0, "info-tree-level", "set up a tree level info level (greater level -> more info).");

		modeOptions_ [SHOW_MODE_HUMAN] = new option :: Bool (true,  "info-human-readable", "show info in human readable format.");
		modeOptions_ [SHOW_MODE_XML]   = new option :: Bool (false, "info-xml-format",     "show info in XML format.");
		modeOptions_ [SHOW_MODE_GML]   = new option :: Bool (false, "info-gml-format",     "show info in GML (graph markup language) format.");
	}
	inline void
	Info :: release()
	{
		for (int i = 0; i < INFO_OPTIONS_NUM; ++ i) {
			delete infoOptions_ [i];
			infoOptions_ [i] = NULL;
		}
		for (int i = 0; i < LOG_OPTIONS_NUM; ++ i) {
			delete logOptions_ [i];
			logOptions_ [i] = NULL;
		}
		for (int i = 0; i < TREE_OPTIONS_NUM; ++ i) {
			delete treeOptions_ [i];
			treeOptions_ [i] = NULL;
		}
		for (int i = 0; i < MODE_OPTIONS_NUM; ++ i) {
			delete modeOptions_ [i];
			modeOptions_ [i] = NULL;
		}
		delete infoLevelOption_;
		infoLevelOption_ = NULL;
	}
	inline Size_t
	Info :: getVolume()
	{
		Size_t volume = 0;
		for (int i = 0; i < INFO_OPTIONS_NUM; ++ i) {
			volume += object :: Object :: getAggregateVolume (infoOptions_ [i]);
		}
		for (int i = 0; i < LOG_OPTIONS_NUM; ++ i) {
			volume += object :: Object :: getAggregateVolume (logOptions_ [i]);
		}
		for (int i = 0; i < TREE_OPTIONS_NUM; ++ i) {
			volume += object :: Object :: getAggregateVolume (treeOptions_ [i]);
		}
		for (int i = 0; i < MODE_OPTIONS_NUM; ++ i) {
			volume += object :: Object :: getAggregateVolume (modeOptions_ [i]);
		}
		volume += object :: Object :: getAggregateVolume (infoLevelOption_);
		return volume;
	}

	/*************************************
	 *		Private static attributes
	 *************************************/

	option :: Bool* Info :: infoOptions_ [INFO_OPTIONS_NUM];
	option :: Bool* Info :: logOptions_  [LOG_OPTIONS_NUM];
	option :: Bool* Info :: treeOptions_ [TREE_OPTIONS_NUM];
	option :: Bool* Info :: modeOptions_ [MODE_OPTIONS_NUM];
	option :: Integer* Info :: infoLevelOption_ = NULL;
	const char* Info :: optionGroupName_ = "info";
}
}
}


