/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_auxiliary_Corrector_Grammar.hpp                       */
/* Description:     corrector for math.mm syntax irregularities              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AUXILIARY_CORRECTOR_GRAMMAR_HPP_
#define MM_AUXILIARY_CORRECTOR_GRAMMAR_HPP_

#include "mm/types/mm_types.hpp"
#include "mm/auxiliary/mm_auxiliary_Name.hpp"
#include "mm/lexer/mm_lexer.dpp"

namespace mm {
namespace auxiliary {

/// Class \c Corrector :: Grammar is used for parsing of the external alternative axioms list.
/**
 * This class uses mm lexer to parse the file, containing the list of
 * alternative axiom (and hypothesis) declarations.
 *
 * Main procedure is \c run() .
 *
 * When the label of some axiom or essential hypothesis matches the label
 * of some expression in the external axioms list, it's expression is replaced
 * with the alternative one.
 * */
class Corrector :: Grammar : public nstd :: Static<Corrector :: Grammar> {
public :
	static const vector :: Literal* getExpression (const String&);
	static void release();

	// nstd :: Static interface
	static void initRaw();
	static void showRaw (String&);
	static Size_t getRawVolume();

private :
	static bool run();
	static void open();
	static void close();
	static void parse();

	typedef
		Name<index :: Assertion>
		CorrectionLabels_;
	typedef
		Vector
		<
			vector :: Literal,
			storage :: ByPointer,
			allocator :: Heap
		>
		ExpressionVector_;

	// The storage for alternative axioms declarations, extracted from the file.
	static ExpressionVector_* expressionVector_;

	// table of identifiers for correction labels.
	static CorrectionLabels_* correctionLabels_;

	static Path* path_;
	static Lexer* lexer_;
	enum {
		INITIAL_EXPRESSIONS_VECTOR_CAPACITY = nstd :: size :: KILOBYTE * 2
	};
};

}
}

#endif /*MM_AUXILIARY_CORRECTOR_GRAMMAR_HPP_*/
