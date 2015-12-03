/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_list_Generators.hpp                            */
/* Description:     generators for type list                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_TYPE_LIST_GENERATORS_HPP_
#define NSTD_TYPE_LIST_GENERATORS_HPP_

#include "type/constant/nstd_type_constant.hpp"
#include "type/list/nstd_type_list.dpp"
#include "type/list/nstd_type_list_List.hpp"

namespace nstd {
namespace type {
namespace list {

template<class T_1>
struct Generator_1 {
	typedef T_1 Head;
	typedef Null Tail;
	typedef typename type :: List<Head, Tail> Result;
};

template<class T_1, class T_2>
struct Generator_2 {
	typedef T_1 Head;
	typedef typename Generator_1<T_2> :: Result Tail;
	typedef List<Head, Tail> Result;
};

template<class T_1, class T_2, class T_3>
struct Generator_3 {
	typedef T_1 Head;
	typedef typename Generator_2<T_2, T_3> :: Result Tail;
	typedef List<Head, Tail> Result;
};

template<class T_1, class T_2, class T_3, class T_4>
struct Generator_4 {
	typedef T_1 Head;
	typedef typename Generator_3<T_2, T_3, T_4> :: Result Tail;
	typedef List<Head, Tail> Result;
};

template<class T_1, class T_2, class T_3, class T_4, class T_5>
struct Generator_5 {
	typedef T_1 Head;
	typedef typename Generator_4<T_2, T_3, T_4, T_5> :: Result Tail;
	typedef List<Head, Tail> Result;
};

}
}
}

#endif /*NSTD_TYPE_LIST_GENERATORS_HPP_*/
