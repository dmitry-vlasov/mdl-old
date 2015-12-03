/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File name:       del_auxiliary_Config.cpp                                 */
/* Description:     static class for command line arguments                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_AUXILIARY_CONFIG_CPP_
#define DEL_AUXILIARY_CONFIG_CPP_

#include "del/auxiliary/del_auxiliary_Config.hpp"

namespace del {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	// input/output format
	inline Config :: Format
	Config :: inputFormat() {
		return inputFormat_;
	}
	inline Config :: Format
	Config :: outputFormat() {
		return outputFormat_;
	}

	// main actions
	inline bool
	Config :: translate() {
		return translate_;
	}
	inline bool
	Config :: solve() {
		return solve_;
	}
	inline bool
	Config :: minimize() {
		return minimize_;
	}
	inline bool
	Config :: decompose() {
		return decompose_;
	}
	inline bool
	Config :: computeDelta() {
		return computeDelta_;
	}
	inline bool
	Config :: write() {
		return write_;
	}

	// general flags
	inline bool
	Config :: generateRandomSource() {
		return generateRandomSource_;
	}
	inline bool
	Config :: keepSource() {
		return keepSource_;
	}
	inline bool
	Config :: removeComments() {
		return removeComments_;
	}
	inline bool
	Config :: commentStuff() {
		return commentStuff_;
	}
	inline bool
	Config :: keepTermNames() {
		return keepTermNames_;
	}
	inline bool
	Config :: outputToStdout() {
		return outputToStdout_;
	}
	inline bool
	Config :: verify() {
		return verify_;
	}
	inline value :: Integer
	Config :: partialDecompositionFactor() {
		return partialDecompositionFactor_;
	}

	// memory options
	inline Size_t
	Config :: getStackVolume() {
		return stackVolume_;
	}
	// timing options
	inline Time_t
	Config :: getMaxSolveTime() {
		return maxSolveTime_;
	}
	inline Time_t
	Config :: getMaxDecomposeTime() {
		return maxDecomposeTime_;
	}
	inline Time_t
	Config :: getMaxMinimizeTime() {
		return maxMinimizeTime_;
	}
	inline Clock_t
	Config :: getRefreshClock() {
		return refreshClock_;
	}

	// delta generation parameter
	inline value :: Integer
	Config :: getDeltaThreshold() {
		return deltaThreshold_;
	}
	inline Config :: DeltaGenerationMode
	Config :: getDeltaGenerationMode() {
		return deltaGenerationMode_;
	}

	// dynamic theory generation parameters
	inline value :: Integer
	Config :: getSigmaConceptCount() {
		return sigmaConceptCount_;
	}
	inline value :: Integer
	Config :: getSigmaRelationCount() {
		return sigmaRelationCount_;
	}
	inline value :: Integer
	Config :: getDeltaConceptCount() {
		return deltaConceptCount_;
	}
	inline value :: Integer
	Config :: getDeltaRelationCount() {
		return deltaRelationCount_;
	}
	inline value :: Integer
	Config :: getTermMaxLength() {
		return termMaxLength_;
	}
	inline value :: Integer
	Config :: getTermMaxDepth() {
		return termMaxDepth_;
	}
	inline value :: Integer
	Config :: getTheorySize() {
		return theorySize_;
	}
	inline value :: Integer
	Config :: getTheoryCount() {
		return theoryCount_;
	}

	// statistics output options
	inline bool
	Config :: showStatistics() {
		return showStatistics_;
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

using std :: cout;
using std :: endl;

	bool
	Config :: proceed (const int argCount, const char* argValues[])
	{
		init();
		if (argCount == 1) {
			cout << getProgramName() << ": no input files" << endl;
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
		if (equalStrings (opt, "translate")) {
			translate_ = true;
			return true;
		}
		if (equalStrings (opt, "solve")) {
			solve_ = true;
			return true;
		}
		if (equalStrings (opt, "minimize")) {
			minimize_ = true;
			return true;
		}
		if (equalStrings (opt, "decompose")) {
			decompose_ = true;
			return true;
		}
		if (equalStrings (opt, "onlydelta")) {
			computeDelta_ = true;
			return true;
		}
		if (equalStrings (opt, "gen-rand-source")) {
			generateRandomSource_ = true;
			return true;
		}
		if (equalStrings (opt, "keep-source")) {
			keepSource_ = true;
			return true;
		}
		if (equalStrings (opt, "remove-comments")) {
			removeComments_ = true;
			return true;
		}
		if (equalStrings (opt, "comment-stuff")) {
			commentStuff_ = true;
			return true;
		}
		if (equalStrings (opt, "keep-term-names")) {
			keepTermNames_ = true;
			return true;
		}
		if (equalStrings (opt, "output-to-stdout")) {
			outputToStdout_ = true;
			write_ = false;
			return true;
		}
		if (equalStrings (opt, "input-del")) {
			inputFormat_ = DEL_FORMAT;
			return true;
		}
		if (equalStrings (opt, "input-man")) {
			inputFormat_ = MAN_FORMAT;
			return true;
		}
		if (equalStrings (opt, "input-func")) {
			inputFormat_ = FUNC_FORMAT;
			return true;
		}
		if (equalStrings (opt, "output-del")) {
			outputFormat_ = DEL_FORMAT;
			return true;
		}
		if (equalStrings (opt, "output-man")) {
			outputFormat_ = MAN_FORMAT;
			return true;
		}
		if (equalStrings (opt, "output-func")) {
			outputFormat_ = FUNC_FORMAT;
			return true;
		}
		if (equalStrings (opt, "verify")) {
			verify_ = true;
			return true;
		}
		if (equalStrings (opt, "max-solve-time")) {
			sscanf (argValues [++ i], "%ld", &maxSolveTime_);
			return true;
		}
		if (equalStrings (opt, "max-decompose-time")) {
			sscanf (argValues [++ i], "%ld", &maxDecomposeTime_);
			return true;
		}
		if (equalStrings (opt, "max-minimize-time")) {
			sscanf (argValues [++ i], "%ld", &maxMinimizeTime_);
			return true;
		}
		if (equalStrings (opt, "refresh-time")) {
			sscanf (argValues [++ i], "%ld", &refreshClock_);
			return true;
		}
		if (equalStrings (opt, "stack-volume")) {
			int stackVolume = DEFAULT_STACK_VOLUME;
			sscanf (argValues [++ i], "%d", &stackVolume);
			stackVolume_ = stackVolume;
			return true;
		}
		if (equalStrings (opt, "delta-threshold")) {
			sscanf (argValues [++ i], "%d", &deltaThreshold_);
			return true;
		}
		if (equalStrings (opt, "delta-max-cohesion")) {
			deltaGenerationMode_ = PERCENT_OF_MAX_COHESION;
			return true;
		}
		if (equalStrings (opt, "delta-relative-cohesion")) {
			deltaGenerationMode_ = PERCENT_OF_RELATIVE_COHESION;
			return true;
		}
		if (equalStrings (opt, "part-decomp-factor")) {
			sscanf (argValues [++ i], "%d", &partialDecompositionFactor_);
			return true;
		}
		if (equalStrings (opt, "concept-count")) {
			sscanf (argValues [++ i], "%d", &sigmaConceptCount_);
			return true;
		}
		if (equalStrings (opt, "relation-count")) {
			sscanf (argValues [++ i], "%d", &sigmaRelationCount_);
			return true;
		}
		if (equalStrings (opt, "term-max-length")) {
			sscanf (argValues [++ i], "%d", &termMaxLength_);
			return true;
		}
		if (equalStrings (opt, "term-max-depth")) {
			sscanf (argValues [++ i], "%d", &termMaxDepth_);
			return true;
		}
		if (equalStrings (opt, "theory-size")) {
			sscanf (argValues [++ i], "%d", &theorySize_);
			return true;
		}
		if (equalStrings (opt, "theory-count")) {
			sscanf (argValues [++ i], "%d", &theoryCount_);
			return true;
		}
		if (equalStrings (opt, "statistics")) {
			showStatistics_ = true;
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
		return false;
	}
	bool
	Config :: proceedOneCharOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		if (Ancestor_ :: proceedOneCharOption (opt, argCount, argValues, i)) {
			return true;
		}
		if (*opt == 't') {
			translate_ = true;
			return true;
		}
		if (*opt == 's') {
			solve_ = true;
			return true;
		}
		return false;
	}

	inline void
	Config :: release() {
		Ancestor_ :: release();
	}
	inline Size_t
	Config :: getVolume() {
		return Ancestor_ :: getVolume();
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
		cout << "  -t,  --translate               translate source to the target language. By default = ";
			cout << (translate_ ? "true" : "false") << endl;
		cout << "  -s,  --solve                   answer the given questions. By default = ";
			cout << (solve_ ? "true" : "false") << endl;
		cout << "       --gen-rand-source         generate random source, for testing. By default = ";
			cout << (generateRandomSource_ ? "true" : "false") << endl;
		cout << "       --keep-source             keep source in the output. By default = ";
			cout << (keepSource_ ? "true" : "false") << endl;
		cout << "       --remove-comments         remove comments at translation. By default = ";
			cout << (commentStuff_ ? "true" : "false") << endl;
		cout << "       --comment-stuff           comment OWL stuff instead of throwing it away. By default = ";
			cout << (commentStuff_ ? "true" : "false") << endl;
		cout << "       --keep-term-names         keep term names in symbols of definitions. By default = ";
			cout << (keepTermNames_ ? "true" : "false") << endl;
		cout << "       --output-to-stdout        output to the stadard output stream. By default = ";
			cout << (outputToStdout_ ? "true" : "false") << endl;
		cout << "       --verify                  verify the result of decomposition. By default = ";
			cout << (verify_ ? "true" : "false") << endl;
		cout << "       --onlydelta               compute delta signature automatically, do nothing else. By default = ";
			cout << (computeDelta_ ? "true" : "false") << endl;
		cout << endl;
		cout << "       --input-del               input in the original del format. By default = ";
			cout << ((inputFormat_ ==  DEL_FORMAT)? "true" : "false") << endl;
		cout << "       --input-man               input in the Manchester syntax. By default = ";
			cout << ((inputFormat_ ==  MAN_FORMAT)? "true" : "false") << endl;
		cout << "       --input-func              input in the functional OWL2 format. By default = ";
			cout << ((inputFormat_ ==  FUNC_FORMAT)? "true" : "false") << endl;
		cout << "       --output-del              output in the original del format. By default = ";
			cout << ((outputFormat_ ==  DEL_FORMAT)? "true" : "false") << endl;
		cout << "       --output-man              output in the manchester syntax. By default = ";
			cout << ((outputFormat_ ==  MAN_FORMAT)? "true" : "false") << endl;
		cout << "       --output-func             output in the functional OWL2 format. By default = ";
			cout << ((outputFormat_ ==  FUNC_FORMAT)? "true" : "false") << endl;
		cout << endl;
		cout << "       --max-solve-time <time>     max time for solving (minutes). By default = " << DEFAULT_MAX_SOLVE_TIME << endl;
		cout << "       --max-decompose-time <time> max time for decomposing (minutes). By default = " << DEFAULT_MAX_DECOMPOSE_TIME << endl;
		cout << "       --max-minimize-time <time>  max time for minimizing (minutes). By default = " << DEFAULT_MAX_MINIMIZE_TIME << endl;
		cout << "       --refresh-time <time>       time to refresh progress indicator (milliseconds). By default = " << DEFAULT_REFRESH_CLOCK << endl;
		cout << "       --stack-volume <size>       use <size> volume for stack (megabytes). By default = " << DEFAULT_STACK_VOLUME << endl;
		cout << "       --delta-threshold <%>       delta signature threshold (percent). By default = " << DEFAULT_DELTA_THRESHOLD << endl;
		cout << "       --delta-max-cohesion        compute delta signature by comparing symbol cohesion" << endl;
		cout << "                                   with the max cohesion. By default = ";
		cout << ((DEFAULT_DELTA_GENERATION_MODE == PERCENT_OF_MAX_COHESION)? "true" : "false") << endl;
		cout << "       --delta-relative-cohesion   compute delta signature by comparing symbol cohesion" << endl;
		cout << "                                   with the signature cardinality. By default = ";
		cout << ((DEFAULT_DELTA_GENERATION_MODE == PERCENT_OF_RELATIVE_COHESION)? "true" : "false") << endl;
		cout << "       --part-decomp-factor <R>    partial decomposition factor. By default = ";
		if (partialDecompositionFactor_ == value :: undefined :: INTEGER) {
			cout << "undefined" << endl;
		} else {
			cout << partialDecompositionFactor_ << endl;
		}
		cout << endl;
		cout << "       --concept-count <size>      concept count, for random signature. By default = " << DEFAULT_SIGMA_CONCEPT_COUNT << endl;
		cout << "       --relation-count <size>     relation count, for random signature. By default = " << DEFAULT_SIGMA_RELATION_COUNT << endl;
		cout << "       --term-max-length <size>    max term length, for random term. By default = " << DEFAULT_TERM_MAX_LENGTH << endl;
		cout << "       --term-max-depth <size>     max term depth, for random term. By default = " << DEFAULT_TERM_MAX_DEPTH << endl;
		cout << "       --theory-size <size>        size of a random theory. By default = " << DEFAULT_THEORY_SIZE << endl;
		cout << "       --theory-count <size>       number of theories in random source. By default = " << DEFAULT_THEORY_COUNT << endl;
		cout << endl;
		cout << "       --statistics              show statistics" << endl;
		cout << "       --info-timing             show thorough timing info" << endl;
		cout << "       --info-math               show thorough math info" << endl;
		cout << "       --info-volume             show thorough volume info" << endl;
		cout << "       --info-all                show all thorough info" << endl;
		cout << endl;
	}
	inline void
	Config :: init ()
	{
		Ancestor_ :: init ();
		verbosity_ = VERBOSE_MAX;
		programName() << "del";
		programDescription() << "del ('d' EL description logic) solver/decomposer";
	}

	inline bool
	Config :: initMemorySize()
	{
		stackVolume_ *= MEMORY_UNIT_SIZE;
		return true;
	}
	inline bool
	Config :: initTimes()
	{
		maxSolveTime_     *= 60;   // seconds in one minute
		maxDecomposeTime_ *= 60;   // seconds in one minute
		maxMinimizeTime_  *= 60;   // seconds in one minute
		#ifdef __linux__
		refreshClock_     *= 1000; // microseconds in one millisecond,
		#endif
		return true;
	}
	bool
	Config :: isConsistent()
	{
		if (deltaThreshold_ > 100) {
			cout << "wrong delta threshold: " << deltaThreshold_ << std :: endl;
			cout << "Should be an integer between 0 and 100" << endl;
			return false;
		}
		if (computeDelta_) {
			if (inputFormat_ == DEL_FORMAT) {
				cout << "makes no sense to compute delta automatically since the source file is in del format." << std :: endl;
				cout << "This option works only with *.man and *.owl sources" << endl;
				return false;
			}
			solve_ = false;
			translate_ = false;
			minimize_ = false;
			decompose_ = false;
			write_ = false;
		}
		return true;
	}
	bool
	Config :: checkPaths()
	{
		if (generateRandomSource_) {
			return true;
		}
		switch (inputFormat_) {
		case DEL_FORMAT :
			if (getSource().getExtension() != "del") {
				cout << "wrong source extension *." << getSource().getExtension() << std :: endl;
				cout << "Should be *.del" << endl;
				cout << "If the input file is in Manchester or OWL format, please, specify an appropriate option." << endl;
				exit_ = true;
				error_ = true;
				return false;
			}
			break;
		case MAN_FORMAT :
			if (getSource().getExtension() != "man") {
				cout << "wrong source extension *." << getSource().getExtension() << std :: endl;
				cout << "Should be *.man - Manchester syntax" << endl;
				exit_ = true;
				error_ = true;
				return false;
			}
			break;
		case FUNC_FORMAT :
			if (getSource().getExtension() != "owl") {
				cout << "wrong source extension *." << getSource().getExtension() << std :: endl;
				cout << "Should be *.owl - functional OWL2 format" << endl;
				exit_ = true;
				error_ = true;
				return false;
			}
			break;
		}
		if (getTarget().isUndefined()) {
			target() = getSource();
			target().extension() = "del";
			target().name() << "_out";
		}
		return Paths :: checkPaths();
	}
	bool
	Config :: analyseArguments()
	{
		//overwrite_ = true;
		if (showHelp()) {
			showUsageMessage();
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
		if (!initMemorySize()) {
			return false;
		}
		if (!initTimes()) {
			return false;
		}
		return true;
	}

	/*************************************
	 *		Private static attributes
	 *************************************/

	// input/output format
	Config :: Format Config :: outputFormat_ = DEFAULT_FORMAT;
	Config :: Format Config :: inputFormat_ = DEFAULT_FORMAT;

	// main actions
	bool Config :: translate_ = false;
	bool Config :: solve_ = false;
	bool Config :: minimize_ = true;
	bool Config :: decompose_ = true;
	bool Config :: computeDelta_ = false;
	bool Config :: write_ = true;

	// general flags
	bool Config :: generateRandomSource_ = false;
	bool Config :: keepSource_= false;
	bool Config :: removeComments_ = false;
	bool Config :: commentStuff_ = false;
	bool Config :: keepTermNames_ = false;
	bool Config :: outputToStdout_ = false;
	bool Config :: verify_ = false;
	value :: Integer
		Config :: partialDecompositionFactor_ = value :: undefined :: INTEGER;

	// memory options
	Size_t
		Config :: stackVolume_ = DEFAULT_STACK_VOLUME;

	// timing options
	Time_t
		Config :: maxSolveTime_ = DEFAULT_MAX_SOLVE_TIME;
	Time_t
		Config :: maxDecomposeTime_ = DEFAULT_MAX_DECOMPOSE_TIME;
	Time_t
		Config :: maxMinimizeTime_ = DEFAULT_MAX_MINIMIZE_TIME;
	Clock_t
		Config :: refreshClock_ = DEFAULT_REFRESH_CLOCK;

	// delta generation parameter
	value :: Integer
		Config :: deltaThreshold_ = DEFAULT_DELTA_THRESHOLD;
	Config :: DeltaGenerationMode
		Config :: deltaGenerationMode_ = DEFAULT_DELTA_GENERATION_MODE;

	// dynamic theory generation parameters
	value :: Integer
		Config :: sigmaConceptCount_ = DEFAULT_SIGMA_CONCEPT_COUNT;
	value :: Integer
		Config :: sigmaRelationCount_ = DEFAULT_SIGMA_RELATION_COUNT;
	value :: Integer
		Config :: deltaConceptCount_ = DEFAULT_DELTA_CONCEPT_COUNT;
	value :: Integer
		Config :: deltaRelationCount_ = DEFAULT_DELTA_RELATION_COUNT;
	value :: Integer
		Config :: termMaxLength_ = DEFAULT_TERM_MAX_LENGTH;
	value :: Integer
		Config :: termMaxDepth_ = DEFAULT_TERM_MAX_DEPTH;
	value :: Integer
		Config :: theorySize_ = DEFAULT_THEORY_SIZE;
	value :: Integer
		Config :: theoryCount_ = DEFAULT_THEORY_COUNT;

	// statistics output options
	bool Config :: showStatistics_ = false;

	// info output options
	bool Config :: showTimings_ = false;
	bool Config :: showMath_ = false;
	bool Config :: showVolume_ = false;
}
}

#endif /*DEL_AUXILIARY_CONFIG_CPP_*/
