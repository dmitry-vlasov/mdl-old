/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_type_undefined_Type.hpp                             */
/* Description:     general undefined type value                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "type/undefined/nstd_type_undefined_Bool.hpp"
#include "type/undefined/nstd_type_undefined_Char.hpp"
#include "type/undefined/nstd_type_undefined_Empty.hpp"
#include "type/undefined/nstd_type_undefined_Floating.hpp"
#include "type/undefined/nstd_type_undefined_Integer.hpp"
#include "type/undefined/nstd_type_undefined_Object.hpp"
#include "type/undefined/nstd_type_undefined_Pointer.hpp"
#include "type/undefined/nstd_type_undefined_Void.hpp"

namespace nstd {
namespace type {
namespace undefined {

template<class T>
class Type :
	public Void<T>,
	public Bool<T>,
	public Empty<T>,
	public Char<T>,
	public Floating
	<
		T,
		traits :: Type<T> :: is_floating
	>,
	public Integer
	<
		T,
		traits :: Type<T> :: is_integer &&
		!traits :: Type<T> :: is_char &&
		!traits :: Type<T> :: is_pointer
	>,
	public Pointer<T, traits :: Type<T> :: is_pointer>,
	public Object<T, traits :: Type<T> :: is_object> {
};

}
}
}



