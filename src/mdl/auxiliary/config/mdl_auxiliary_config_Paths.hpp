/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_Paths.hpp                           */
/* Description:     path options                                             */
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

class Paths {
public :
	typedef nstd :: Path<> Path_;

	enum Paths_ {
		UNIVERSE_PATH = 0,
		PATHS_NUM     = 1
	};

	static Path_& universe();
	static const Path_& getUniverse();

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
	static bool checkPaths();

private :
	enum {
		INITIAL_EXTENSION_CAPACITY = 16
	};
	static bool checkUniverse();

	static option :: Path* pathOptions_[PATHS_NUM];
	static const char* optionGroupName_;
};

}
}
}


