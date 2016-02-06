/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_auxiliary_Config.hpp                                 */
/* Description:     static class for command line arguments                  */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "smm/types/smm_types.hpp"
#include "smm/auxiliary/smm_auxiliary.dpp"

namespace smm {
namespace auxiliary {

// Class which contain boolean flags and string parameters for smm.
class Config : public nstd :: Config<Config> {
	typedef nstd :: Config<Config> Ancestor_;
public :
	// The checker will show the content of the proof stack at proof errors.
	static bool keepChecking ();
	// The checker will show the content of the proof stack at proof errors.
	static bool showStack();
	// do not use name table for assertion labels
	static bool noLabels();
	// do not allow non-ascii characters in source code
	static bool asciiOnly();

	// info output options
	static bool showTimings();
	static bool showMath();
	static bool showVolume();

	static const char* smmExtension();

	static bool proceed (const int argCount, const char* argValues[]);
	static bool proceedStringOption (const char*, const int, const char* [], int&);
	static bool proceedOneCharOption (const char*, const int, const char* [], int&);

	static void release();
	static Size_t getVolume();

private :
	// Shows the options usage message.
	static void showUsageMessage();
	static void init ();

	static bool checkPaths();
	static bool analyseArguments();

	static bool keepChecking_;
	static bool showStack_;
	static bool noLabels_;
	static bool asciiOnly_;

	static bool showTimings_;
	static bool showMath_;
	static bool showVolume_;
};

}
}

#include "smm/auxiliary/smm_auxiliary_Config.ipp"


