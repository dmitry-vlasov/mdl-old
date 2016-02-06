/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_Info.hpp                            */
/* Description:     static class for mdl prover info parameters              */
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

class Info {
public :
	// general info output options
	enum InfoOption_ {
		SHOW_STATISTICS  = 0,
		SHOW_TIMINGS     = 1,
		SHOW_MATH        = 2,
		SHOW_VOLUME      = 3,
		SHOW_REFACTORING = 4,
		SHOW_ALL         = 5,
		INFO_OPTIONS_NUM = 6
	};

	static option :: Bool& infoOption (InfoOption_);
	static bool showStatistics();
	static bool showTimings();
	static bool showMath();
	static bool showVolume();
	static bool showRefactoring();

	// logging output options
	enum {
		LOG_PROVING     = 0,
		LOG_COMPRESSION = 1,
		LOG_ALL         = 2,
		LOG_OPTIONS_NUM = 3
	};

	static bool logProving();
	static bool logCompression();

	// interactive proving info options
	enum TreeInfo_ {
		SHOW_TREE_NODE     = 0,
		SHOW_TREE_EVIDENCE = 1,
		SHOW_TREE_UP       = 2,
		SHOW_TREE_DOWN     = 3,
		SHOW_TREE_TIMING   = 4,
		SHOW_TREE          = 5,
		SHOW_TREE_SPROUT   = 6,
		TREE_OPTIONS_NUM   = 7,
		SHOW_TREE_DEFAULT  = SHOW_TREE
	};

	static TreeInfo_ infoTree ();
	static bool infoTree (const TreeInfo_);
	static int  infoLevel();

	// info output format
	enum ShowMode_ {
		SHOW_MODE_HUMAN   = 0,
		SHOW_MODE_XML     = 1,
		SHOW_MODE_GML     = 2,
		MODE_OPTIONS_NUM  = 3,
		SHOW_MODE_DEFAULT = SHOW_MODE_HUMAN
	};

	static ShowMode_ showMode ();
	static bool showHumanReadable();
	static bool showXML();
	static bool showGML();

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

	static void init();
	static void release();
	static Size_t getVolume();

private :
	static option :: Bool* infoOptions_ [INFO_OPTIONS_NUM];
	static option :: Bool* logOptions_  [LOG_OPTIONS_NUM];
	static option :: Bool* treeOptions_ [TREE_OPTIONS_NUM];
	static option :: Bool* modeOptions_ [MODE_OPTIONS_NUM];
	static option :: Integer* infoLevelOption_;
	static const char* optionGroupName_;
};

}
}
}


