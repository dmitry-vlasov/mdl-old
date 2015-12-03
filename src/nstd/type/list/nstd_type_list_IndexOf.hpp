/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_list_IndexOf.hpp                               */
/* Description:     search operation for type list                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_TYPE_LIST_INDEX_OF_HPP_
#define NSTD_TYPE_LIST_INDEX_OF_HPP_

#include "type/constant/nstd_type_constant.hpp"
#include "type/list/nstd_type_list.dpp"
#include "type/list/nstd_type_list_List.hpp"

namespace nstd {
namespace type {
namespace list {

template<class C>
struct IndexOf<Null, C> {
	enum { 
		result = -1 
	};
};

template<class T, class C>
struct IndexOf<List<C, T>, C> {
	enum { 
		result = 0 
	};
};

template<class H, class T, class C>
struct IndexOf<List<H, T>, C> {
private :
	enum { 
		ind = IndexOf<T, C> :: result 
	};
public :
	enum { 
		result = 
			(ind == -1) ? 
				-1 : 
				1 + ind
	};
};

}
}
}

#endif /*NSTD_TYPE_LIST_INDEX_OF_HPP_*/
