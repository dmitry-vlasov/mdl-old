/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_types_vector.hpp                                     */
/* Description:     basic vector types                                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_TYPES_VECTOR_HPP_
#define MDL_TYPES_VECTOR_HPP_

#include "mdl/types/storage/mdl_types_storage.hpp"
#include "mdl/types/value/mdl_types_value.hpp"

namespace mdl {
namespace vector {

	using nstd :: container :: Bit;
	using nstd :: container :: Vector;
	typedef
		Vector<mdl :: String, storage :: ByPointer, allocator :: Heap>
		String;
}
}

#include "mdl/types/vector/index/mdl_types_vector_index.hpp"
#include "mdl/types/vector/value/mdl_types_vector_value.hpp"

#endif /*MDL_TYPES_VECTOR_HPP_*/

