/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_Table.hpp                                  */
/* Description:     identificator table class                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/types/mdl_types.hpp"

namespace mdl {
namespace auxiliary {

class Table : public nstd :: Static<Table> {
private :
	typedef
		NameTable<index :: File, allocator :: Heap>
		Files_;
	typedef
		NameTable<value :: Name, allocator :: Heap>
		Names_;
	typedef Symbol Literals_;

public :
	static Files_* files();
	static Literals_* literals();
	static Names_* names();

	static void clear();

	static value :: Name defaultName();
	static void dumpLiteral (value :: Literal);
	static void dumpName (value :: Name);

	// nstd :: Static interface
	static void init();
	static void release();
	static void show (String&);
	static Size_t getVolume();

private :
	static Files_* files_;
	static Literals_* literals_;
	static Names_* names_;
	static value :: Name defaultName_;

	enum {
		INITIAL_FILES_CAPACITY = nstd :: size :: KILOBYTE * 2,
		INITIAL_LITERALS_CAPACITY =  nstd :: size :: KILOBYTE * 4,
		INITIAL_NAMES_CAPACITY = nstd :: size :: KILOBYTE * 64
	};
};

}
}


