/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_Mining.hpp                          */
/* Description:     static class for mdl source mining                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_CONFIG_MINING_HPP_
#define MDL_AUXILIARY_CONFIG_MINING_HPP_

#include "mdl/types/mdl_types.hpp"
#include "mdl/auxiliary/config/mdl_auxiliary_config.dpp"

namespace mdl {
namespace auxiliary {
namespace config {

class Mining {
public :
	// lookup definitions
	static bool lookupDefinition();
	// lookup location
	static bool lookupLocation();
	// any lookup
	static bool lookup();

	// lookup options
	enum {
		LOOKUP_DEFINITION  = 0,
		LOOKUP_LOCATION    = 1,
		LOOKUP_OPTIONS_NUM = 2
	};

	// mining options
	enum {
		MINE_IMPORTS     = 0,
		MINE_CONSTANTS   = 1,
		MINE_AXIOMS      = 2,
		MINE_DEFINITIONS = 3,
		MINE_RULES       = 4,
		MINE_TYPES       = 5,
		MINE_THEORIES    = 6,
		MINE_THEOREMS    = 7,
		MINE_PROBLEMS    = 8,
		MINE_ALL         = 9,
		MINE_OPTIONS_NUM = 10
	};

	// mining mode
	enum MiningMode_ {
		MINE_NOTHING     = -1,
		MINE_OUTLINE     = 0,
		MINE_STRUCTURE   = 1,
		MINE_TYPE_SYSTEM = 2,
		MINE_MODE_NUM    = 3,
		DEFAULT_MINING   = MINE_NOTHING
	};

	static container :: Bit getMiningOptions();
	static MiningMode_ getMiningMode();
	static bool mine();

	// parse only definitions
	static bool shallowParsing();
	// parse only current file
	static bool localParsing();

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
	static bool someActionIsChosen();

	static void init();
	static void release();
	static Size_t getVolume();
	static bool initTimes();

private :
	// mine options
	static container :: Bit miningOptions_;
	// mine mode
	static MiningMode_ miningMode_;

	static option :: Bool* lookupOptions_ [LOOKUP_OPTIONS_NUM];
	static option :: Bool* mineModes_ [MINE_MODE_NUM];
	static option :: Bool* mineOptions_ [MINE_OPTIONS_NUM];

	static const char* optionGroupName_;
};

}
}
}

#endif /*MDL_AUXILIARY_CONFIG_MINING_HPP_*/
