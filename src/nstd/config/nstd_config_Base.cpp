/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_config_Base.cpp                                     */
/* Description:     base config class                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONFIG_BASE_CPP_
#define NSTD_CONFIG_BASE_CPP_

namespace nstd {
namespace config {

	/****************************
	 *		Public members
	 ****************************/

	inline bool
	Base :: exit() {
		return exit_;
	}
	inline bool
	Base :: error() {
		return error_;
	}
	inline bool
	Base :: getUpdate() {
		return update_;
	}
	inline void
	Base :: setUpdate(const bool value) {
		update_ = value;
	}
	inline void
	Base :: setInExternalConfig(const bool value) {
		inExternalConfig_ = value;
	}


	/****************************
	 *		Protected members
	 ****************************/

	inline Size_t
	Base :: getVolume() {
		return 0;
	}
	Size_t
	Base :: stringLength (const char string[])
	{
		Size_t length = 0;
		while (string [length] != '\0') {
			length ++;
		}
		return length;
	}

	bool
	Base :: equalStrings (const char* str_1,  const char* str_2)
	{
		while (*str_2 != 0) {
			if (*str_1 != *str_2) {
				return false;
			}
			str_1 ++;
			str_2 ++;
		}
		return (*str_1 == 0);
	}

	void
	Base :: copyString (const char* const str_1, char* const str_2)
	{
		const Size_t
			length_1 = stringLength (str_1);

		const Size_t
			length_2 = stringLength (str_2);

		for (Size_t i = 0; i < length_1; i ++) {
			str_2 [i] = str_1 [i];
		}
		for (Size_t i = length_1; i < length_2; i++) {
			str_2 [i] = '\0';
		}
	}

	bool
	Base :: stringIsInArray(const char* string, const char* array[], const int n)
	{
		for (int i = 0; i < n; ++ i) {
			const char* s = array[i];
			if (equalStrings(string, s)) {
				return true;
			}
		}
		return false;
	}

	/************************************
	 *		Static private attributes
	 ************************************/

	bool Base :: exit_   = false;
	bool Base :: error_  = false;
	bool Base :: update_ = false;
	bool Base :: inExternalConfig_ = false;
}
}

#endif /*NSTD_CONFIG_BASE_CPP_*/
