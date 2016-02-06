/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File name:       del_auxiliary_Table.hpp                                  */
/* Description:     identificator table class                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/types/del_types.hpp"

namespace del {
namespace auxiliary {

class Table : public nstd :: Static<Table> {
private :
	typedef
		NameTable<index :: File, allocator :: Heap>
		Files_;
	typedef
		NameTable<value :: Relation, allocator :: Heap>
		Relations_;
	typedef
		NameTable<value :: Theory, allocator :: Heap>
		Theories_;
	typedef
		NameTable<value :: Variable, allocator :: Heap>
		Variables_;
	typedef
		NameTable<value :: Signature, allocator :: Heap>
		Signatures_;
	typedef
		vector :: Vector<Variables_, storage :: ByPointer, allocator :: Heap>
		VariablesStack_;

public :
	static Files_* files();
	static Relations_* relations();
	static Theories_* theories();
	static Variables_* variables();
	static Signatures_* signatures();
	static void release();

	static void pushVariables();
	static void popVariables();

	// nstd :: Static interface
	static void initRaw ();
	static void showRaw (String&);
	static Size_t getRawVolume();

private :
	static Files_* files_;
	static Relations_* relations_;
	static Theories_* theories_;
	static Variables_* variables_;
	static Signatures_* signatures_;
	static VariablesStack_* variablesStack_;

	enum {
		INITIAL_FILES_CAPACITY = nstd :: size :: KILOBYTE * 2,
		INITIAL_RELATIONS_CAPACITY =  1024 * 4,
		INITIAL_THEORIES_CAPACITY =  1024 * 4,
		INITIAL_VARIABLES_CAPACITY =  1024 * 4,
		INITIAL_SIGNATURES_CAPACITY =  1024 * 4,
		INITIAL_VARIABLES_STACK_CAPACITY = 8
	};
};

}
}


