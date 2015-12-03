/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_traits_indicator_long_long.hpp                 */
/* Description:     long long type indicator                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_TYPE_TRAITS_INDICATOR_LONG_LONG_HPP_
#define NSTD_TYPE_TRAITS_INDICATOR_LONG_LONG_HPP_

namespace nstd {
namespace type {
namespace traits {
namespace indicator {

	/****************************
	 *		long long types
	 ****************************/
	
	template<class T> 
	struct long_long_ {
		enum { result = false }; 
	};
	template<> 
	struct long_long_<long long> {
		enum { result = true }; 
	};
	
	template<class T> 
	struct unsigned_long_long_ {
		enum { result = false }; 
	};
	template<> 
	struct unsigned_long_long_<unsigned long long> {
		enum { result = true }; 
	};
}
}
}
}

#endif /*NSTD_TYPE_TRAITS_INDICATOR_LONG_LONG_HPP_*/
