/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_list_Erase.hpp                                 */
/* Description:     erase operation for type list                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "type/constant/nstd_type_constant.hpp"
#include "type/list/nstd_type_list.dpp"
#include "type/list/nstd_type_list_List.hpp"

namespace nstd {
namespace type {
namespace list {

template<class C>
struct Erase<Null, C> {
	typedef Null Result;
};

template<class C, class T>
struct Erase<List<C, T>, C> {
	typedef T Result;
};

template<class H, class T, class C>
struct Erase<List<H, T>, C> {
	typedef 
		List<H, typename Erase<T, C> :: Result> 
		Result;
};

}
}
}


