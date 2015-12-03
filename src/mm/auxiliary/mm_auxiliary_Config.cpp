/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_auxiliary_Config.cpp                                  */
/* Description:     static class for command line arguments                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AUXILIARY_CONFIG_CPP_
#define MM_AUXILIARY_CONFIG_CPP_

#include "mdl/auxiliary/config/mdl_auxiliary_config.hpp"

namespace mm {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	inline Config :: RunMode_
	Config :: getRunMode() {
		return runMode_;
	}

	inline bool
	Config :: check () {
		return check_;
	}
	inline bool
	Config :: translate () {
		return translate_;
	}

	inline bool
	Config :: removeComments () {
		return removeComments_;
	}
	inline bool
	Config :: removeProofs () {
		return removeProofs_;
	}
	inline bool
	Config :: keepChecking () {
		return keepChecking_;
	}
	inline bool
	Config :: showStack() {
		return showStack_;
	}
	inline bool
	Config :: useGrammarCorrection() {
		return useGrammarCorrection_;
	}
	inline bool
	Config :: useSymbolCorrection() {
		return useSymbolCorrection_;
	}
	inline bool
	Config :: extractAxioms() {
		return extractAxioms_;
	}
	inline bool
	Config :: implicitSteps() {
		return implicitSteps_;
	}
	inline bool
	Config :: explicitDisjointeds() {
		return explicitDisjointeds_;
	}
	inline bool
	Config :: cutSource() {
		return cutSource_;
	}
	inline bool
	Config :: deepTranslation() {
		return deepTranslation_;
	}

	inline const nstd :: Path<>*
	Config :: getGrammarCorrectionSource() {
		return grammarCorrectionSource_;
	}
	inline const nstd :: Path<>*
	Config :: getSymbolCorrectionSource() {
		return symbolCorrectionSource_;
	}
	inline const nstd :: Path<>*
	Config :: getExtractionTarget() {
		return extractionTarget_;
	}

	// info output options
	inline bool
	Config :: showTimings() {
		return showTimings_;
	}
	inline bool
	Config :: showMath() {
		return showMath_;
	}
	inline bool
	Config :: showVolume() {
		return showVolume_;
	}
	inline Size_t
	Config :: getVolume()
	{
		Size_t volume = 0;
		volume += Ancestor_ :: getVolume();
		if (grammarCorrectionSource_ != NULL) {
			volume += grammarCorrectionSource_->getVolume();
			volume += grammarCorrectionSource_->getSizeOf();
		}
		if (symbolCorrectionSource_ != NULL) {
			volume += symbolCorrectionSource_->getVolume();
			volume += symbolCorrectionSource_->getSizeOf();
		}
		if (extractionTarget_ != NULL) {
			volume += extractionTarget_->getVolume();
			volume += extractionTarget_->getSizeOf();
		}
		return volume;
	}

using std :: cout;
using std :: endl;

	bool
	Config :: proceed (const int argCount, const char* argValues[])
	{
		init();
		if (argCount == 1) {
			std :: cout << getProgramName() << ": no input files" << std :: endl;
			exit_ = true;
			error_ = true;
			return false;
		}
		if (!Ancestor_ :: proceedOptions (argCount,argValues)) {
			return false;
		}
		return analyseArguments();
	}
	bool
	Config :: proceedStringOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		if (Ancestor_ :: proceedStringOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (equalStrings (opt, "check")) {
			check_ = true;
			runMode_ = CHECK_WORK;
			return true;
		}
		if (equalStrings (opt, "translate")) {
			translate_ = true;
			runMode_ = TRANSLATE_WORK;
			return true;
		}
		if (equalStrings (opt, "remove-comments")) {
			removeComments_ = true;
			return true;
		}
		if (equalStrings (opt, "remove-proofs")) {
			removeProofs_ = true;
			return true;
		}
		if (equalStrings (opt, "explicit-disjointed")) {
			explicitDisjointeds_ = true;
			return true;
		}
		if (equalStrings (opt, "cut-source")) {
			cutSource_ = true;
			runMode_ = CUT_WORK;
			return true;
		}
		if (equalStrings (opt, "deep-translation")) {
			deepTranslation_ = true;
			return true;
		}
		if (equalStrings (opt, "show-stack")) {
			showStack_ = true;
			return true;
		}
		if (equalStrings (opt,"keep-checking")) {
			keepChecking_ = true;
			return true;
		}
		if (equalStrings (opt,"implicit-steps")) {
			implicitSteps_ = true;
			return true;
		}
		if (equalStrings (opt, "info-timing")) {
			showTimings_ = true;
			return true;
		}
		if (equalStrings (opt, "info-math")) {
			showMath_ = true;
			return true;
		}
		if (equalStrings (opt, "info-volume")) {
			showVolume_ = true;
			return true;
		}
		if (equalStrings (opt, "info-all")) {
			showTimings_ = true;
			showMath_ = true;
			showVolume_ = true;
			return true;
		}
		if (equalStrings (opt, "correct-symbol")) {
			if (i < argCount - 1) {
				useSymbolCorrection_ = true;
				const char* const
					path = argValues [++ i];
				symbolCorrectionSource_ = new Path_ (path);
			} else {
				cout << "\"--correct-symbol\" option must be followed by a valid external file name." << endl;
				exit_ = true;
				error_ = true;
			}
			return true;
		}
		if (equalStrings (opt, "correct-grammar")) {
			if (i < argCount - 1) {
				useGrammarCorrection_ = true;
				const char* const
					path = argValues [++ i];
				grammarCorrectionSource_ = new Path_ (path);
			} else {
				cout << "\"--correct-grammar\" option must be followed by a valid external file name." << endl;
				exit_ = true;
				error_ = true;
			}
			return true;
		}
		if (equalStrings (opt, "extract-axioms")) {
			if (i < argCount - 1) {
				extractAxioms_ = true;
				const char* const
					path = argValues [++ i];
				extractionTarget_ = new Path_ (path);
			} else {
				cout << "\"--extract-axioms\" option must be followed by an external file name." << endl;
				exit_ = true;
				error_ = true;
			}
			return true;
		}
		return false;
	}
	bool
	Config :: proceedOneCharOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		switch (*opt) {
		case 'c' :
			check_ = true;
			runMode_ = CHECK_WORK;
			return true;
		case 't' :
			translate_ = true;
			runMode_ = TRANSLATE_WORK;
			return true;
		case 'k' :
			keepChecking_ = true;
			return true;
		case 's' :
			showStack_ = true;
			return true;
		case 'i' :
			implicitSteps_ = true;
			return true;
		default :
			return Ancestor_ :: proceedOneCharOption (opt, argCount, argValues, i);
		}
	}

	void
	Config :: release()
	{
		if (grammarCorrectionSource_ != NULL) {
			delete grammarCorrectionSource_;
			grammarCorrectionSource_ = NULL;
		}
		if (symbolCorrectionSource_ != NULL) {
			delete symbolCorrectionSource_;
			symbolCorrectionSource_ = NULL;
		}
		if (extractionTarget_ != NULL) {
			delete extractionTarget_;
			extractionTarget_ = NULL;
		}
		Ancestor_ :: release();
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Config :: showUsageMessage()
	{
		Ancestor_ :: showProgramUsage();
		cout << "Options:" << endl;
		Ancestor_ :: showUsageMessage (cout);
		cout << "  -c,  --check                  check the source file." << endl;
		cout << "  -t,  --translate              translate source file to the russell language." << endl;
		cout << endl;
		cout << "  -k,  --keep-checking          keep checking at check errors" << endl;
		cout << "  -i,  --implicit-steps         translate proof steps implicitly" << endl;
		cout << "  -s,  --show-stack             extra debugging facility: shows proof stack at proof errors." << endl;
		cout << "       --remove-comments        remove comments at translation" << endl;
		cout << "       --remove-proofs          remove proofs from the source" << endl;
		cout << "       --explicit-disjointed    make disjointed variable restrictions explicit" << endl;
		cout << "       --cut-source             cut single source file into a directory tree" << endl;
		cout << "       --deep-translation       translate all included source files" << endl;
		cout << endl;
		cout << "       --info-timing            show thorough timing info" << endl;
		cout << "       --info-math              show thorough math info" << endl;
		cout << "       --info-volume            show thorough volume info" << endl;
		cout << "       --info-all               show all thorough info" << endl;
		cout << endl;
		cout << "       --correct-symbol <file>  replace math symbols with unicode alternatives" << endl;
		cout << "       --correct-grammar <file> use external file with axioms and " << endl;
		cout << "                                definitions to correct math grammar" << endl;
		cout << "                                WARNINIG!" << endl;
		cout << "                                when using external axioms definition" << endl;
		cout << "                                theorems are not being checked." << endl;
		cout << endl;
		//cout << "       --extract-axioms <file>  extract axioms and definitions to the file" << endl;
		//cout << endl;
	}

	void
	Config :: init ()
	{
		Ancestor_ :: init ();
		programName() << "mm";
		programDescription() << "metamath checker & translator to russell";
	}

	bool
	Config :: isConsistent()
	{
		if (!translate() && useGrammarCorrection()) {
			cout << "insensible to use grammar correction definition for checking. " << endl;
			cout << "option \"--correct-grammar\" makes no sense for checking." << endl;
			exit_ = true;
			error_ = true;
			return false;
		}
		if (!translate() && useSymbolCorrection()) {
			cout << "insensible to use symbol correction definition for checking. " << endl;
			cout << "option \"--correct-symbol\" makes no sense for checking." << endl;
			exit_ = true;
			error_ = true;
			return false;
		}
		if (!translate() && removeProofs()) {
			cout << "insensible to remove proofs without translation. " << endl;
			cout << "option \"--remove-proofs\" makes no sense for checking." << endl;
			exit_ = true;
			error_ = true;
			return false;
		}
		/*
		if (useExternal && verbose) {
			cout << "CAUTION!" << endl;
			cout << "when using external axioms definition theorems are not being checked." << endl;
		}
		*/
		return true;
	}
	bool
	Config :: checkPaths()
	{
		if (getSource().getExtension() != metamathExtension()) {
			cout << "wrong source extension *." << getSource().getExtension() << std :: endl;
			cout << "Should be *." << metamathExtension() << endl;
			exit_ = true;
			error_ = true;
			return false;
		}
		if (translate()) {
			if (getTarget().isUndefined()) {
				target() = getSource();
				target().extension() = mdl :: Config :: russellExtension();
			}
			if (getTarget().getExtension() != mdl :: Config :: russellExtension()) {
				cout << "wrong target extension *." << getTarget().getExtension() << std :: endl;
				cout << "Should be *." << mdl :: Config :: russellExtension() << endl;
				exit_ = true;
				error_ = true;
				return false;
			}
		} else if (cutSource()) {
			if (getTarget().isUndefined()) {
				target() = getSource();
				target().extension() = metamathExtension();
			}
			if (getTarget().getExtension() != metamathExtension()) {
				cout << "wrong target extension *." << getTarget().getExtension() << std :: endl;
				cout << "Should be *." << metamathExtension() << endl;
				exit_ = true;
				error_ = true;
				return false;
			}
		} else {
			if (getTarget().isUndefined()) {
				cout << "target file defined while no translation is done" << endl;
				exit_ = true;
				error_ = true;
				return false;
			}
		}
		return Ancestor_ :: Paths :: checkPaths();
	}
	bool
	Config :: analyseArguments()
	{
		if (showHelp()) {
			showUsageMessage();
			return false;
		}
		if (exit()) {
			return false;
		}
		if (!checkPaths()) {
			return false;
		}
		if (!isConsistent()) {
			return false;
		}
		return true;
	}

	/*************************************
	 *		Static private attributes
	 *************************************/

	Config :: RunMode_ Config :: runMode_ = DEFAULT_WORK;

	bool Config :: check_ = true;
	bool Config :: translate_ = false;

	bool Config :: removeComments_ = false;
	bool Config :: removeProofs_ = false;
	bool Config :: keepChecking_ = false;
	bool Config :: showStack_ = false;
	bool Config :: useGrammarCorrection_ = false;
	bool Config :: useSymbolCorrection_ = false;
	bool Config :: extractAxioms_ = false;
	bool Config :: implicitSteps_ = false;
	bool Config :: explicitDisjointeds_ = false;
	bool Config :: cutSource_ = false;
	bool Config :: deepTranslation_ = false;

	nstd :: Path<>*
		Config :: grammarCorrectionSource_ = NULL;
	nstd :: Path<>*
		Config :: symbolCorrectionSource_ = NULL;
	nstd :: Path<>*
		Config :: extractionTarget_ = NULL;

	// info output options
	bool Config :: showTimings_ = false;
	bool Config :: showMath_ = false;
	bool Config :: showVolume_ = false;
}
}

#endif /*MM_AUXILIARY_CONFIG_CPP_*/
