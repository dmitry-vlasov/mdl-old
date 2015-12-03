/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_traits_indicator_Empty.hpp                     */
/* Description:     Empty type indicator                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_TYPE_TRAITS_INDICATOR_EMPTY_HPP_
#define NSTD_TYPE_TRAITS_INDICATOR_EMPTY_HPP_

#include "type/constant/nstd_type_constant.hpp"

namespace nstd {
namespace type {
namespace traits {
namespace indicator {

	/****************************
	 *		Empty type
	 ****************************/

	template<class T> 
	struct Empty {
		enum { result = false }; 
	};
	template<> 
	struct Empty<type :: Empty> {
		enum { result = true }; 
	};
}
}
}
}

#endif /*NSTD_TYPE_TRAITS_INDICATOR_EMPTY_HPP_*/
