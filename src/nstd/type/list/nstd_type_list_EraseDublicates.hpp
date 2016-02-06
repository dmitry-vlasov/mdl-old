/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_list_EraseDublicates.hpp                       */
/* Description:     erase dublicates operation for type list                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "type/list/nstd_type_list_Erase.hpp"
#include "type/list/nstd_type_list.dpp"

namespace nstd {
namespace type {
namespace list {

template<>
struct EraseDublicates<Null> {
	typedef Null Result;
};

template<class H, class T>
struct EraseDublicates<List<H, T> > {
private :
	typedef
		typename EraseDublicates<T> :: Result
		ErasedTail_1;
	typedef
		typename Erase<ErasedTail_1, H> :: Result
		ErasedTail_2;
public :
	typedef 
		List<H, ErasedTail_2>
		Result;
};

}
}
}


