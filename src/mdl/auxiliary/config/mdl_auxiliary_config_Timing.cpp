/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_Timing.cpp                          */
/* Description:     static class for mdl prover timings                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_CONFIG_TIMING_CPP_
#define MDL_AUXILIARY_CONFIG_TIMING_CPP_

namespace mdl {
namespace auxiliary {
namespace config {

	/****************************
	 *		Public members
	 ****************************/

	inline Time
	Timing :: getTimeLimit() {
		return timeOptions_ [TIME_LIMIT]->getTime();
	}
	inline Time
	Timing :: getRefreshTime() {
		return timeOptions_[REFRESH_TIME]->getTime();
	}

	inline option :: String&
	Timing :: getSampleTimePolynomial() {
		return *polynomialOptions_[SAMPLE_TIME_POLYNOMIAL];
	}
	inline option :: String&
	Timing :: getFrisTimePolynomial() {
		return *polynomialOptions_[FRIS_TIME_POLYNOMIAL];
	}
	inline option :: String&
	Timing :: getOptTimePolynomial() {
		return *polynomialOptions_[OPT_TIME_POLYNOMIAL];
	}

	template<class S>
	void
	Timing :: showUsageMessage (S& os, const List& groupList)
	{
		if (groupList.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int i = 0; i < TIME_OPTIONS_NUM; ++ i) {
				timeOptions_ [i]->showUsageMessage (os);
			}
			os << chars :: NEW_LINE;
			for (int i = 0; i < POLYNOMIAL_OPTIONS_NUM; ++ i) {
				polynomialOptions_ [i]->showUsageMessage (os);
			}
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	void
	Timing :: showOptionValues (S& os, const List& groupList)
	{
		if (groupList.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int i = 0; i < TIME_OPTIONS_NUM; ++ i) {
				timeOptions_ [i]->showOptionValues (os);
			}
			os << chars :: NEW_LINE;
			for (int i = 0; i < POLYNOMIAL_OPTIONS_NUM; ++ i) {
				polynomialOptions_ [i]->showOptionValues (os);
			}
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	inline void
	Timing :: showGroupName (S& os) {
		os << "\t" << optionGroupName_ << chars :: NEW_LINE;
	}

	/****************************
	 *		Protected members
	 ****************************/

	bool
	Timing :: proceedStringOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		for (int j = 0; j < TIME_OPTIONS_NUM; ++ j) {
			if (timeOptions_[j]->proceedStringOption (opt, argCount, argValues, i)) {
				return true;
			}
		}
		for (int j = 0; j < POLYNOMIAL_OPTIONS_NUM; ++ j) {
			if (polynomialOptions_[j]->proceedStringOption (opt, argCount, argValues, i)) {
				return true;
			}
		}
		return false;
	}
	bool
	Timing :: proceedOneCharOption (const char* opt, const int argCount, const char* argValues[], int& i) {
		return false;
	}

	bool
	Timing :: isCorrect()
	{
		for (int j = 0; j < TIME_OPTIONS_NUM; ++ j) {
			if (!timeOptions_[j]->isCorrect()) {
				return false;
			}
		}
		for (int j = 0; j < POLYNOMIAL_OPTIONS_NUM; ++ j) {
			if (!polynomialOptions_[j]->isCorrect()) {
				return false;
			}
		}
		return true;
	}

	inline void
	Timing :: init()
	{
		timeOptions_ [TIME_LIMIT]   = new option :: Time (defaultTimeLimit_,   "time-limit",   "max time for all purposes.");
		timeOptions_ [REFRESH_TIME] = new option :: Time (defaultRefreshTime_, "refresh-time", "screen status refresh time.");

		polynomialOptions_ [SAMPLE_TIME_POLYNOMIAL] = new option :: String ("", "sample-time-polynomial", "polynomial, used to estimate sample building time.");
		polynomialOptions_ [FRIS_TIME_POLYNOMIAL]   = new option :: String ("", "fris-time-polynomial",   "polynomial, used to estimate FRiS learning time.");
		polynomialOptions_ [OPT_TIME_POLYNOMIAL]    = new option :: String ("", "opt-time-polynomial",    "polynomial, used to estimate optimization learning.");
	}
	inline void
	Timing :: release()
	{
		for (int i = 0; i < TIME_OPTIONS_NUM; ++ i) {
			delete timeOptions_ [i];
			timeOptions_ [i] = NULL;
		}
		for (int i = 0; i < POLYNOMIAL_OPTIONS_NUM; ++ i) {
			delete polynomialOptions_ [i];
			polynomialOptions_ [i] = NULL;
		}
	}
	inline Size_t
	Timing :: getVolume()
	{
		Size_t volume = 0;
		for (int i = 0; i < TIME_OPTIONS_NUM; ++ i) {
			volume += object :: Object :: getAggregateVolume (timeOptions_ [i]);
		}
		for (int i = 0; i < POLYNOMIAL_OPTIONS_NUM; ++ i) {
			volume += object :: Object :: getAggregateVolume (polynomialOptions_ [i]);
		}
		return volume;
	}
	inline bool
	Timing :: initTimeLimit (const RunMode runMode)
	{
		switch (runMode) {
		case NO_WORK : break;
		case PROVE_WORK :
			if (!timeOptions_ [TIME_LIMIT]->isScaned()) {
				timeOptions_ [TIME_LIMIT]->setTime (defaultProveTimeLimit_);
			}
			break;
		case CHECK_WORK : break;
		case TRANSLATE_WORK : break;
		case COMPRESS_WORK :
			if (!timeOptions_ [TIME_LIMIT]->isScaned()) {
				timeOptions_ [TIME_LIMIT]->setTime (defaultCompressTimeLimit_);
			}
			break;
		case LOOKUP_WORK : break;
		case MINE_WORK : break;
		case REPROVE_WORK : break;
		case LEARN_WORK :
			if (!timeOptions_ [TIME_LIMIT]->isScaned()) {
				timeOptions_ [TIME_LIMIT]->setTime (defaultLearnTimeLimit_);
			}
			break;
		case TUNE_WORK : break;
			if (!timeOptions_ [TIME_LIMIT]->isScaned()) {
				timeOptions_ [TIME_LIMIT]->setTime (defaultTuneTimeLimit_);
			}
			break;
		case BENCHMARK_WORK : break;
		default : break;
		}
		return true;
	}

	/*************************************
	 *		Private static attributes
	 *************************************/

	option :: Time*   Timing :: timeOptions_  [TIME_OPTIONS_NUM];
	option :: String* Timing :: polynomialOptions_ [POLYNOMIAL_OPTIONS_NUM];

	Time Timing :: defaultProveTimeLimit_    = 1 * time :: MINUTE;
	Time Timing :: defaultCompressTimeLimit_ = 1 * time :: MINUTE;
	Time Timing :: defaultLearnTimeLimit_    = 5 * time :: MINUTE;
	Time Timing :: defaultTuneTimeLimit_     = 5 * time :: MINUTE;
	Time Timing :: defaultTimeLimit_         = 1 * time :: MINUTE;
	Time Timing :: defaultRefreshTime_       = 1 * time :: SECOND;

	const char* Timing :: optionGroupName_ = "timing";
}
}
}

#endif /*MDL_AUXILIARY_CONFIG_TIMING_CPP_*/
