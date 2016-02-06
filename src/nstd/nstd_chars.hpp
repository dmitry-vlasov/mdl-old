/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_chars.hpp                                           */
/* Description:     char constants                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {
namespace chars {

	const char SLASH = '/';
	const char DOT = '.';
	const char BACK_SLASH = '\\';
	const char DIR_DELIMITER = SLASH;
	const char EXTENSION_DELIMITER = DOT;
	const char NEW_LINE = '\n';
	const char SPACE = ' ';
	const char TAB = '\t';
	const char UNDERLINE = '_';
	const char NULL_CHAR = '\0';
	const char BACKSPACE = '\b';
	const char HASH_KEY = '#';

	template<class S>
	void iterate (S& s, const char ch, const int k)
	{
		for (int i = 0; i < k; ++ i) {
			s << ch;
		}
	}
	template<class S>
	inline void shift (S& s, const int k) {
		iterate (s, TAB, k);
	}
}
}


