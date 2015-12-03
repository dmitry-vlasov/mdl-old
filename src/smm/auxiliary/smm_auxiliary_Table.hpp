/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_auxiliary_Table.hpp                                  */
/* Description:     identificator table class                                */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_AUXILIARY_TABLE_HPP_
#define SMM_AUXILIARY_TABLE_HPP_

#include "smm/types/smm_types.hpp"

namespace smm {
namespace auxiliary {

class Table : public nstd :: Static<Table> {
private :
	typedef
		NameTable<index :: File, allocator :: Heap>
		Files_;
	typedef
		NameTable<value :: Literal, allocator :: Heap>
		Literals_;
	typedef
		NameTable<value :: Index, allocator :: Heap>
		Labels_;

public :
	static Files_* files();
	static Literals_* literals();
	static Labels_* labels();
	static void release();

	// nstd :: Static interface
	static void initRaw ();
	static void showRaw (String&);
	static Size_t getRawVolume();

private :
	static Files_* files_;
	static Literals_* literals_;
	static Labels_* labels_;

	enum {
		INITIAL_FILES_CAPACITY = nstd :: size :: KILOBYTE * 2,
		INITIAL_LITERALS_CAPACITY =  1024 * 4,
		INITIAL_LABELS_CAPACITY =  1024 * 32
	};
};

}
}

#endif /*SMM_AUXILIARY_TABLE_HPP_*/
