/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_Switch.hpp                                     */
/* Description:     int selector metafunction                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "type/nstd_type.dpp"

namespace nstd {
namespace type {

template<int X, int Y>
class Switch<true, X, Y> {
public :
	enum {
		result_ = X
	};
};

template<int X, int Y>
class Switch<false, X, Y> {
public :
	enum {
		result_ = Y
	};
};

}
}


