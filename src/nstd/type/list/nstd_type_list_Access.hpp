/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_list_Access.hpp                                */
/* Description:     access template to the type list                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_TYPE_LIST_ACCESS_HPP_
#define NSTD_TYPE_LIST_ACCESS_HPP_

#include "type/list/nstd_type_list.dpp"
#include "type/list/nstd_type_list_List.hpp"

namespace nstd {
namespace type {
namespace list {

template<class H, class T>
struct Access<List <H, T>, 0> {
	typedef H Result;
};

template<class H, class T, int i>
struct Access<List<H, T>, i> {
	typedef 
		typename Access<T, i - 1> :: Result 
		Result;
};

}
}
}

#endif /*NSTD_TYPE_LIST_ACCESS_HPP_*/
