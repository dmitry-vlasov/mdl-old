/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_Unpointer.hpp                                  */
/* Description:     type unpointer metafunction                              */
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

template<class T>
struct Unpointer {
	enum { is_pointer = false };
	typedef T Result_;
};

template<class T>
struct Unpointer<T*> {
	enum { is_pointer = true };
	typedef T Result_;
};

}
}


