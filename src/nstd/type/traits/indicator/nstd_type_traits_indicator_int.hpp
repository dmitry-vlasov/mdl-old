/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_traits_indicator_int.hpp                       */
/* Description:     int type indicator                                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_TYPE_TRAITS_INDICATOR_INT_HPP_
#define NSTD_TYPE_TRAITS_INDICATOR_INT_HPP_

namespace nstd {
namespace type {
namespace traits {
namespace indicator {

	/****************************
	 *		int types
	 ****************************/
	
	template<class T> 
	struct int_ {
		enum { result = false }; 
	};
	template<> 
	struct int_<int> {
		enum { result = true }; 
	};
	
	template<class T> 
	struct unsigned_int_ {
		enum { result = false }; 
	};
	template<> 
	struct unsigned_int_<unsigned int> {
		enum { result = true }; 
	};

}
}
}
}

#endif /*NSTD_TYPE_TRAITS_INDICATOR_INT_HPP_*/
