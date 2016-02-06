/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_Refactor.hpp                        */
/* Description:     refactoring options                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/types/mdl_types.hpp"
#include "mdl/auxiliary/config/mdl_auxiliary_config.dpp"

namespace mdl {
namespace auxiliary {
namespace config {

class Refactor {
public :
	enum RefactoringJob_ {
		NO_REFACTORING      = 0,
		RENAME              = 1,
		MOVE                = 2,
		REDUCE              = 3,
		DEFAULT_REFACTORING_JOB = NO_REFACTORING
	};

	static RefactoringJob_ getRefactoringJob();

	static bool rename();
	static bool move();
	static bool reduce();

	static bool removeRedundantHypothesis();
	static bool removeRedundantProofSteps();
	static bool removeRedundantVariables();
	static bool removeRedundantAssertions();

	enum RefactoringOption_ {
		OPTION_RENAME                       = 0,
		OPTION_MOVE                         = 1,
		OPTION_REMOVE_REDUNDANT_ALL         = 2,
		OPTION_REMOVE_REDUNDANT_HYPOTHESIS  = 3,
		OPTION_REMOVE_REDUNDANT_PROOF_STEPS = 4,
		OPTION_REMOVE_REDUNDANT_VARIABLES   = 5,
		OPTION_REMOVE_REDUNDANT_ASSERTIONS  = 6,

		OPTION_FROM                         = 7,
		OPTION_FROM_BEGIN                   = 8,
		OPTION_FROM_END                     = 9,

		OPTION_TO                           = 10,
		OPTION_TO_BEGIN                     = 11,
		OPTION_TO_END                       = 12,

		OPTION_ID                           = 13,
		OPTION_ID_BEGIN                     = 14,
		OPTION_ID_END                       = 15,

		OPTION_DEEP_REFACTORING             = 16,
		OPTION_CHECK_BEFORE_REFACTORING     = 17,

		REFACTORING_OPTIONS_NUM             = 18
	};

	static bool deepRefactoring();
	static bool checkBeforeRefactoring();

	static vector :: String* refactorFrom();
	static vector :: String* refactorTo();
	static vector :: String* refactorId();

	template<class S>
	static void showUsageMessage (S&, const List& groupList = List());
	template<class S>
	static void showOptionValues (S&, const List& groupList = List());
	template<class S>
	static void showGroupName (S&);

protected :
	static bool proceedStringOption (const char*, const int, const char* [], int&);
	static bool proceedOneCharOption (const char*, const int, const char* [], int&);

	static bool isCorrect();
	static bool isConsistent();

	static void init();
	static void release();
	static Size_t getVolume();

private :
	enum {
		INITIAL_STRING_VECTOR_CAPACITY = 32
	};

	static void proceedStringGroup
	(
		const int argCount,
		const char* argValues[],
		int& i,
		vector :: String* stringVector,
		const option :: Bool* groupBegin,
		const option :: Bool* groupEnd
	);

	static option :: Bool* refactoringOptions_ [REFACTORING_OPTIONS_NUM];
	static vector :: String* from_;
	static vector :: String* to_;
	static vector :: String* id_;
	static bool isConsistent_;
	static const char* optionGroupName_;
};

}
}
}


