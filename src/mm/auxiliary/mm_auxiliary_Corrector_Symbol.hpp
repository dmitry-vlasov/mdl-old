/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_auxiliary_Corrector_Symbol.hpp                        */
/* Description:     corrector for math.mm symbol designations                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mm/types/mm_types.hpp"
#include "mm/auxiliary/mm_auxiliary_Name.hpp"
#include "mm/lexer/mm_lexer.dpp"

namespace mm {
namespace auxiliary {

class Corrector :: Symbol : public nstd :: Static<Corrector :: Symbol> {
public :
	static void release();

	// nstd :: Static interface
	static void initRaw();
	static void showRaw (String&);
	static Size_t getRawVolume();

private :
	typedef
		Vector
		<
			String,
			storage :: ByPointer,
			allocator :: Heap
		>
		Vector_;

	enum {
		INITIAL_VECTOR_CAPACITY = 1024
	};

	static void run();
	static void read();
	static void parse();
	static void consumeToken (const char*, const char*&);
	static const char* consumeString (const char*&);
	static const String* parseEntry (const char*, Vector_*, const char*&);
	static void parseError (const char*, const char*);

	static Path* path_;
	static Vector_* ascii_;
	static Vector_* unicode_;
	static Vector_* latex_;

	static InputFileStream fileStream_;
	static String* buffer_;
};

}
}


