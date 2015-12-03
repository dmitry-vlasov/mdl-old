/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_undefined_Empty.hpp                            */
/* Description:     undefined empty type value                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_TYPE_UNDEFINED_EMPTY_HPP_
#define NSTD_TYPE_UNDEFINED_EMPTY_HPP_

#include "type/constant/nstd_type_constant_Empty.hpp"

namespace nstd {
namespace type {
namespace undefined {

template<class T>
class Empty {
};

template<>
class Empty<type :: Empty> {
public :
	static type :: Empty getValue () {
		return type :: Empty();
	}
	static const bool isUndefined (const type :: Empty) {
		return true;
	}
};

}
}
}

#endif /*NSTD_TYPE_UNDEFINED_EMPTY_HPP_*/
