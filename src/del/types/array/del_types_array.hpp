/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_types_array.hpp                                      */
/* Description:     basic array types                                        */
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
namespace array {

	using nstd :: container :: Array;

	typedef
		Array
		<
			bool,
			storage :: ByValue,
			allocator :: Heap
		>
		Bool;
}
}



