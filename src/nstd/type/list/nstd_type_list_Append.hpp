/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_list_Append.hpp                                */
/* Description:     append list operation                                    */
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

template<>
struct Append<Null, Null> {
	typedef Null Result;
};

template<class C>
struct Append<Null, C> {
	typedef 
		List<C, Null> 
		Result;
};

template<class H, class T>
struct Append<Null, List<H, T> > {
	typedef 
		List<H, T> 
		Result;
};

template<class H, class T, class C>
struct Append<List<H, T>, C> {
	typedef 
		List<H, typename Append<T, C> :: Result> 
		Result;
};

}
}
}


