/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_undefined_Defined.hpp                          */
/* Description:     defined template metafunction                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "type/undefined/nstd_type_undefined_Type.hpp"

namespace nstd {
namespace type {
namespace undefined {

template<class T>
class Defined {
public :
	const bool isUndefined() const {
		const T& x = static_cast<const T&> (*this);
		return Type<T> :: isUndefined (x);
	}
};

}
}
}


