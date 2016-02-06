/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_config_Paths.hpp                                    */
/* Description:     paths config flags                                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "nstd/config/nstd_config_Base.hpp"

namespace nstd {
namespace config {

class Paths : public Base {
public :
	typedef Path<> Path_;
	typedef
		container :: Vector
		<
			Path_,
			container :: storage :: ByPointer,
			memory :: allocator :: Standard
		>
		PathVector_;

	enum Option_ {
		SOURCE      = 0,
		TARGET      = 1,
		SOURCE_ROOT = 2,
		TARGET_ROOT = 3,
		LOG         = 4,
		CONFIG      = 5,
		OPTION_NUM  = 6
	};

	static Path_& source();
	static Path_& target();
	static Path_& sourceRoot();
	static Path_& targetRoot();
	static Path_& log();
	static PathVector_* configVector();

	static const Path_& getSource();
	static const Path_& getTarget();
	static const Path_& getSourceRoot();
	static const Path_& getTargetRoot();
	static const Path_& getLog();
	static const PathVector_* getConfigVector();

	// Shows the usage message.
	template<class S>
	static void showUsageMessage (S&, const List& = List());
	template<class S>
	static void showOptionValues (S&, const List& = List());
	template<class S>
	static void showGroupName (S&);

protected :
	static void init();
	static void release();
	static Size_t getVolume();
	static bool checkPaths();

	static void proceedLastOption (const char*);
	static bool proceedStringOption (const char*, const int, const char* [], int&);
	static bool proceedOneCharOption (const char*, const int, const char* [], int&);

private :
	template<class>
	friend class Config;

	static bool checkSource();
	static bool checkTarget();
	static bool checkSourceRoot();
	static bool checkTargetRoot();
	static bool checkLog();
	static bool checkConfig (const Path_*);
	static bool checkSourceAndTarget();

	enum {
		INITIAL_EXTENSION_CAPACITY = 16,
		INITIAL_CONFIG_VECTOR_CAPACITY
	};

	static PathVector_* configVector_;
	static option :: Path* pathOptions_ [OPTION_NUM];
	static const char* optionGroupName_;
};

}
}


