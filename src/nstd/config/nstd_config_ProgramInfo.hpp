/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_config_ProgramInfo.hpp                              */
/* Description:     program description config flags                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "config/nstd_config_Base.hpp"

namespace nstd {
namespace config {

class ProgramInfo : public Base {
public :
	enum {
		SHOW_VERSION = 0,
		OPTION_NUM   = 1
	};

	static String<>& version();
	static String<>& programName();
	static String<>& programDescription();
	static const String<>& getVersion();
	static const String<>& getProgramName();
	static const String<>& getProgramDescription();

	static bool showVersion();

	template<class S>
	static void showUsageMessage (S&, const List& = List());
	template<class S>
	static void showOptionValues (S&, const List& = List());
	template<class S>
	static void showGroupName (S&);

protected :
	template<class S>
	static void showProgramInfo (S&);
	template<class S>
	static void showProgramUsage (S&);
	static void showProgramUsage ();

	static void init();
	static void release();
	static Size_t getVolume();

	static bool proceedStringOption (const char* option, const int argCount, const char* argValues[], int& );
	static bool proceedOneCharOption (const char* option, const int argCount, const char* argValues[], int& );

private :
	enum {
		INITIAL_VERSION_CAPACITY = 64,
		INITIAL_PROGRAM_NAME_CAPACITY = 256,
		INITIAL_PROGRAM_DESCRIPTION_CAPACITY = 512
	};

	static String<>* version_;
	static String<>* programName_;
	static String<>* programDescription_;

	static option :: Bool* programOptions_[OPTION_NUM];

	static const char* optionGroupName_;
};

}
}


