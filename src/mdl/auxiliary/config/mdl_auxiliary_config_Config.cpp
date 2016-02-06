/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_Config.cpp                          */
/* Description:     static class for command line arguments                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "smm/auxiliary/smm_auxiliary_Config.hpp"

namespace mdl {
namespace auxiliary {
namespace config {

	/****************************
	 *		Public members
	 ****************************/

	inline RunMode
	Config :: getRunMode() {
		return runMode_;
	}
	inline void
	Config :: setRunMode (const RunMode runMode) {
		runMode_ = runMode;
	}

	inline bool
	Config :: useProver() {
		return (prove() || compress() || reprove() ||
				Mode :: runServer() || Mode :: runConsole());
	}
	inline bool
	Config :: useLearning() {
		return (learn() || reprove() || tune() || benchmark() ||
				Mode :: runServer() || Mode :: runConsole());
	}
	inline bool
	Config :: useWriting() {
		return (translate() || prove() || reprove() || compress() || learn() || refactor() ||
				Mode :: runServer() || Mode :: runConsole());
	}

	// memory options
	inline Size_t
	Config :: getStackVolume() {
		return Memory :: getStackVolume();
	}
	inline Size_t
	Config :: getProverVolume()
	{
		if (useProver()) {
			return Memory :: getProverVolume();
		} else {
			return 0;
		}
	}
	inline Size_t
	Config :: getReserveVolume()
	{
		if (useProver()) {
			return Memory :: getReserveVolume();
		} else {
			return 0;
		}
	}

using std :: cout;
using std :: endl;

	bool
	Config :: proceed (const int argCount, const char* argValues[])
	{
		init();
		if (Mode :: runOnefold() && Ancestor_ :: getSource().isUndefined()) {
			cout << getProgramName() << ": no input files" << endl;
			exit_ = true;
			error_ = true;
			return false;
		}
		if (!Ancestor_ :: proceedOptions (argCount,argValues)) {
			return false;
		}
		return analyseArguments();
	}
	bool
	Config :: proceedStringOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		if (Ancestor_ :: proceedStringOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (Concurrency :: proceedStringOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (Info :: proceedStringOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (Integer :: proceedStringOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (Location :: proceedStringOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (Memory :: proceedStringOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (Mining :: proceedStringOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (Misc :: proceedStringOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (Mode :: proceedStringOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (Paths :: proceedStringOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (Real :: proceedStringOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (Refactor :: proceedStringOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (Search :: proceedStringOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (Server :: proceedStringOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (String :: proceedStringOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (Timing :: proceedStringOption (opt, argCount, argValues, i)) {
			return true;
		}
		return false;
	}
	bool
	Config :: proceedOneCharOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		if (Ancestor_ :: proceedOneCharOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (Location :: proceedOneCharOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (Mode :: proceedOneCharOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (Server :: proceedOneCharOption (opt, argCount, argValues, i)) {
			return true;
		}
		return false;
	}
	bool
	Config :: analyseArguments()
	{
		if (showHelp()) {
			showUsageMessage();
		}
		if (exit()) {
			return false;
		}
		if (!checkCorrectness()) {
			return false;
		}
		if (!checkConsistency()) {
			return false;
		}
		return true;
	}

	template<class S>
	void
	Config :: showUsageMessage (S& os, const List& groupList)
	{
		if (Config :: runOnefold()) {
			Ancestor_ :: showProgramUsage (os);
		}
		Ancestor_ :: showUsageMessage (os, groupList);
		os << "Mdl options:" << chars :: NEW_LINE;
		Mode    :: showUsageMessage (os, groupList);
		Timing  :: showUsageMessage (os, groupList);
		Concurrency :: showUsageMessage (os, groupList);
		Memory  :: showUsageMessage (os, groupList);
		Search  :: showUsageMessage (os, groupList);
		Paths   :: showUsageMessage (os, groupList);
		Real    :: showUsageMessage (os, groupList);
		Refactor:: showUsageMessage (os, groupList);
		Integer :: showUsageMessage (os, groupList);
		Location:: showUsageMessage (os, groupList);
		Info    :: showUsageMessage (os, groupList);
		Mining  :: showUsageMessage (os, groupList);
		Misc    :: showUsageMessage (os, groupList);
		String  :: showUsageMessage (os, groupList);
		Server  :: showUsageMessage (os, groupList);
	}
	template<class S>
	void
	Config :: showOptionValues (S& os, const List& groupList)
	{
		os << "Option values:" << chars :: NEW_LINE;
		Ancestor_ :: showOptionValues (os, groupList);
		Mode    :: showOptionValues (os, groupList);
		Timing  :: showOptionValues (os, groupList);
		Concurrency :: showOptionValues (os, groupList);
		Memory  :: showOptionValues (os, groupList);
		Search  :: showOptionValues (os, groupList);
		Paths   :: showOptionValues (os, groupList);
		Real    :: showOptionValues (os, groupList);
		Refactor:: showOptionValues (os, groupList);
		Integer :: showOptionValues (os, groupList);
		Location:: showOptionValues (os, groupList);
		Info    :: showOptionValues (os, groupList);
		Mining  :: showOptionValues (os, groupList);
		Misc    :: showOptionValues (os, groupList);
		String  :: showOptionValues (os, groupList);
		Server  :: showOptionValues (os, groupList);
	}
	template<class S>
	void
	Config :: showGroupNames (S& os) {
		os << "Option group names." << chars :: NEW_LINE;
		os << "-------------------" << chars :: NEW_LINE;
		os << "General:" << chars :: NEW_LINE;
		Ancestor_ :: showGroupNames (os);
		os << chars :: NEW_LINE;
		os << "Mdl:" << chars :: NEW_LINE;
		Mode    :: showGroupName (os);
		Timing  :: showGroupName (os);
		Concurrency :: showGroupName (os);
		Memory  :: showGroupName (os);
		Search  :: showGroupName (os);
		Paths   :: showGroupName (os);
		Real    :: showGroupName (os);
		Refactor:: showGroupName (os);
		Integer :: showGroupName (os);
		Location:: showGroupName (os);
		Info    :: showGroupName (os);
		Mining  :: showGroupName (os);
		Misc    :: showGroupName (os);
		String  :: showGroupName (os);
		Server  :: showGroupName (os);
		os << chars :: NEW_LINE;
	}
	void
	Config :: showUsageMessage ()
	{
		showUsageMessage (std :: cout);
		std :: cout << std :: flush;
	}

	inline void
	Config :: show() {
		showUsageMessage (std :: cout);
	}
	inline void
	Config :: init()
	{
		static bool initialized = false;
		if (initialized) {
			return;
		}
		Ancestor_ :: init ();
		Concurrency :: init();
		Info    :: init();
		Integer :: init();
		Location:: init();
		Memory  :: init();
		Mining  :: init();
		Misc    :: init();
		Mode    :: init();
		Paths   :: init();
		Real    :: init();
		Refactor:: init();
		Search  :: init();
		Server  :: init();
		String  :: init();
		Timing  :: init();
		programName() << "mdl";
		programDescription() << "mdl prover & translator from Russell to smm (Simplified MetaMath)";
		initialized = true;
	}
	inline void
	Config :: release()
	{
		Ancestor_ :: release();
		Concurrency :: release();
		Info    :: release();
		Integer :: release();
		Location:: release();
		Memory  :: release();
		Mining  :: release();
		Misc    :: release();
		Mode    :: release();
		Paths   :: release();
		Real    :: release();
		Refactor:: release();
		Search  :: release();
		Server  :: release();
		String  :: release();
		Timing  :: release();
	}
	inline Size_t
	Config :: getVolume()
	{
		Size_t volume = 0;
		volume += Ancestor_ :: getVolume();
		volume += Concurrency :: getVolume();
		volume += Info    :: getVolume();
		volume += Integer :: getVolume();
		volume += Location:: getVolume();
		volume += Memory  :: getVolume();
		volume += Mining  :: getVolume();
		volume += Misc    :: getVolume();
		volume += Mode    :: getVolume();
		volume += Paths   :: getVolume();
		volume += Real    :: getVolume();
		volume += Refactor:: getVolume();
		volume += Search  :: getVolume();
		volume += Server  :: getVolume();
		volume += String  :: getVolume();
		volume += Timing  :: getVolume();
		return volume;
	}

	/****************************
	 *		Private members
	 ****************************/

	inline bool
	Config :: initRunMode()
	{
		if (translate()) {
			runMode_ = TRANSLATE_WORK;
		}
		if (check()) {
			runMode_ = CHECK_WORK;
		}
		if (prove()) {
			runMode_ = PROVE_WORK;
		}
		if (compress()) {
			runMode_ = COMPRESS_WORK;
		}
		if (reprove()) {
			runMode_ = REPROVE_WORK;
		}
		if (learn()) {
			runMode_ = LEARN_WORK;
		}
		if (tune()) {
			runMode_ = TUNE_WORK;
		}
		if (benchmark()) {
			runMode_ = BENCHMARK_WORK;
		}
		if (refactor()) {
			runMode_ = REFACTOR_WORK;
		}
		if (lookup()) {
			verbosity_ = VERBOSE_NONE;
			generalOptions_[CLEAN_MEMORY]->value() = false;
			runMode_ = LOOKUP_WORK;
		}
		if (mine()) {
			verbosity_ = VERBOSE_NONE;
			generalOptions_[CLEAN_MEMORY]->value() = false;
			runMode_ = MINE_WORK;
		}
		return true;
	}
	bool
	Config :: isConsistent()
	{
		if (!Mining :: isConsistent() || !Mode :: isConsistent()) {
			exit_ = true;
			error_ = true;
			return false;
		}
		if (Mining :: someActionIsChosen() && Mode :: someModeIsChosen()) {
			std :: cout << "two different actions are chosen." << std :: endl;
			exit_ = true;
			error_ = true;
			return false;
		}
		if (Mode :: runOnefold() && !Mining :: someActionIsChosen() && !Mode :: someModeIsChosen()) {
			std :: cout << "no action is chosen." << std :: endl;
			exit_ = true;
			error_ = true;
			return false;
		}
		return true;
	}
	bool
	Config :: checkPaths()
	{
		if (!Mode :: runOnefold()) {
			return true;
		}
		if (getSource().getExtension() != russellExtension()) {
			cout << "wrong source extension *." << getSource().getExtension() << std :: endl;
			cout << "Should be *." << russellExtension() << endl;
			exit_ = true;
			error_ = true;
			return false;
		}
		if (translate()) {
			if (getTarget().isUndefined()) {
				target().copy (getSource());
				target().extension() = smm :: Config :: smmExtension();
			}
			if (getTarget().getExtension() != smm :: Config :: smmExtension()) {
				cout << "wrong target extension *." << getTarget().getExtension() << std :: endl;
				cout << "Should be *." << smm :: Config :: smmExtension() << endl;
				exit_ = true;
				error_ = true;
				return false;
			}
		}
		if (prove() || compress() || reprove() || learn()) {
			if (getTarget().isUndefined()) {
				target().copy (getSource());
				target().extension() = russellExtension();
				if (insertPostfix()) {
					target().name() << "_out";
				}
			}
			if (getTarget().getExtension() != russellExtension()) {
				cout << "wrong target extension *." << getTarget().getExtension() << std :: endl;
				cout << "Should be *." <<russellExtension() << endl;
				exit_ = true;
				error_ = true;
				return false;
			}
		}
		if (!Paths :: checkPaths()) {
			return false;
		}
		if (!Ancestor_ :: Paths :: checkPaths()) {
			return false;
		}
		return true;
	}
	bool
	Config :: checkCorrectness()
	{
		if (!Concurrency :: isCorrect()) {
			return false;
		}
		if (!Info :: isCorrect()) {
			return false;
		}
		if (!Integer :: isCorrect()) {
			return false;
		}
		if (!Location :: isCorrect()) {
			return false;
		}
		if (!Memory :: isCorrect()) {
			return false;
		}
		if (!Mining :: isCorrect()) {
			return false;
		}
		if (!Misc :: isCorrect()) {
			return false;
		}
		if (!Mode :: isCorrect()) {
			return false;
		}
		if (!Paths :: isCorrect()) {
			return false;
		}
		if (!Real :: isCorrect()) {
			return false;
		}
		if (!Refactor :: isCorrect()) {
			return false;
		}
		if (!Search :: isCorrect()) {
			return false;
		}
		if (!Server :: isCorrect()) {
			return false;
		}
		if (!String :: isCorrect()) {
			return false;
		}
		if (!Timing :: isCorrect()) {
			return false;
		}
		return true;
	}
	bool
	Config :: checkConsistency()
	{
		if (!initRunMode()) {
			return false;
		}
		if (!isConsistent()) {
			return false;
		}
		if (!checkPaths()) {
			return false;
		}
		if (!Memory :: initMemorySize (lookup(), exit_, error_)) {
			return false;
		}
		if (!Timing :: initTimeLimit (runMode_)) {
			return false;
		}
		return true;
	}

	/*************************************
	 *		Private static attributes
	 *************************************/

	RunMode Config :: runMode_ = DEFAULT_WORK;
}
}
}


