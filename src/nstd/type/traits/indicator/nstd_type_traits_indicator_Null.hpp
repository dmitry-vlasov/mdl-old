/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_traits_indicator_Null.hpp                      */
/* Description:     Null type indicator                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "type/constant/nstd_type_constant.hpp"

namespace nstd {
namespace type {
namespace traits {
namespace indicator {

	/****************************
	 *		Null type
	 ****************************/

	template<class T> 
	struct Null {
		enum { result = false }; 
	};
	template<> 
	struct Null<type :: Null> {
		enum { result = true }; 
	};
}
}
}
}


