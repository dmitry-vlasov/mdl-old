/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_auxiliary_Config.hpp                                  */
/* Description:     static class for command line arguments                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AUXILIARY_CONFIG_HPP_
#define MM_AUXILIARY_CONFIG_HPP_

#include "types/mm_types.hpp"
#include "auxiliary/mm_auxiliary.dpp"

namespace mm {
namespace auxiliary {

// Class which contain boolean flags and string parameters for mm.
class Config : public nstd :: Config<Config> {
	typedef	nstd :: Config<Config> Ancestor_;
public :
	// mm general run mode
	enum RunMode_ {
		NO_WORK        = 0,
		CHECK_WORK     = 1,
		TRANSLATE_WORK = 2,
		CUT_WORK       = 3,
		DEFAULT_WORK   = CHECK_WORK
	};

	static RunMode_ getRunMode();

	static bool check();
	static bool translate();

	// Comments are removed at translation.
	static bool removeComments();
	// The translator will remove all proofs and make problems from theorems.
	static bool removeProofs();
	// The checker will show the content of the proof stack at proof errors.
	static bool keepChecking ();
	// The checker will show the content of the proof stack at proof errors.
	static bool showStack();
	// Use external file for alternative axiom declarations.
	static bool useGrammarCorrection();
	// Use external file to replace math symbols with unicode.
	static bool useSymbolCorrection();
	// Extract the list of all axiomatic declarations.
	static bool extractAxioms();
	static bool implicitSteps();
	static bool explicitDisjointeds();
	// Cut single source file into a directory tree.
	static bool cutSource();
	// translate all included source files
	static bool deepTranslation();
	// metamath extension
	static const char* metamathExtension();

	// The whole path to the file with external alternative axioms.
	static const nstd :: Path<>* getGrammarCorrectionSource();
	static const nstd :: Path<>* getSymbolCorrectionSource();
	static const nstd :: Path<>* getExtractionTarget();

	// info output options
	static bool showTimings();
	static bool showMath();
	static bool showVolume();
	static Size_t getVolume();

	static bool proceed (const int argCount, const char* argValues[]);
	static bool proceedStringOption (const char*, const int, const char* [], int&);
	static bool proceedOneCharOption (const char*, const int, const char* [], int&);

	static void release();

private :
	// Shows the options usage message.
	static void showUsageMessage();
	static void init ();

	static bool isConsistent();
	static bool checkPaths();
	static bool analyseArguments();

	static RunMode_ runMode_;

	static bool check_;
	static bool translate_;

	static bool removeComments_;
	static bool removeProofs_;
	/// The checker will show the content of the proof steck at proof errors.
	static bool keepChecking_;
	/// The checker will show the content of the proof steck at proof errors.
	static bool showStack_;
	/// Use external file for alternative axiom declarations.
	static bool useGrammarCorrection_;
	/// Use external file to replace math symbols with unicode.
	static bool useSymbolCorrection_;
	/// Extract the list of all axiomatic declarations.
	static bool extractAxioms_;

	static bool implicitSteps_;
	static bool explicitDisjointeds_;
	static bool cutSource_;
	static bool deepTranslation_;

	/// The whole path to the file path with external alternative axioms.
	static nstd :: Path<>* grammarCorrectionSource_;
	static nstd :: Path<>* symbolCorrectionSource_;
	static nstd :: Path<>* extractionTarget_;

	static bool showTimings_;
	static bool showMath_;
	static bool showVolume_;
};

}
}

#include "mm/auxiliary/mm_auxiliary_Config.ipp"

#endif /*MM_AUXILIARY_CONFIG_HPP_*/
