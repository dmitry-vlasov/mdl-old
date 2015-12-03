/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_config_General.hpp                                  */
/* Description:     general purpose config flags                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONFIG_GENERAL_HPP_
#define NSTD_CONFIG_GENERAL_HPP_

#include "config/nstd_config_Base.hpp"
#include "config/nstd_config_List.hpp"

namespace nstd {
namespace config {

class General : public config :: Base {
public :
	enum Verbosity_ {
		VERBOSE_SILENT   = -1,
		VERBOSE_NONE     = 0,
		VERBOSE_MIN      = 1,
		VERBOSE_MED      = 2,
		VERBOSE_MAX      = 3,
		VERBOSE_EXT      = 4,
		VERBOSE_DEFAULT  = VERBOSE_NONE
	};

	enum Waringity_ {
		WARNINGS_NONE     = 0,
		WARNINGS_MIN      = 1,
		WARNINGS_MED      = 2,
		WARNINGS_MAX      = 3,
		WARNINGS_DEFAULT  = WARNINGS_MED
	};

	enum Option_ {
		SHOW_HELP            = 0,
		CLEAN_MEMORY         = 1,
		SHOW_CONFIG_DEFAULTS = 2,
		OVERWRITE            = 3,
		OPTION_NUM           = 4
	};

	static bool showHelp();
	static bool cleanMemory();
	static bool showConfigDefaults();
	static bool overwrite();

	static bool verbose();
	static bool warnings();

	static Verbosity_ verbosity();
	static Waringity_ warningity();

	static void setVerbosity (const Verbosity_);
	static void rememberVerbosity();
	static void recallVerbosity();

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

	static bool proceedStringOption (const char* opt, const int argCount, const char* argValues[], int& i);
	static bool proceedOneCharOption (const char* opt, const int argCount, const char* argValues[], int& i);

	static bool proceedVerboseOption (const char* opt, const int argCount, const char* argValues[], int& i);
	static bool proceedWarningsOption (const char* opt, const int argCount, const char* argValues[], int& i);

	// Verbosity level
	static Verbosity_  verbosity_;
	// Warningity level
	static Waringity_  warningity_;
	// last verbosity -
	static Verbosity_  verbosityLast_;

	static option :: Bool* generalOptions_ [OPTION_NUM];
	static const char* optionGroupName_;
};

}
}

#endif /*NSTD_CONFIG_GENERAL_HPP_*/
