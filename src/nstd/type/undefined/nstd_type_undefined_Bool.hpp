/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_undefined_Bool.hpp                             */
/* Description:     undefined bool value                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_TYPE_UNDEFINED_BOOL_HPP_
#define NSTD_TYPE_UNDEFINED_BOOL_HPP_

#include "type/traits/nstd_type_traits_Type.hpp"

namespace nstd {
namespace type {
namespace undefined {

template<class T>
class Bool {
};

template<>
class Bool<bool> {
public :
	static const bool getValue () {
		return false;
	}
	static const bool isUndefined (const bool value) {
		return (value == false);
	}
};

}
}
}

#endif /*NSTD_TYPE_UNDEFINED_BOOL_HPP_*/
