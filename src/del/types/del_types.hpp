/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_types.hpp                                            */
/* Description:     module for basic types                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_TYPES_HPP_
#define DEL_TYPES_HPP_

#include <nstd>

namespace del {
namespace type {
	using nstd :: type :: Alternator;
	using nstd :: type :: Equality;
	using nstd :: type :: Empty;
	using nstd :: type :: Selector;
	using nstd :: type :: Switch;
	using nstd :: type :: traits :: Type;
}
namespace memory {
	using nstd :: memory :: UsageMessage;
	using nstd :: memory :: Unit;
	using nstd :: memory :: exception :: OutOfMemory;
}
namespace system {
	using namespace nstd :: system;
}
	using nstd :: Counter;
	using nstd :: NameTable;
	using nstd :: OutputFileStream;
	using nstd :: Ptrdiff_t;
	using nstd :: Size_t;
	using nstd :: Time_t;
	using nstd :: Clock_t;
	using nstd :: Undefined;
	using nstd :: Mode;

namespace stack {
	using nstd :: container :: Stack;
}

	typedef
		nstd :: String<nstd :: memory :: allocator :: Heap>
		String;
	typedef
		nstd :: Timer
		Timer;
	typedef
		nstd :: Path<nstd :: memory :: allocator :: Heap>
		Path;
	typedef
		nstd :: memory :: Space
		Memory;

namespace container {
	typedef
		nstd :: container :: Bit<>
		Bit;
}
}

#include "del/types/allocator/del_types_allocator.hpp"
#include "del/types/array/del_types_array.hpp"
#include "del/types/chars/del_types_chars.hpp"
#include "del/types/exception/del_types_exception.hpp"
#include "del/types/index/del_types_index.hpp"
#include "del/types/lexer/del_types_lexer.hpp"
#include "del/types/list/del_types_list.hpp"
#include "del/types/manipulator/del_types_manipulator.hpp"
#include "del/types/map/del_types_map.hpp"
#include "del/types/pair/del_types_pair.hpp"
#include "del/types/set/del_types_set.hpp"
#include "del/types/storage/del_types_storage.hpp"
#include "del/types/value/del_types_value.hpp"
#include "del/types/vector/del_types_vector.hpp"

#endif /*DEL_TYPES_HPP_*/

