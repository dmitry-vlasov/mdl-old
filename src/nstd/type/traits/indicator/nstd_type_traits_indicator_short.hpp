/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_traits_indicator_short.hpp                     */
/* Description:     short type indicator                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_TYPE_TRAITS_INDICATOR_SHORT_HPP_
#define NSTD_TYPE_TRAITS_INDICATOR_SHORT_HPP_

namespace nstd {
namespace type {
namespace traits {
namespace indicator {

	/****************************
	 *		short types
	 ****************************/
	
	template<class T> 
	struct short_ {
		enum { result = false }; 
	};
	template<> 
	struct short_<short> {
		enum { result = true }; 
	};
	
	template<class T> 
	struct unsigned_short_ {
		enum { result = false }; 
	};
	template<> 
	struct unsigned_short_<unsigned short> {
		enum { result = true }; 
	};
}
}
}
}

#endif /*NSTD_TYPE_TRAITS_INDICATOR_SHORT_HPP_*/
