/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_types_value.hpp                                      */
/* Description:     basic types for values                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace value {

	// Basic type for any integer
	typedef
		nstd :: Int32_t
		Integer;
	// type for 64 bit integer values
	typedef
		nstd :: Int64_t
		Long;
	// Type for real numbers.
	typedef
		double
		Real;
	// Value type for identificator names
	typedef
		nstd :: U_int32_t
		Name;
	// Value type for literals - symbols in expressions
	typedef
		nstd :: U_int32_t
		Literal;
	// kind is a small type for distinction of objects
	typedef
		nstd :: U_int8_t
		Kind;
}
}

#include "mdl/types/value/undefined/mdl_types_value_undefined.hpp"

namespace mdl {
namespace value {

	const Real
		LARGE = 1E3;
	const Real
		VERY_LARGE = 1E6;
	const Real
		EXTREMELY_LARGE = 1E12;
	const Real
		ALMOST_ZERO = 1E-9;
}
}


