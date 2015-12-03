/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File Name:       smm_types.hpp                                            */
/* Description:     basic smm types module                                   */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_TYPES_HPP_
#define SMM_TYPES_HPP_

#include <nstd>

namespace smm {

	using nstd :: Size_t;
	using nstd :: Ptrdiff_t;
	using nstd :: InputFileStream;
	using nstd :: OutputFileStream;
	using nstd :: NameTable;
	using nstd :: Undefined;
}

#include "smm/types/allocator/smm_types_allocator.hpp"
#include "smm/types/chars/smm_types_chars.hpp"
#include "smm/types/exception/smm_types_exception.hpp"
#include "smm/types/index/smm_types_index.hpp"
#include "smm/types/lexer/smm_types_lexer.hpp"
#include "smm/types/list/smm_types_list.hpp"
#include "smm/types/manipulator/smm_types_manipulator.hpp"
#include "smm/types/stack/smm_types_stack.hpp"
#include "smm/types/storage/smm_types_storage.hpp"
#include "smm/types/value/smm_types_value.hpp"
#include "smm/types/vector/smm_types_vector.hpp"

namespace smm {

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

#endif /*SMM_TYPES_HPP_*/
