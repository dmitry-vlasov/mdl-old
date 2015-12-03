/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_types_index.hpp                                       */
/* Description:     index types                                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_TYPES_INDEX_HPP_
#define MM_TYPES_INDEX_HPP_

namespace mm {
namespace index {
	// Index type for source files
	typedef
		nstd :: U_int32_t
		File;
	// Index type for literals in expressions
	typedef
		nstd :: U_int32_t
		Literal;
	typedef
		nstd :: U_int32_t
		Type;
	// Index type for assertions
	typedef
		nstd :: U_int32_t
		Assertion;
	// Index type for hypothesis and propositions
	typedef
		nstd :: U_int32_t
		Arity;
	// Index type for proof steps
	typedef
		nstd :: U_int32_t
		Step;
}
}

#include "types/index/undefined/mm_types_index_undefined.hpp"

#endif /*MM_TYPES_INDEX_HPP_*/
