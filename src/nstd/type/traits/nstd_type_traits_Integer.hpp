/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_traits_Integer.hpp                             */
/* Description:     integer type traits                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_TYPE_TRAITS_INTEGER_HPP_
#define NSTD_TYPE_TRAITS_INTEGER_HPP_

#include "type/traits/indicator/nstd_type_traits_indicator_integers.hpp"

namespace nstd {
namespace type {
namespace traits {

template<class T>
class Integer {
public :
	enum { 
		is_short = indicator :: short_<T> :: result 
	};
	enum { 
		is_unsigned_short = indicator :: unsigned_short_<T> :: result 
	};
	enum { 
		is_long = indicator :: long_<T> :: result 
	};
	enum { 
		is_unsigned_long = indicator :: unsigned_long_<T> :: result 
	};
	enum { 
		is_long_long = indicator :: long_long_<T> :: result 
	};
	enum { 
		is_unsigned_long_long = indicator :: unsigned_long_long_<T> :: result 
	};
	enum { 
		is_char = indicator :: char_<T> :: result 
	};
	enum { 
		is_unsigned_char = indicator :: unsigned_char_<T> :: result 
	};
	enum { 
		is_int = indicator :: int_<T> :: result 
	};
	enum { 
		is_unsigned_int = indicator :: unsigned_int_<T> :: result 
	};
	
	enum {
		is_signed = indicator :: signed_<T> :: result
	};
	enum {
		is_unsigned = indicator :: unsigned_<T> :: result
	};
	enum {
		digits = indicator :: digits_<T> :: result
	};
	
	enum { 
		is_integer = 
		is_short || is_unsigned_short || 
		is_long || is_unsigned_long ||
		is_long_long || is_unsigned_long_long ||  
		is_char || is_unsigned_char ||
		is_int || is_unsigned_int 
	};
};

}
}
}

#endif /*NSTD_TYPE_TRAITS_INTEGER_HPP_*/
