/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_Real.hpp                            */
/* Description:     static class for real-valued prover factors              */
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

// Class which factor parameters for mdl prover.
class Real {
public :
	// mdl floating point factors enum type
	enum OptionType_ {
		// experience classifier factors
		DIST_LOC = 0,
		DIST_BAL = 1,
		CLAS_LOC = 2,
		UP_DOWN  = 3,
		REAL_OPTIONS_NUM = 4
	};

	static option :: Real& realOption (const OptionType_);
	static bool hasRealOption (const char*);
	static value :: Real getReal (const char*);
	static value :: Real getReal (const OptionType_);

	static value :: Real getDistanceLocalityFactor (const value :: Integer);
	static value :: Real getClassifierLocalityFactor (const value :: Integer);
	static value :: Real getDistanceBalanceFactor();
	static value :: Integer getDistanceLocalityBoundary();
	static value :: Integer getClassifierLocalityBoundary();

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

private :
	static void initFactors();
	typedef
		vector :: Vector
		<
			value :: Real,
			storage :: ByValue,
			allocator :: Standard
		>
		RealVector_;
	typedef
		vector :: Vector
		<
			option :: Real,
			storage :: ByPointer,
			allocator :: Standard
		>
		OptionVector_;

	enum {
		INITIAL_LOCALITY_CAPACITY = 16,
		INITIAL_OPTION_VECTOR_CAPACITY = 32
	};

	static option :: Real* realOptions_ [REAL_OPTIONS_NUM];
	static OptionVector_* optionVector_;

	static value :: Integer distanceLocalityBoundary_;
	static value :: Integer classifierLocalityBoundary_;
	static RealVector_* distanceLocalityFactors_;
	static RealVector_* classifierLocalityFactors_;
	static value :: Real epsilon_;

	static const char* optionGroupName_;
};

}
}
}


