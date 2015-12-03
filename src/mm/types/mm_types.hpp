/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_types.hpp                                             */
/* Description:     mm general types module                                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_TYPES_HPP_
#define MM_TYPES_HPP_

#include <nstd>

namespace mm {

	using nstd :: Size_t;
	using nstd :: Ptrdiff_t;
	using nstd :: InputFileStream;
	using nstd :: OutputFileStream;
	using nstd :: NameTable;
	using nstd :: Undefined;
	using nstd :: Counter;

namespace system {

	using namespace nstd :: system;
}
namespace chars {

	using namespace nstd :: chars;
}
}

#include "mm/types/allocator/mm_types_allocator.hpp"
#include "mm/types/chars/mm_types_chars.hpp"
#include "mm/types/exception/mm_types_exception.hpp"
#include "mm/types/index/mm_types_index.hpp"
#include "mm/types/lexer/mm_types_lexer.hpp"
#include "mm/types/list/mm_types_list.hpp"
#include "mm/types/manipulator/mm_types_manipulator.hpp"
#include "mm/types/stack/mm_types_stack.hpp"
#include "mm/types/storage/mm_types_storage.hpp"
#include "mm/types/value/mm_types_value.hpp"
#include "mm/types/vector/mm_types_vector.hpp"

namespace mm {

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
}

#endif /*MM_TYPES_HPP_*/
