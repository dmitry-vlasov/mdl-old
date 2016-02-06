/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_traits_Empty.hpp                               */
/* Description:     Empty type traits                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "type/traits/indicator/nstd_type_traits_indicator_Empty.hpp"

namespace nstd {
namespace type {
namespace traits {

template<class T>
class Empty {
public :
	enum { 
		is_empty = indicator :: Empty<T> :: result 
	};
};

}
}
}


