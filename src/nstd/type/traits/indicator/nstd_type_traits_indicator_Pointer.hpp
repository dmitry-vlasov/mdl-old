/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_traits_indicator_Pointer.hpp                   */
/* Description:     pointer type indicator                                   */
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
	 *		pointer types
	 ****************************/

	template<class T> 
	struct Pointer {
		enum { result = false };
		typedef 
			type :: Null 
			PointeeType; 
	};

	template<class T> 
	struct Pointer<T*> {
		enum { result = true };
		typedef T PointeeType; 
	};

	template<class T> 
	struct Pointer<const T*> {
		enum { result = true };
		typedef T PointeeType; 
	};
	
	template<class T> 
	struct Pointer<T* const> {
		enum { result = true };
		typedef T PointeeType; 
	};
	
	template<class T> 
	struct Pointer<const T* const> {
		enum { result = true };
		typedef T PointeeType; 
	};
}
}
}
}


