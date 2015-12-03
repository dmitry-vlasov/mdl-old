/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_traits_Pointer.hpp                             */
/* Description:     pointer type traits                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_TYPE_TRAITS_POINTER_HPP_
#define NSTD_TYPE_TRAITS_POINTER_HPP_

#include "type/traits/indicator/nstd_type_traits_indicator_Pointer.hpp"

namespace nstd {
namespace type {
namespace traits {

template<class T>
class Pointer {
public :
	enum { 
		is_pointer = indicator :: Pointer<T> :: result
	};
	typedef 
		typename indicator :: Pointer<T> :: PointeeType 
		PointeeType;
};

}
}
}

#endif /*NSTD_TYPE_TRAITS_POINTER_HPP_*/
