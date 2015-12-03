/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_undefined_Floating.hpp                         */
/* Description:     undefined floating value                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_TYPE_UNDEFINED_FLOATING_HPP_
#define NSTD_TYPE_UNDEFINED_FLOATING_HPP_

#include "type/traits/nstd_type_traits_Type.hpp"
#include "type/undefined/nstd_type_undefined.dpp"

namespace nstd {
namespace type {
namespace undefined {

template<class T>
class Floating<T, true> {
public :
	static const T getValue () {
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
Floating<T, true> :: undefined_ = 0;

template <class T>
class Floating<T, false> {
};

}
}
}

#endif /*NSTD_TYPE_UNDEFINED_FLOATING_HPP_*/
