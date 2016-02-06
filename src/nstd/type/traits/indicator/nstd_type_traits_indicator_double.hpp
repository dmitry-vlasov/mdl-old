/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_traits_indicator_double.hpp                    */
/* Description:     double type indicator                                    */
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
	 *		double type
	 ****************************/
	
	template<class T> 
	struct double_ {
		enum { result = false }; 
	};
	template<> 
	struct double_<double> {
		enum { result = true }; 
	};
}
}
}
}


