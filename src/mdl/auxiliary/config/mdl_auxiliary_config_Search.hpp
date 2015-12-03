/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_Search.hpp                          */
/* Description:     static class for mdl prover search mode                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_CONFIG_SEARCH_HPP_
#define MDL_AUXILIARY_CONFIG_SEARCH_HPP_

#include "mdl/types/mdl_types.hpp"
#include "mdl/auxiliary/config/mdl_auxiliary_config.dpp"

namespace mdl {
namespace auxiliary {
namespace config {

class Search {
public :
	// proof search options
	enum SearchMode_ {
		MINIMAL_SEARCH   = 0,
		OPTIMAL_SEARCH   = 1,
		MAXIMAL_SEARCH   = 2,
		SEARCH_MODE_NUM  = 3,
		DEFAULT_SEARCH = OPTIMAL_SEARCH
	};
	static SearchMode_ searchMode();

	// Prover debug options
	enum GrowUpMode_ {
		GROW_UP_UNRESTRICTED = 0,
		GROW_UP_DETERMINED   = 1,
		GROW_UP_MODE_NUM     = 2,
		DEFAULT_GROW_UP = GROW_UP_UNRESTRICTED
	};
	static GrowUpMode_ growUpMode();

	enum GrowDownMode_ {
		GROW_DOWN_DELAYED    = 0,
		GROW_DOWN_IMMEDIATE  = 1,
		GROW_DOWN_DETERMINED = 2,
		GROW_DOWN_MODE_NUM   = 3,
		DEFAULT_GROW_DOWN = GROW_DOWN_DELAYED
	};
	static GrowDownMode_ growDownMode();

	enum SearchOption_ {
		GROW_COMPLETE_TREE  = 0,
		SEARCH_OPTION_NUM   = 1
	};

	static bool growCompleteTree();
	static option :: Bool& debugSearchOption (const SearchOption_);

	enum SearchFactor_ {
		GROW_UP_LIMIT     = 0,
		GROW_DOWN_LIMIT   = 1,
		SEARCH_FACTOR_NUM = 2
	};

	static value :: Integer growUpLimit();
	static value :: Integer growDownLimit();
	static option :: Integer& searchFactorOption (const SearchFactor_);

	template<class S>
	static void showUsageMessage (S&, const List& groupList = List());
	template<class S>
	static void showOptionValues (S&, const List& groupList = List());
	template<class S>
	static void showGroupName    (S&);

protected :
	static bool proceedStringOption (const char*, const int, const char* [], int&);
	static bool proceedOneCharOption (const char*, const int, const char* [], int&);

	static bool isCorrect();

	static void init();
	static void release();
	static Size_t getVolume();

private :
	// search options
	static option :: Bool*    searchModes_   [SEARCH_MODE_NUM];
	static option :: Bool*    growUpModes_   [GROW_UP_MODE_NUM];
	static option :: Bool*    growDownModes_ [GROW_DOWN_MODE_NUM];
	static option :: Bool*    searchOptions_ [SEARCH_OPTION_NUM];
	static option :: Integer* searchFactors_ [SEARCH_FACTOR_NUM];
	static const char* optionGroupName_;
};

}
}
}

#endif /*MDL_AUXILIARY_CONFIG_SEARCH_HPP_*/
