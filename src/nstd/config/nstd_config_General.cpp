/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_config_General.cpp                                  */
/* Description:     general purpose config flags                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONFIG_GENERAL_CPP_
#define NSTD_CONFIG_GENERAL_CPP_

namespace nstd {
namespace config {

	/****************************
	 *		Public members
	 ****************************/

	inline bool
	General :: showHelp() {
		return generalOptions_ [SHOW_HELP]->getValue();
	}
	inline bool
	General :: cleanMemory() {
		return generalOptions_ [CLEAN_MEMORY]->getValue();
	}
	inline bool
	General :: showConfigDefaults() {
		return generalOptions_ [SHOW_CONFIG_DEFAULTS]->getValue();
	}
	inline bool
	General :: overwrite() {
		return generalOptions_ [OVERWRITE]->getValue();
	}

	inline bool
	General :: verbose() {
		return (verbosity_ != VERBOSE_NONE);
	}
	inline bool
	General :: warnings() {
		return (warningity_ != WARNINGS_NONE);
	}

	inline General :: Verbosity_
	General :: verbosity() {
		return verbosity_;
	}
	inline General :: Waringity_
	General :: warningity() {
		return warningity_;
	}

	inline void
	General :: setVerbosity (const Verbosity_ verbosity) {
		verbosity_ = verbosity;
	}
	inline void
	General :: rememberVerbosity() {
		verbosityLast_ = verbosity_;
	}
	inline void
	General :: recallVerbosity() {
		verbosity_ = verbosityLast_;
	}

using std :: cout;
using std :: endl;

	template<class S>
	void
	General :: showUsageMessage (S& os, const List& list)
	{
		if (!list.contains (optionGroupName_)) {
			return;
		}
		os << optionGroupName_ << ':' << chars :: NEW_LINE;
		for (int j = 0; j < OPTION_NUM; ++ j) {
			generalOptions_[j]->showUsageMessage (os);
		}
		os << chars :: NEW_LINE;
		os << "  -v,  --verbose                medium verbose mode" << chars :: NEW_LINE;
		os << "       --verbose-min            minimal verbose mode" << chars :: NEW_LINE;
		os << "       --verbose-med            medium verbose mode" << chars :: NEW_LINE;
		os << "       --verbose-max            maximum verbose mode" << chars :: NEW_LINE;
		os << "       --verbose-ext            extra maximum verbose mode" << chars :: NEW_LINE;
		os << chars :: NEW_LINE;
		os << "  -W,  --warnings               show warnings (by default - medium)" << chars :: NEW_LINE;
		os << "       --warnings-min           show critical warnings" << chars :: NEW_LINE;
		os << "       --warnings-med           show typical warnings" << chars :: NEW_LINE;
		os << "       --warnings-max           show all warnings" << chars :: NEW_LINE;
		os << chars :: NEW_LINE;
	}
	template<class S>
	void
	General :: showOptionValues (S& os, const List& list)
	{
		if (list.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int j = 0; j < OPTION_NUM; ++ j) {
				generalOptions_[j]->showOptionValues (os);
			}
			os << "\tverbosity_ = ";
			switch (verbosity_) {
			case VERBOSE_SILENT : os << "silent"; break;
			case VERBOSE_NONE   : os << "none";   break;
			case VERBOSE_MIN    : os << "verbose-min"; break;
			case VERBOSE_MED    : os << "verbose-med"; break;
			case VERBOSE_MAX    : os << "verbose-max"; break;
			case VERBOSE_EXT    : os << "verbose-ext"; break;
			default : os << "<unknown>"; break;
			}
			os << chars :: NEW_LINE;
			os << "\twerbosity_ = ";
			switch (warningity_) {
			case WARNINGS_NONE : os << "none"; break;
			case WARNINGS_MIN  : os << "warnings-min"; break;
			case WARNINGS_MED  : os << "warnings-med"; break;
			case WARNINGS_MAX  : os << "warnings-max"; break;
			default : os << "<unknown>"; break;
			}
			os << chars :: NEW_LINE;
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	inline void
	General :: showGroupName (S& os) {
		os << "\t" << optionGroupName_ << chars :: NEW_LINE;
	}

	/****************************
	 *		Protected members
	 ****************************/

	inline void
	General :: init()
	{
		generalOptions_[SHOW_HELP]    = new option :: Bool (false, "help",          "display basic usage/options information.", 'h');
		generalOptions_[CLEAN_MEMORY] = new option :: Bool (true,  "clean-memory",  "clean up memory after the execution (test for memory leaks)");
		generalOptions_[SHOW_CONFIG_DEFAULTS] = new option :: Bool (true, "show-config-defaults",  "show default values, when showing the config.");
		generalOptions_[OVERWRITE] = new option :: Bool (false, "overwrite",  "overwrite output file", 'w');
	}
	inline void
	General :: release()
	{
		for (int i = 0; i < OPTION_NUM; ++ i) {
			delete generalOptions_ [i];
			generalOptions_ [i] = NULL;
		}
	}
	inline Size_t
	General :: getVolume()
	{
		Size_t volume = 0;
		for (int i = 0; i < OPTION_NUM; ++ i) {
			volume += Object :: getAggregateVolume (generalOptions_ [i]);
		}
		return volume;
	}

	bool
	General :: proceedStringOption (const char* option, const int argCount, const char* argValues[], int& i)
	{
		for (int j = 0; j < OPTION_NUM; ++ j) {
			if (generalOptions_[j]->proceedStringOption (option, argCount, argValues, i)) {
				return true;
			}
		}
		if (proceedVerboseOption (option, argCount, argValues, i)) {
			return true;
		}
		if (proceedWarningsOption (option, argCount, argValues, i)) {
			return true;
		}
		return false;
	}

	bool
	General :: proceedOneCharOption (const char* option, const int argCount, const char* argValues[], int& i)
	{
		for (int j = 0; j < OPTION_NUM; ++ j) {
			if (generalOptions_[j]->proceedOneCharOption (option, argCount, argValues, i)) {
				return true;
			}
		}
		switch (*option) {
		case 'v' :
			if (!verbose()) {
				verbosity_ = VERBOSE_MED;
			}
			return true;
		case 'W' :
			if (!warnings()) {
				warningity_ = WARNINGS_DEFAULT;
			}
			return true;
		default :
			return false;
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	bool
	General :: proceedVerboseOption (const char* option, const int argCount, const char* argValues[], int& i)
	{
		if (equalStrings (option, "verbose")) {
			verbosity_ = VERBOSE_MIN;
			return true;
		}
		if (equalStrings (option, "verbose-none")) {
			verbosity_ = VERBOSE_NONE;
			return true;
		}
		if (equalStrings (option, "verbose-min")) {
			verbosity_ = VERBOSE_MIN;
			return true;
		}
		if (equalStrings (option, "verbose-med")) {
			verbosity_ = VERBOSE_MED;
			return true;
		}
		if (equalStrings (option, "verbose-max")) {
			verbosity_ = VERBOSE_MAX;
			return true;
		}
		if (equalStrings (option, "verbose-ext")) {
			verbosity_ = VERBOSE_EXT;
			return true;
		}
		return false;
	}
	bool
	General :: proceedWarningsOption (const char* option, const int argCount, const char* argValues[], int& i)
	{
		if (equalStrings (option, "warnings")) {
			warningity_ = WARNINGS_DEFAULT;
			return true;
		}
		if (equalStrings (option, "warnings-min")) {
			warningity_ = WARNINGS_MIN;
			return true;
		}
		if (equalStrings (option, "warnings-med")) {
			warningity_ = WARNINGS_MED;
			return true;
		}
		if (equalStrings (option, "warnings-max")) {
			warningity_ = WARNINGS_MAX;
			return true;
		}
		return false;
	}

	/************************************
	 *		Static private attributes
	 ************************************/

	General :: Verbosity_
		General :: verbosity_     = General :: VERBOSE_DEFAULT;
	General :: Waringity_
		General :: warningity_    = General :: WARNINGS_DEFAULT;
	General :: Verbosity_
		General :: verbosityLast_ = General :: VERBOSE_DEFAULT;

	option :: Bool* General :: generalOptions_ [OPTION_NUM];
	const char* General :: optionGroupName_ = "general";
}
}

#endif /*NSTD_CONFIG_GENERAL_CPP_*/
