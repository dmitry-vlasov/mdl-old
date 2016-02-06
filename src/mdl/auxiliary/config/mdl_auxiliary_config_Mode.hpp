/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_Mode.hpp                            */
/* Description:     static class for mdl run mode                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/types/mdl_types.hpp"
#include "mdl/auxiliary/config/mdl_auxiliary_config.dpp"

namespace mdl {
namespace auxiliary {
namespace config {

class Mode {
public :
	// Possible run variants:
	enum Run_ {
		RUN_ONEFOLD = 0, // Runs mdl for a single purpose, selected by Work_ value
		RUN_SERVER  = 1, // Runs mdl as a server, granting an access to the mdl engine
		RUN_CONSOLE = 2, // Runs mdl in a console, so that user may control all stages of processing
		RUN_NUM = 3,
		DEFAULT_RUN = RUN_ONEFOLD
	};

	enum Mode_ {
		CHECK       = 0,
		TRANSLATE   = 1,
		PROVE       = 2,
		COMPRESS    = 3,
		REPROVE     = 4,
		LEARN       = 5,
		TUNE        = 6,
		BENCHMARK   = 7,
		REFACTOR    = 8,
		MODE_NUM    = 9
	};

	// mdl runs in intreactive mode
	static bool interactive();

	// Runs mdl for a single purpose, selected by Work_ value
	static bool runOnefold();
	// Runs mdl as a server, granting an access to the mdl engine
	static bool runServer();
	// Runs mdl in a console, so that user may control all stages of processing
	static bool runConsole();

	// check proofs
	static bool check();
	// translate to smm
	static bool translate();
	// prove problems
	static bool prove();
	// compress proofs
	static bool compress();
	// reprove proofs
	static bool reprove();
	// prover learning
	static bool learn();
	// tune learning
	static bool tune();
	// benchmark tuning
	static bool benchmark();
	// refactor source
	static bool refactor();

	enum {
		EXPERIENCE_NAME         = 0,
		EXCLUDED_ASSERTION_NAME = 1,
		COMPRESS_ASSERTION_NAME = 2,
		REFINED_RULE_NAME       = 3,
		REFINED_TYPE_NAME       = 4,
		NAME_NUM                = 5
	};

	// experience (for learning and proving)
	static value :: Name experience();
	// exclude the assertion from learning
	static value :: Name excludeAssertion();
	// compress the exact assertion
	static value :: Name compressAssertion();

	// rule name to be refined
	static value :: Name refinedRule();
	// type name to be refined
	static value :: Name refinedType();

	// compress one of each getCompressionFactor() theorems
	static value :: Integer getCompressionFactor();

	template<class S>
	static void showUsageMessage (S&, const List& groupList = List());
	template<class S>
	static void showOptionValues (S&, const List& groupList = List());
	template<class S>
	static void showGroupName (S&);

protected :
	static bool proceedStringOption (const char*, const int, const char* [], int&);
	static bool proceedOneCharOption (const char*, const int, const char* [], int&);

	static bool isCorrect();

	static bool isConsistent();
	static bool someRunIsChosen();
	static bool someModeIsChosen();

	static void init();
	static void release();
	static Size_t getVolume();

private :
	enum {
		DEFAULT_COMPRESSION_FACTOR = 1 // compress one of each DEFAULT_COMPRESSION_FACTOR theorems
	};

	// general work mode flags
	static option :: Bool*    runOptions_  [RUN_NUM];
	static option :: Bool*    modeOptions_ [MODE_NUM];
	static option :: String*  nameOptions_ [NAME_NUM];
	static option :: Integer* compressionFactor_;
	static option :: Bool*    interactiveOption_;

	static value :: Name names_ [NAME_NUM];

	static const char* optionGroupName_;
};

}
}
}


