/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_traits_Void.hpp                                */
/* Description:     Null type traits                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_TYPE_TRAITS_VOID_HPP_
#define NSTD_TYPE_TRAITS_VOID_HPP_

#include "type/traits/indicator/nstd_type_traits_indicator_void.hpp"

namespace nstd {
namespace type {
namespace traits {

template<class T>
class Void {
public :
	enum { 
		is_void = indicator :: void_<T> :: result
	};
};

}
}
}

#endif /*NSTD_TYPE_TRAITS_VOID_HPP_*/