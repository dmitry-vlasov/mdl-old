/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_types_value.hpp                                      */
/* Description:     basic types for values                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_TYPES_VALUE_HPP_
#define DEL_TYPES_VALUE_HPP_

namespace del {
namespace value {

	// Basic type for any integer
	typedef
		nstd :: Int32_t
		Integer;

	// type for 64 bit integer values
	typedef
		nstd :: Int64_t
		Long;

	// Value type for relation names
	typedef
		nstd :: U_int32_t
		Relation;

	// Value type for theory names
	typedef
		nstd :: U_int32_t
		Theory;

	// Value type for signature names
	typedef
		nstd :: U_int32_t
		Signature;

	// Value type for propositional variables
	typedef
		nstd :: U_int32_t
		Variable;

	// Value type for signature symbols
	typedef
		nstd :: U_int32_t
		Symbol;
}
}

#include "types/value/undefined/del_types_value_undefined.hpp"

namespace del {
namespace value {

	const Variable
		TOP = Undefined<Variable> :: getValue() - 1;
}
}

#include "types/value/pair/del_types_value_pair.hpp"

#endif /*DEL_TYPES_VALUE_HPP_*/
