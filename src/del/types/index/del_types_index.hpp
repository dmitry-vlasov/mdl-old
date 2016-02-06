/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_types_indexes.hpp                                    */
/* Description:     basic types for indexes                                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace del {
namespace index {
	// Index type for source files
	typedef
		nstd :: U_int32_t
		File;
	// Index type for relation names
	typedef
		nstd :: U_int32_t
		Relation;
	// Index type for theories
	typedef
		nstd :: U_int32_t
		Theory;
	// Index type for signatures
	typedef
		nstd :: U_int32_t
		Signature;
	// Index type for propositional variables
	typedef
		nstd :: U_int32_t
		Variable;
}
}

#include "types/index/undefined/del_types_index_undefined.hpp"


