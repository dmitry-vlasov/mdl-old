/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_traits_Floating.hpp                            */
/* Description:     floating type traits                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "type/traits/indicator/nstd_type_traits_indicator_floatings.hpp"

namespace nstd {
namespace type {
namespace traits {

template<class T>
class Floating {
public :
	enum { 
		is_float = indicator :: float_<T> :: result
	};
	enum { 
		is_double = indicator :: double_<T> :: result
	};
	
	enum { 
		is_floating =
		is_float || is_double
	};
};

}
}
}


