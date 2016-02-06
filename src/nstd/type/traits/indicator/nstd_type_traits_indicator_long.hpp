/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_traits_indicator_long.hpp                      */
/* Description:     long type indicator                                      */
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
namespace traits {
namespace indicator {

	/****************************
	 *		long types
	 ****************************/

	template<class T> 
	struct long_ {
		enum { result = false }; 
	};
	template<> 
	struct long_<long> {
		enum { result = true }; 
	};
	
	template<class T> 
	struct unsigned_long_ {
		enum { result = false }; 
	};
	template<> 
	struct unsigned_long_<unsigned long> {
		enum { result = true }; 
	};
}
}
}
}


