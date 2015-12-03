/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_list_Replace.hpp                               */
/* Description:     replace operation for type list                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_TYPE_LIST_REPLACE_HPP_
#define NSTD_TYPE_LIST_REPLACE_HPP_

#include "type/constant/nstd_type_constant.hpp"
#include "type/list/nstd_type_list.dpp"
#include "type/list/nstd_type_list_List.hpp"

namespace nstd {
namespace type {
namespace list {

template<class S_1, class S_2>
struct Replace<Null, S_1, S_2> {
	typedef Null Result;
};

template<class H, class T, class S_2>
struct Replace<List<H, T>, H, S_2> {
	typedef 
		List<S_2, T> 
		Result;
};

template<class H, class T, class S_1, class S_2>
struct Replace<List<H, T>, S_1, S_2> {
	typedef 
		List<H, typename Replace<T, S_1, S_2> :: Result> 
		Result;
};

}
}
}

#endif /*NSTD_TYPE_LIST_REPLACE_HPP_*/
