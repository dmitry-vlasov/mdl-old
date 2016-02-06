/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_types.hpp                                            */
/* Description:     module for basic types                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include <nstd>

namespace mdl {
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
}
namespace equation {
	using namespace nstd :: equation;
}
namespace interpolation {
	using namespace nstd :: interpolation;
}
namespace sampler {
	using namespace nstd :: sampler;
}
namespace system {
	using namespace nstd :: system;
}
namespace size {
	using namespace nstd :: size;
}
namespace time {
	using namespace nstd :: time;
}
	using nstd :: Counter;
	using nstd :: NameTable;
	using nstd :: OutputFileStream;
	using nstd :: Ptrdiff_t;
	using nstd :: Size_t;
	using nstd :: Undefined;
	using nstd :: Mode;
	using nstd :: interpolation :: Polynomial;
	using nstd :: Time;
}

#include "mdl/types/allocator/mdl_types_allocator.hpp"

namespace mdl {

	typedef
		nstd :: String<allocator :: Heap>
		String;
	typedef
		nstd :: Timer
		Timer;
	typedef
		nstd :: Path<allocator :: Heap>
		Path;
	typedef
		nstd :: memory :: Space
		Memory;

namespace container {
	typedef
		nstd :: container :: Bit<>
		Bit;
	using nstd :: container :: Pair;
}
}

#include "mdl/types/array/mdl_types_array.hpp"
#include "mdl/types/chars/mdl_types_chars.hpp"
#include "mdl/types/exception/mdl_types_exception.hpp"
#include "mdl/types/index/mdl_types_index.hpp"
#include "mdl/types/lexer/mdl_types_lexer.hpp"
#include "mdl/types/list/mdl_types_list.hpp"
#include "mdl/types/manipulator/mdl_types_manipulator.hpp"
#include "mdl/types/map/mdl_types_map.hpp"
#include "mdl/types/set/mdl_types_set.hpp"
#include "mdl/types/storage/mdl_types_storage.hpp"
#include "mdl/types/value/mdl_types_value.hpp"
#include "mdl/types/vector/mdl_types_vector.hpp"



