/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_auxiliary_Config.cpp                                 */
/* Description:     static class for command line arguments                  */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_AUXILIARY_CONFIG_CPP_
#define SMM_AUXILIARY_CONFIG_CPP_

#include "smm/auxiliary/smm_auxiliary_Config.hpp"

namespace smm {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	inline bool
	Config :: keepChecking () {
		return keepChecking_;
	}
	inline bool
	Config :: showStack() {
		return showStack_;
	}
	inline bool
	Config :: noLabels() {
		return noLabels_;
	}
	inline bool
	Config :: asciiOnly() {
		return asciiOnly_;
	}

	// info output options
	inline bool
	Config :: showTimings() {
		return showTimings_;
	}
	inline bool
	Config :: showMath() {
		return showMath_;
	}
	inline bool
	Config :: showVolume() {
		return showVolume_;
	}

using std :: cout;
using std :: endl;

	bool
	Config :: proceed (const int argCount, const char* argValues[])
	{
		init();
		if (argCount == 1) {
			std :: cout << getProgramName() << ": no input files" << std :: endl;
			exit_ = true;
			error_ = true;
			return false;
		}
		if (!Ancestor_ :: proceedOptions (argCount,argValues)) {
			return false;
		}
		return analyseArguments();
	}
	bool
	Config :: proceedStringOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		if (Ancestor_ :: proceedStringOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (equalStrings (opt, "show-stack")) {
			showStack_ = true;
			return true;
		}
		if (equalStrings (opt, "keep-checking")) {
			keepChecking_ = true;
			return true;
		}
		if (equalStrings (opt, "no-labels")) {
			noLabels_ = true;
			return true;
		}
		if (equalStrings (opt, "ascii-only")) {
			asciiOnly_ = true;
			return true;
		}
		if (equalStrings (opt, "info-timing")) {
			showTimings_ = true;
			return true;
		}
		if (equalStrings (opt, "info-math")) {
			showMath_ = true;
			return true;
		}
		if (equalStrings (opt, "info-volume")) {
			showVolume_ = true;
			return true;
		}
		if (equalStrings (opt, "info-all")) {
			showTimings_ = true;
			showMath_ = true;
			showVolume_ = true;
			return true;
		}
		return false;
	}
	bool
	Config :: proceedOneCharOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		switch (*opt) {
		case 'k' :
			keepChecking_ = true;
			return true;
		case 's' :
			showStack_ = true;
			return true;
		default :
			return Ancestor_ :: proceedOneCharOption (opt, argCount, argValues, i);
		}
	}

	inline void
	Config :: release() {
		Ancestor_ :: release();
	}
	inline Size_t
	Config :: getVolume() {
		return Ancestor_ :: getVolume();
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Config :: showUsageMessage()
	{
		Ancestor_ :: showProgramUsage();
		cout << "Options:" << endl;
		Ancestor_ :: showUsageMessage (cout);
		cout << "  -k,  --keep-checking          keep checking at check errors" << endl;
		cout << "  -s,  --show-stack             extra debugging facility - " << endl;
		cout << "                                shows proof stack when proof error occurs." << endl;
		cout << "       --no-labels              do not use name table for assertion labels." << endl;
		cout << "       --ascii-only             do not allow non-ascii characters in source code." << endl;
		cout << endl;
		cout << "       --info-timing            show thorough timing info" << endl;
		cout << "       --info-math              show thorough math info" << endl;
		cout << "       --info-volume            show thorough volume info" << endl;
		cout << "       --info-all               show all thorough info" << endl;
		cout << endl;
	}

	void
	Config :: init ()
	{
		Ancestor_ :: init ();
		programName() << "smm";
		programDescription() << "smm (Simplified MetaMath) verifier.";
	}

	bool
	Config :: checkPaths()
	{
		if (getSource().getExtension() != smmExtension()) {
			cout << "wrong source extension *." << getSource().getExtension() << std :: endl;
			cout << "Should be *." << smmExtension() << endl;
			exit_ = true;
			error_ = true;
			return false;
		}
		return Ancestor_ :: Paths :: checkPaths();
	}
	bool
	Config :: analyseArguments()
	{
		if (showHelp()) {
			showUsageMessage();
			return false;
		}
		if (!checkPaths()) {
			return false;
		}
		if (exit()) {
			return false;
		}
		return true;
	}

	/*************************************
	 *		Static private attributes
	 *************************************/

	bool Config :: keepChecking_ = false;
	bool Config :: showStack_ = false;
	bool Config :: noLabels_ = false;
	bool Config :: asciiOnly_ = false;

	// info output options
	bool Config :: showTimings_ = false;
	bool Config :: showMath_ = false;
	bool Config :: showVolume_ = false;
}
}

#endif /*SMM_AUXILIARY_CONFIG_CPP_*/
