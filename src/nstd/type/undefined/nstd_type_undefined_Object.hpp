/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_undefined_Object.hpp                           */
/* Description:     undefined object value                                   */
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
class Object<T, true> {
public :
	static const T& getValue () {
		return undefined_;
	}
	
	static const bool isUndefined (const T& value) {
		return (value == undefined_);
	}
	
private :
	static const T undefined_;
};

template<class T> 
const T
	Object<T, true> :: undefined_;

template<class T>
class Object<T, false> {
};

}
}
}


