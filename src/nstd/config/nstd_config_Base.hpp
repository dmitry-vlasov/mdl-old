/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_config_Base.hpp                                     */
/* Description:     base config class                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "config/nstd_config.dpp"

namespace nstd {
namespace config {

class Base {
public :
	static bool exit();
	static bool error();
	static bool getUpdate();
	static void setUpdate(const bool value = true);
	static void setInExternalConfig(const bool value = true);

	static Size_t getVolume();

	/// Checks iff two strings are equal.
	static bool equalStrings (const char*, const char*);
	/// Returns the length of a string.
	static Size_t stringLength (const char string[]);
	/// Copies first argument to the second argument.
	static void copyString (const char* const, char* const);

	static bool stringIsInArray(const char* string, const char* array[], const int n);

protected :
	/// Do not do any actions.
	static bool exit_;
	/// Inconsistent configuration.
	static bool error_;
	// do not change the config values, if they are not explicitly set.
	static bool update_;
	// at the moment using external configuration file.
	static bool inExternalConfig_;
};

}
}


