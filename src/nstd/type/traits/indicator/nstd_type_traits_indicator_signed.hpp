/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_traits_indicator_signed.hpp                    */
/* Description:     signed type indicator                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_TYPE_TRAITS_INDICATOR_SIGNED_HPP_
#define NSTD_TYPE_TRAITS_INDICATOR_SIGNED_HPP_

namespace nstd {
namespace type {
namespace traits {
namespace indicator {

	/****************************
	 *		signed / unsigned
	 ****************************/
	
	template<class T> 
	struct unsigned_ {
		enum { result = false };
	};
	template<class T> 
	struct signed_ {
		enum { result = false };
	};
	
	/*  unsigned int types */
	
	template<> 
	struct unsigned_<U_int8_t> {
		enum { result = true };
	};	
	template<> 
	struct unsigned_<U_int16_t> {
		enum { result = true }; 
	};
	template<> 
	struct unsigned_<U_int32_t> {
		enum { result = true }; 
	};
	template<> 
	struct unsigned_<U_int64_t> {
		enum { result = true }; 
	};

	/*  signed int types */
	
	template<> 
	struct signed_<Int8_t> {
		enum { result = true };
	};	
	template<> 
	struct signed_<Int16_t> {
		enum { result = true }; 
	};
	template<> 
	struct signed_<Int32_t> {
		enum { result = true }; 
	};
	template<> 
	struct signed_<Int64_t> {
		enum { result = true }; 
	};
}
}
}
}

#endif /*NSTD_TYPE_TRAITS_INDICATOR_SIGNED_HPP_*/
