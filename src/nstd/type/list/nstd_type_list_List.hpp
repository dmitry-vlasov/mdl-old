/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_list_List.hpp                                  */
/* Description:     type list                                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {
namespace type {
namespace list {

template<class H, class T> 
struct List {
	typedef H Head;
	typedef T Tail;
};

}
}
}


