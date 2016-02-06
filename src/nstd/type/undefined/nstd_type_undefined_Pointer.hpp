/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_undefined_Pointer.hpp                          */
/* Description:     undefined pointer value                                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "type/constant/nstd_type_constant.hpp"
#include "type/traits/nstd_type_traits_Type.hpp"
#include "type/undefined/nstd_type_undefined.dpp"

namespace nstd {
namespace type {
namespace undefined {

template<class T>
class Pointer<T, true> {
public :
	static const T getValue () {
		return NULL;
	}
	
	static const bool isUndefined (const T value) {
		return (value == NULL);
	}
};

template<class T>
class Pointer<T, false> {
};

}
}
}


