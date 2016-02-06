/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_list_ReplaceAll.hpp                            */
/* Description:     relpace all operation for type list                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "type/constant/nstd_type_constant.hpp"
#include "type/list/nstd_type_list_List.hpp"

namespace nstd {
namespace type {
namespace list {

template<class S_1, class S_2>
struct ReplaceAll<Null, S_1, S_2> {
	typedef Null Result;
};

template<class H, class T, class S_2>
struct ReplaceAll<List<H, T>, H, S_2> {
	typedef 
		List<S_2, typename ReplaceAll<T, H, S_2> :: Result>  
		Result;
};

template<class H, class T, class S_1, class S_2>
struct ReplaceAll<List<H, T>, S_1, S_2> {
	typedef 
		List<H, typename ReplaceAll<T, S_1, S_2> :: Result> 
		Result;
};

}
}
}


