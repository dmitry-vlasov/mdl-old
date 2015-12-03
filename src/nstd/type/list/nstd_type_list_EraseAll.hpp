/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_list_EraseAll.hpp                              */
/* Description:     erase all operation for type list                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_TYPE_LIST_ERASE_ALL_HPP_
#define NSTD_TYPE_LIST_ERASE_ALL_HPP_

#include "type/constant/nstd_type_constant.hpp"
#include "type/list/nstd_type_list.dpp"
#include "type/list/nstd_type_list_List.hpp"

namespace nstd {
namespace type {
namespace list {

template<class C>
struct EraseAll<Null, C> {
	typedef Null Result;
};

template<class C, class T>
struct EraseAll<List<C, T>, C> {
	typedef 
		typename EraseAll<T, C> :: Result
		Result;
};

template<class H, class T, class C>
struct EraseAll<List<H, T>, C> {
	typedef 
		List<H, typename EraseAll<T, C> :: Result> 
		Result;
};

}
}
}

#endif /*NSTD_TYPE_LIST_ERASE_ALL_HPP_*/
