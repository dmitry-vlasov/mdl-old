/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_auxiliary_Table.hpp                                   */
/* Description:     static class for metamath tables                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AUXILIARY_TABLE_HPP_
#define MM_AUXILIARY_TABLE_HPP_

#include "mm/auxiliary/mm_auxiliary_Name.hpp"
#include "mm/auxiliary/mm_auxiliary_Symbol.hpp"

namespace mm {
namespace auxiliary {

class Table : public nstd :: Static<Table> {
private :
	typedef
		Name<index :: File>
		Files_;
	typedef
		Symbol<value :: Literal>
		Literals_;
	typedef
		Name<value :: Label>
		Identificators_;
	typedef
		Name<index :: Assertion>
		AssertionLabels_;
	typedef
		Name<index :: Assertion>
		HypothesisLabels_;

public :
	static Files_* files();
	static Literals_* literals();
	static Identificators_* identificators();
	static AssertionLabels_* assertionLabels();
	static HypothesisLabels_* hypothesisLabels();
	static void release();

	// nstd :: Static interface
	static void initRaw ();
	static void showRaw (nstd :: String<>&);
	static Size_t getRawVolume();

private :
	static Files_* files_;
	static Literals_* literals_;
	static Identificators_* identificators_;
	static AssertionLabels_* assertionLabels_;
	static HypothesisLabels_* hypothesisLabels_;

	enum {
		INITIAL_FILES_VECTOR_CAPACITY = nstd :: size :: KILOBYTE * 2,
		INITIAL_LITERALS_VECTOR_CAPACITY = nstd :: size :: KILOBYTE * 2,
		INITIAL_IDENTIFICATORS_VECTOR_CAPACITY = nstd :: size :: KILOBYTE * 2,
		INITIAL_ASSERTION_LABELS_VECTOR_CAPACITY = nstd :: size :: KILOBYTE * 4,
		INITIAL_HYPOTHESIS_LABELS_VECTOR_CAPACITY = nstd :: size :: KILOBYTE * 4
	};
};

}
}

#include "mm/auxiliary/mm_auxiliary_Table.ipp"

#endif /*MM_AUXILIARY_TABLE_HPP_*/
