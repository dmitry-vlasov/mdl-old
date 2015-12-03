/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_auxiliary_AxiomExtractor.hpp                          */
/* Description:     axiom extractor                                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AUXILIARY_AXIOM_EXTRACTOR_HPP_
#define MM_AUXILIARY_AXIOM_EXTRACTOR_HPP_

#include "types/mm_types.hpp"
#include "auxiliary/mm_auxiliary.dpp"

namespace mm {
namespace auxiliary {

class AxiomExtractor : public nstd :: Static<AxiomExtractor> {
public :
	static void run();

	/// nstd :: Static interface
	static void initRaw ();
	static void showRaw (nstd :: String&);
	static Size_t getRawVolume();

private :
	static void openSource ();
	static void openOutput ();
	static void closeOutput ();

	/// Parses block in order to extract all axioms.
	static void parseBlockForAxioms();

	/// Parses non-labeled declarations in order to extract all axioms.
	static void parseSimpleNodeForAxioms();

	/// Parses labeled declarations in order to extract all axioms.
	static void parseLabeledNodeForAxioms();

	/// Storage for current label token.
	static String labelToken_;

	/// file stream for extraction/use of axioms
	static OutputFileStream fileStream_;

	/// Initial values for capacity of temporary storages
	enum {
		INITIAL_LABEL_TOKEN_CAPACITY = 256
	};
};

}
}

#endif /*MM_AUXILIARY_AXIOM_EXTRACTOR_HPP_*/
