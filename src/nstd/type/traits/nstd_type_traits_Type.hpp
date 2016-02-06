/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_traits_Type.hpp                                */
/* Description:     general type traits                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "type/traits/nstd_type_traits_Bool.hpp"
#include "type/traits/nstd_type_traits_Empty.hpp"
#include "type/traits/nstd_type_traits_Floating.hpp"
#include "type/traits/nstd_type_traits_Integer.hpp"
#include "type/traits/nstd_type_traits_Null.hpp"
#include "type/traits/nstd_type_traits_Pointer.hpp"
#include "type/traits/nstd_type_traits_Void.hpp"

namespace nstd {
namespace type {
namespace traits {

template<class T>
class Type : 
	public Pointer<T>,
	public Floating<T>,
	public Integer<T>, 
	public Null<T>,  
	public Empty<T>,
	public Bool<T>,
	public Void<T> {
public :
	enum {
		is_object = 
			!Pointer<T> :: is_pointer   &&
			!Floating<T> :: is_floating &&
			!Integer<T> :: is_integer   &&
			!Null<T> :: is_null         &&
			!Empty<T> :: is_empty       &&
			!Bool<T> :: is_bool
	};
};

}
}
}


