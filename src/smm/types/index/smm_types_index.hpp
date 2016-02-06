/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_types_index.hpp                                      */
/* Description:     index types                                              */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace smm {
namespace index {
	// Index type for source files
	typedef
		nstd :: U_int32_t
		File;
	// Index type for literals in expressions
	typedef
		nstd :: U_int32_t
		Literal;
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

#include "smm/types/index/undefined/smm_types_index_undefined.hpp"


