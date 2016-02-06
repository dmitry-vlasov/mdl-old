/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_Equality.hpp                                   */
/* Description:     type equality metafunction                               */
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

template<class X, class Y>
class Equality {
public :
	enum { result = false };
};

template<class X>
class Equality<X, X> {
public :
	enum { result = true };
};

}
}


