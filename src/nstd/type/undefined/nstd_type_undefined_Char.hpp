/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_undefined_Char.hpp                             */
/* Description:     undefined char value                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_TYPE_UNDEFINED_CHAR_HPP_
#define NSTD_TYPE_UNDEFINED_CHAR_HPP_

#include "type/traits/nstd_type_traits_Type.hpp"

namespace nstd {
namespace type {
namespace undefined {

template<class T>
class Char {
};

template<>
class Char<char> {
public :
	static const char getValue () {
		return chars :: NULL_CHAR;
	}

	static const bool isUndefined (const char value) {
		return (value == chars :: NULL_CHAR);
	}
};

}
}
}

#endif /*NSTD_TYPE_UNDEFINED_CHAR_HPP_*/
