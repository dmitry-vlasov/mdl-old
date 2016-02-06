/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_undefined_Void.hpp                             */
/* Description:     undefined void value                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "type/traits/nstd_type_traits_Type.hpp"

namespace nstd {
namespace type {
namespace undefined {

template<class T>
class Void {
};

template<>
class Void<void> {
public :
	static void getValue() {
	}
	static bool isUndefined() {
		return true;
	}
};

}
}
}


