/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_Timing.hpp                          */
/* Description:     static class for mdl prover timings                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_CONFIG_TIMING_HPP_
#define MDL_AUXILIARY_CONFIG_TIMING_HPP_

#include "mdl/types/mdl_types.hpp"
#include "mdl/auxiliary/config/mdl_auxiliary_config.dpp"

namespace mdl {
namespace auxiliary {
namespace config {

class Timing {
public :
	enum {
		TIME_LIMIT        = 0,
		REFRESH_TIME      = 1,
		TIME_OPTIONS_NUM  = 2
	};

	// maximum time limit for all purposes, seconds
	static Time getTimeLimit();
	// Time for the refresh of the prover status, seconds
	static Time getRefreshTime();

	enum {
		SAMPLE_TIME_POLYNOMIAL = 0,
		FRIS_TIME_POLYNOMIAL   = 1,
		OPT_TIME_POLYNOMIAL    = 2,
		POLYNOMIAL_OPTIONS_NUM = 3
	};

	static option :: String& getSampleTimePolynomial();
	static option :: String& getFrisTimePolynomial();
	static option :: String& getOptTimePolynomial();

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

	static void init();
	static void release();
	static Size_t getVolume();
	static bool initTimeLimit (const RunMode);

private :
	static option :: Time*   timeOptions_  [TIME_OPTIONS_NUM];
	static option :: String* polynomialOptions_ [POLYNOMIAL_OPTIONS_NUM];

	static Time defaultProveTimeLimit_;
	static Time defaultCompressTimeLimit_;
	static Time defaultLearnTimeLimit_;
	static Time defaultTuneTimeLimit_;
	static Time defaultTimeLimit_;
	static Time defaultRefreshTime_;

	static const char* optionGroupName_;
};

}
}
}

#endif /*MDL_AUXILIARY_CONFIG_TIMING_HPP_*/
