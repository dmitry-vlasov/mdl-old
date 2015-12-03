/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_list_Length.hpp                                */
/* Description:     length operation for type list                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_TYPE_LIST_LENGTH_HPP_
#define NSTD_TYPE_LIST_LENGTH_HPP_

#include "type/constant/nstd_type_constant.hpp"
#include "type/list/nstd_type_list.dpp"
#include "type/list/nstd_type_list_List.hpp"

namespace nstd {
namespace type {
namespace list {

template<class T>
struct Length {
	typedef 
		typename T :: Tail 
		Tail;
	enum { result = 1 + Length<Tail> :: result };
};

template<>
struct Length<Null> {
	enum { result = 0 };
};

}
}
}

#endif /*NSTD_TYPE_LIST_LENGTH_HPP_*/
