/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_traits_indicator_digits.hpp                    */
/* Description:     digits type indicator                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_TYPE_TRAITS_INDICATOR_DIGITS_HPP_
#define NSTD_TYPE_TRAITS_INDICATOR_DIGITS_HPP_

namespace nstd {
namespace type {
namespace traits {
namespace indicator {

	/****************************
	 *		digits in int types
	 ****************************/

	template<class T> 
	struct digits_ {
		enum { result = -1 };
	};

	template<> 
	struct digits_<U_int8_t> {
		enum { result = 8 };
	};	
	template<> 
	struct digits_<U_int16_t> {
		enum { result = 16 }; 
	};
	template<> 
	struct digits_<U_int32_t> {
		enum { result = 32 }; 
	};
	template<> 
	struct digits_<U_int64_t> {
		enum { result = 64 }; 
	};

	template<> 
	struct digits_<Int8_t> {
		enum { result = 8 };
	};	
	template<> 
	struct digits_<Int16_t> {
		enum { result = 16 }; 
	};
	template<> 
	struct digits_<Int32_t> {
		enum { result = 32 }; 
	};
	template<> 
	struct digits_<Int64_t> {
		enum { result = true }; 
	};
}
}
}
}

#endif /*NSTD_TYPE_TRAITS_INDICATOR_DIGITS_HPP_*/
