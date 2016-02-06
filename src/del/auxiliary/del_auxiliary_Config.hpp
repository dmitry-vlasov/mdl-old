/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File name:       del_auxiliary_Config.hpp                                 */
/* Description:     static class for command line arguments                  */
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

class Config : public nstd :: Config<Config> {
	typedef nstd :: Config<Config> Ancestor_;
public :
	typedef int Percent_;

	enum Format {
		DEL_FORMAT     = 0,
		MAN_FORMAT     = 1,
		FUNC_FORMAT    = 2,
		DEFAULT_FORMAT = DEL_FORMAT
	};

	// format of the source file
	static Format inputFormat();
	// translate output to the given format
	static Format outputFormat();

	// translate source
	static bool translate();
	// solve questions
	static bool solve();
	// minimize theories
	static bool minimize();
	// decompose theories
	static bool decompose();
	// compute delta signature
	static bool computeDelta();
	// write the output
	static bool write();

	// generate random source
	static bool generateRandomSource();
	// keep Source
	static bool keepSource();
	// Comments are removed at translation.
	static bool removeComments();
	// comment OWL stuff at translation
	static bool commentStuff();
	// keep term names in symbols of definiton
	static bool keepTermNames();
	// to standard output
	static bool outputToStdout();
	// verify result of decomposition
	static bool verify();
	// decompose a theory partially
	static value :: Integer partialDecompositionFactor();

	// volume for stack memory space
	static Size_t getStackVolume();

	// maximum time for solving procedure, seconds
	static Time_t getMaxSolveTime();
	// maximum time for decomposing procedure, seconds
	static Time_t getMaxDecomposeTime();
	// maximum time for minimizing procedure, seconds
	static Time_t getMaxMinimizeTime();
	// refresh cycle clock
	static Clock_t getRefreshClock();

	enum DeltaGenerationMode {
		PERCENT_OF_MAX_COHESION       = 0,
		PERCENT_OF_RELATIVE_COHESION  = 1,
		DEFAULT_DELTA_GENERATION_MODE = PERCENT_OF_MAX_COHESION
	};
	// delta generation paramete: percent
	static value :: Integer getDeltaThreshold();
	static DeltaGenerationMode getDeltaGenerationMode();

	// dynamic theory generation parameters
	static value :: Integer getSigmaConceptCount();
	static value :: Integer getSigmaRelationCount();
	static value :: Integer getDeltaConceptCount();
	static value :: Integer getDeltaRelationCount();
	static value :: Integer getTermMaxLength();
	static value :: Integer getTermMaxDepth();
	static value :: Integer getTheorySize();
	static value :: Integer getTheoryCount();

	// statistics output options
	static bool showStatistics();

	// info output options
	static bool showTimings();
	static bool showMath();
	static bool showVolume();

	static bool proceed (const int, const char* []);
	static bool proceedStringOption (const char*, const int, const char* [], int&);
	static bool proceedOneCharOption (const char*, const int, const char* [], int&);

	static void release();
	static Size_t getVolume();

private :
	enum {
		MEMORY_UNIT_SIZE = nstd :: size :: MEGABYTE,
		DEFAULT_STACK_VOLUME = 64,                // in memory units
		DEFAULT_MAX_SOLVE_TIME = 600,             // minutes
		DEFAULT_MAX_DECOMPOSE_TIME = 600,         // minutes
		DEFAULT_MAX_MINIMIZE_TIME = 600,          // minutes
		DEFAULT_REFRESH_CLOCK = 10 * 1000,        // milliseconds
		DEFAULT_QUANTUM_CLOCK = 10000,            // microseconds
		DEFAULT_DELTA_THRESHOLD = 60              // delta = % of most connected symbols
	};
	enum {
		DEFAULT_SIGMA_CONCEPT_COUNT = 4,
		DEFAULT_SIGMA_RELATION_COUNT = 2,
		DEFAULT_DELTA_CONCEPT_COUNT = 3,
		DEFAULT_DELTA_RELATION_COUNT = 2,
		DEFAULT_TERM_MAX_LENGTH = 12,
		DEFAULT_TERM_MAX_DEPTH = 4,
		DEFAULT_THEORY_SIZE = 10,
		DEFAULT_THEORY_COUNT = 10
	};

	static void showUsageMessage();
	static void init();

	static bool initMemorySize();
	static bool initTimes();
	static bool isConsistent();
	static bool checkPaths();
	static bool analyseArguments();

	// input/output format
	static Format inputFormat_;
	static Format outputFormat_;

	// main actions
	static bool translate_;
	static bool solve_;
	static bool minimize_;
	static bool decompose_;
	static bool computeDelta_;
	static bool write_;

	// general flags
	static bool generateRandomSource_;
	static bool keepSource_;
	static bool removeComments_;
	static bool commentStuff_;
	static bool keepTermNames_;
	static bool outputToStdout_;
	static bool verify_;
	static value :: Integer partialDecompositionFactor_;

	// memory options
	static Size_t stackVolume_;

	// timing options
	static Time_t maxSolveTime_;
	static Time_t maxDecomposeTime_;
	static Time_t maxMinimizeTime_;
	static Clock_t refreshClock_;

	// delta generation parameter
	static value :: Integer deltaThreshold_;
	static DeltaGenerationMode deltaGenerationMode_;

	// dynamic theory generation parameters
	static value :: Integer sigmaConceptCount_;
	static value :: Integer sigmaRelationCount_;
	static value :: Integer deltaConceptCount_;
	static value :: Integer deltaRelationCount_;
	static value :: Integer termMaxLength_;
	static value :: Integer termMaxDepth_;
	static value :: Integer theorySize_;
	static value :: Integer theoryCount_;

	// statistics output options
	static bool showStatistics_;

	// info output options
	static bool showTimings_;
	static bool showMath_;
	static bool showVolume_;
};

}
}


