/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_config_option_Path.cpp                              */
/* Description:     config option for path                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {
namespace config {
namespace option {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Path :: Path
	(
		const char* cmdString,
		const char* usageMessage,
		const char  cmdChar,
		const Path_& defaultPath,
		const int   largeIndent
	) :
	Option_ (defaultPath, cmdString, usageMessage, cmdChar, largeIndent) {
	}
	inline
	Path :: ~ Path() {
	}

	const Path :: Path_&
	Path :: getPath() const {
		return Option_ :: getValue();
	}
	inline void
	Path :: setPath (const Path_& path) {
		Option_ :: value() = path;
	}

	inline bool
	Path :: proceedStringOption (const char* opt, const int argCount, const char* argValues[], int& i) {
		return Option_ :: proceedStringOption (opt, argCount, argValues, i);
	}
	inline bool
	Path :: proceedOneCharOption (const char* opt, const int argCount, const char* argValues[], int& i) {
		return Option_ :: proceedOneCharOption (opt, argCount, argValues, i);
	}

	template<class S>
	inline void
	Path :: showUsageMessage (S& os) const {
		Option_ :: showUsageMessage(os);
	}
	template<class S>
	inline void
	Path :: showOptionValues (S& os) const {
		Option_ :: showOptionValues(os);
	}

	void
	Path :: commitSuicide() {
		delete this;
	}
	inline Size_t
	Path :: getVolume() const
	{
		Size_t volume = 0;
		volume += Option_ :: getVolume();
		return volume;
	}
	inline Size_t
	Path :: getSizeOf() const {
		return sizeof (Path);
	}
	template<class S>
	inline void
	Path :: show (S& string) const {
		Option_ :: show<S> (string);
	}

	/****************************
	 *		Private members
	 ****************************/
}
}
}


