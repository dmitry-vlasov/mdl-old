/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_types_indexes.hpp                                    */
/* Description:     basic types for indexes                                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace index {
	// Index type for source files
	typedef
		nstd :: U_int32_t
		File;
	// Index type for identificator Names
	typedef
		nstd :: U_int32_t
		Name;
	// Index type for literals in expressions
	typedef
		nstd :: U_int16_t
		Literal;
	// Index type for assertions
	typedef
		nstd :: U_int32_t
		Assertion;
	// Index type for hypothesis and propositions
	typedef
		nstd :: U_int16_t
		Arity;
	// Index type for proof steps
	typedef
		nstd :: U_int32_t
		Step;
	typedef
		nstd :: U_int16_t
		Type;
	typedef
		nstd :: U_int16_t
		Rule;
	typedef
		nstd :: U_int16_t
		Constant;
	typedef
		nstd :: U_int16_t
		Theory;
	// Index type for forms
	typedef
		nstd :: U_int32_t
		Form;
}
}

#include "mdl/types/index/undefined/mdl_types_index_undefined.hpp"


