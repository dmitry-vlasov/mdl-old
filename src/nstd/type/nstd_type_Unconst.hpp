/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_Unconst.hpp                                    */
/* Description:     type unconst metafunction                                */
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
struct Unconst {
	enum { is_const = false };
	typedef T Result_;
};

template<class T>
struct Unconst<const T> {
	enum { is_const = true };
	typedef T Result_;
};

}
}


