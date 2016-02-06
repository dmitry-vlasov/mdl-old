/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_types_vector.hpp                                     */
/* Description:     basic vector types                                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "types/storage/del_types_storage.hpp"
#include "types/value/del_types_value.hpp"

namespace del {
namespace vector {

	using nstd :: container :: Bit;
	using nstd :: container :: Vector;

	typedef
		vector :: Vector
		<
			del :: String,
			storage :: ByPointer,
			allocator :: Heap
		>
		String;

	typedef
		vector :: Vector
		<
			bool,
			storage :: ByValue,
			allocator :: Heap
		>
		Bool;
}
}

#include "types/vector/index/del_types_vector_index.hpp"
#include "types/vector/value/del_types_vector_value.hpp"



