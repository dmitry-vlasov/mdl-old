/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_traits_indicator_char.hpp                      */
/* Description:     char type indicator                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_TYPE_TRAITS_INDICATOR_CHAR_HPP_
#define NSTD_TYPE_TRAITS_INDICATOR_CHAR_HPP_

namespace nstd {
namespace type {
namespace traits {
namespace indicator {

	/****************************
	 *		char types
	 ****************************/
	
	template<class T> 
	struct char_ {
		enum { result = false };
	};
	template<> 
	struct char_<char> {
		enum { result = true };
	};
	
	template<class T> 
	struct unsigned_char_ {
		enum { result = false }; 
	};
	template<> 
	struct unsigned_char_<unsigned char> {
		enum { result = true }; 
	};
}
}
}
}

#endif /*NSTD_TYPE_TRAITS_INDICATOR_CHAR_HPP_*/
