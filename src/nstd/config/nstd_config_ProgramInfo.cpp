/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_config_ProgramInfo.cpp                              */
/* Description:     program description config flags                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONFIG_PROGRAM_INFO_CPP_
#define NSTD_CONFIG_PROGRAM_INFO_CPP_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

namespace nstd {
namespace config {

	/****************************
	 *		Public members
	 ****************************/

	inline String<>&
	ProgramInfo :: version() {
		return *version_;
	}
	inline String<>&
	ProgramInfo :: programName() {
		return *programName_;
	}
	inline String<>&
	ProgramInfo :: programDescription() {
		return *programDescription_;
	}
	inline const String<>&
	ProgramInfo :: getVersion() {
		return *version_;
	}
	inline const String<>&
	ProgramInfo :: getProgramName() {
		return *programName_;
	}
	inline const String<>&
	ProgramInfo :: getProgramDescription() {
		return *programDescription_;
	}
	inline bool
	ProgramInfo :: showVersion() {
		return programOptions_[SHOW_VERSION]->getValue();
	}

	template<class S>
	void
	ProgramInfo :: showUsageMessage (S& os, const List& list)
	{
		if (list.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int j = 0; j < OPTION_NUM; ++ j) {
				programOptions_[j]->showUsageMessage (os);
			}
		}
	}
	template<class S>
	void
	ProgramInfo :: showOptionValues (S& os, const List& list)
	{
		if (list.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int j = 0; j < OPTION_NUM; ++ j) {
				programOptions_[j]->showOptionValues (os);
			}
		}
	}
	template<class S>
	inline void
	ProgramInfo :: showGroupName (S& os) {
		os << "\t" << optionGroupName_ << chars :: NEW_LINE;
	}

	/****************************
	 *		Protected members
	 ****************************/

	template<class S>
	void
	ProgramInfo :: showProgramInfo (S& os)
	{
		os << getProgramDescription() << chars :: NEW_LINE;
		os << "Version: " << getVersion() << chars :: NEW_LINE;
		os << "Copyleft (L) 2006-2015 Dmitri Yu. Vlasov" << chars :: NEW_LINE;
	}
	template<class S>
	inline void
	ProgramInfo :: showProgramUsage (S& os) {
		os << "Usage: " << getProgramName() << " [options] file..." << chars :: NEW_LINE;
	}
	inline void
	ProgramInfo :: showProgramUsage ()
	{
		showProgramUsage (std :: cout);
		std :: cout << std :: flush;
	}

	inline void
	ProgramInfo :: init()
	{
		programOptions_[SHOW_VERSION] = new option :: Bool (false, "version", "version of program", 'V');

		version_ = new String<> (INITIAL_VERSION_CAPACITY);
		#ifdef HAVE_CONFIG_H
		*version_ << VERSION;
		#endif
		programName_ = new String<> (INITIAL_PROGRAM_NAME_CAPACITY);
		programDescription_ = new String<> (INITIAL_PROGRAM_DESCRIPTION_CAPACITY);
	}
	inline void
	ProgramInfo :: release()
	{
		if (version_ != NULL) {
			delete version_;
			version_ = NULL;
		}
		if (programName_ != NULL) {
			delete programName_;
			programName_ = NULL;
		}
		if (programDescription_ != NULL) {
			delete programDescription_;
			programDescription_ = NULL;
		}
		for (int i = 0; i < OPTION_NUM; ++ i) {
			delete programOptions_ [i];
			programOptions_ [i] = NULL;
		}
	}
	inline Size_t
	ProgramInfo :: getVolume()
	{
		Size_t volume = 0;
		if (version_ != NULL) {
			volume += version_->getVolume();
			volume += version_->getSizeOf();
		}
		if (programName_ != NULL) {
			volume += programName_->getVolume();
			volume += programName_->getSizeOf();
		}
		if (programDescription_ != NULL) {
			volume += programDescription_->getVolume();
			volume += programDescription_->getSizeOf();
		}
		for (int i = 0; i < OPTION_NUM; ++ i) {
			volume += Object :: getAggregateVolume (programOptions_ [i]);
		}
		return volume;
	}

	bool
	ProgramInfo :: proceedStringOption (const char* option, const int argCount, const char* argValues[], int& i)
	{
		for (int j = 0; j < OPTION_NUM; ++ j) {
			if (programOptions_[j]->proceedStringOption (option, argCount, argValues, i)) {
				return true;
			}
		}
		return false;
	}

	bool
	ProgramInfo :: proceedOneCharOption (const char* option, const int argCount, const char* argValues[], int& i)
	{
		for (int j = 0; j < OPTION_NUM; ++ j) {
			if (programOptions_[j]->proceedOneCharOption (option, argCount, argValues, i)) {
				return true;
			}
		}
		return false;
	}

	/************************************
	 *		Static private attributes
	 ************************************/

	String<>* ProgramInfo :: version_ = NULL;
	String<>* ProgramInfo :: programName_ = NULL;
	String<>* ProgramInfo :: programDescription_ = NULL;

	option :: Bool* ProgramInfo :: programOptions_[OPTION_NUM];

	const char* ProgramInfo :: optionGroupName_ = "program_info";
}
}

#endif /*NSTD_CONFIG_PROGRAM_INFO_CPP_*/
