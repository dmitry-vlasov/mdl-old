/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_Real.cpp                            */
/* Description:     static class for real-valued prover factors              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_CONFIG_REAL_CPP_
#define MDL_AUXILIARY_CONFIG_REAL_CPP_

namespace mdl {
namespace auxiliary {
namespace config {

	/****************************
	 *		Public members
	 ****************************/

	option :: Real&
	Real :: realOption (const OptionType_ t) {
		return *realOptions_ [t];
	}
	bool
	Real :: hasRealOption (const char* name)
	{
		for (int k = 0; k < REAL_OPTIONS_NUM; ++ k) {
			if (nstd :: config :: Base :: equalStrings (realOptions_[k]->getName(), name)) {
				return true;
			}
		}
		for (int k = 0; k < optionVector_->getSize(); ++ k) {
			if (nstd :: config :: Base :: equalStrings (optionVector_->getValue(k)->getName(), name)) {
				return true;
			}
		}
		return false;
	}
	value :: Real
	Real :: getReal (const char* name)
	{
		for (int k = 0; k < REAL_OPTIONS_NUM; ++ k) {
			if (nstd :: config :: Base :: equalStrings (realOptions_[k]->getName(), name)) {
				return realOptions_[k]->getValue();
			}
		}
		for (int k = 0; k < optionVector_->getSize(); ++ k) {
			if (nstd :: config :: Base :: equalStrings (optionVector_->getValue(k)->getName(), name)) {
				return optionVector_->getValue(k)->getValue();
			}
		}
		return 0;
	}
	value :: Real
	Real :: getReal (const OptionType_ t) {
		return realOptions_ [t]->getValue();
	}

	// floating factors for prover
	inline
	value :: Real
	Real :: getDistanceLocalityFactor (const value :: Integer i) {
		return distanceLocalityFactors_->getValue (i);
	}
	inline value :: Real
	Real :: getClassifierLocalityFactor (const value :: Integer i) {
		return classifierLocalityFactors_->getValue (i);
	}
	inline value :: Real
	Real :: getDistanceBalanceFactor() {
		return realOptions_ [DIST_BAL]->getValue();
	}
	inline value :: Integer
	Real :: getDistanceLocalityBoundary() {
		return distanceLocalityBoundary_;
	}
	inline value :: Integer
	Real :: getClassifierLocalityBoundary() {
		return classifierLocalityBoundary_;
	}

	template<class S>
	void
	Real :: showUsageMessage (S& os, const List& groupList)
	{
		if (groupList.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int i = 0; i < REAL_OPTIONS_NUM; ++ i) {
				realOptions_[i]->showUsageMessage (os);
			}
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	void
	Real :: showOptionValues (S& os, const List& groupList)
	{
		if (groupList.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int i = 0; i < REAL_OPTIONS_NUM; ++ i) {
				realOptions_[i]->showOptionValues (os);
			}
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	inline void
	Real :: showGroupName (S& os) {
		os << "\t" << optionGroupName_ << chars :: NEW_LINE;
	}

	/****************************
	 *		Protected members
	 ****************************/

	bool
	Real :: proceedStringOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		for (int k = 0; k < REAL_OPTIONS_NUM; ++ k) {
			if (realOptions_[k]->proceedStringOption (opt, argCount, argValues, i)) {
				return true;
			}
		}
		initFactors();
		option :: Real* realOption = new option :: Real();
		if (realOption->proceedStringOption (opt, argCount, argValues, i)) {
			optionVector_->add (realOption);
			return true;
		} else {
			delete realOption;
		}
		return false;
	}
	bool
	Real :: proceedOneCharOption (const char* opt, const int argCount, const char* argValues[], int& i) {
		return false;
	}

	bool
	Real :: isCorrect()
	{
		for (int i = 0; i < REAL_OPTIONS_NUM; ++ i) {
			if (!realOptions_[i]->isCorrect()) {
				return false;
			}
		}
		return true;
	}

	inline void
	Real :: init ()
	{
		distanceLocalityFactors_ = new RealVector_ (INITIAL_LOCALITY_CAPACITY);
		classifierLocalityFactors_ = new RealVector_ (INITIAL_LOCALITY_CAPACITY);
		realOptions_ [DIST_LOC] = new option :: Real (0.3, "factor-dist-loc",     "distance locality.");
		realOptions_ [DIST_BAL] = new option :: Real (0.5, "factor-dist-bal",     "distance balance.");
		realOptions_ [CLAS_LOC] = new option :: Real (0.3, "factor-clas-loc",     "classifier locality.");
		realOptions_ [UP_DOWN]  = new option :: Real (16,  "factor-up-down",      "up/down tree balance.");
		optionVector_ = new OptionVector_ (INITIAL_OPTION_VECTOR_CAPACITY);
	}
	inline void
	Real :: release()
	{
		delete distanceLocalityFactors_;
		delete classifierLocalityFactors_;
		distanceLocalityFactors_ = NULL;
		classifierLocalityFactors_ = NULL;
		for (value :: Integer i = 0; i < REAL_OPTIONS_NUM; ++ i) {
			delete realOptions_ [i];
			realOptions_ [i] = NULL;
		}
		delete optionVector_;
		optionVector_ = NULL;
	}
	inline Size_t
	Real :: getVolume()
	{
		Size_t volume = 0;
		volume += object :: Object :: getAggregateVolume (optionVector_);
		volume += object :: Object :: getAggregateVolume (distanceLocalityFactors_);
		volume += object :: Object :: getAggregateVolume (classifierLocalityFactors_);
		for (value :: Integer i = 0; i < REAL_OPTIONS_NUM; ++ i) {
			volume += object :: Object :: getAggregateVolume (realOptions_ [i]);
		}
		return volume;
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Real :: initFactors()
	{
		distanceLocalityBoundary_ = 0;
		const value :: Real dist_q = realOptions_ [DIST_LOC]->getValue();
		value :: Real dist_factor = 1;
		while (dist_factor > epsilon_) {
			distanceLocalityFactors_->add (dist_factor);
			++ distanceLocalityBoundary_;
			dist_factor *= dist_q;
		}
		classifierLocalityBoundary_ = 0;
		const value :: Real class_q = realOptions_ [CLAS_LOC]->getValue();
		value :: Real class_factor = 1;
		while (class_factor > epsilon_) {
			classifierLocalityFactors_->add (class_factor);
			++ classifierLocalityBoundary_;
			class_factor *= class_q;
		}
	}

	/*************************************
	 *		Private static attributes
	 *************************************/

	option :: Real* Real :: realOptions_ [REAL_OPTIONS_NUM];
	Real :: OptionVector_* Real :: optionVector_ = NULL;

	value :: Integer Real :: distanceLocalityBoundary_ = 3;
	value :: Integer Real :: classifierLocalityBoundary_ = 3;

	Real :: RealVector_*
		Real :: distanceLocalityFactors_ = NULL;
	Real :: RealVector_*
		Real :: classifierLocalityFactors_ = NULL;
	value :: Real
		Real :: epsilon_ = 0.05;

	const char* Real :: optionGroupName_ = "real_options";
}
}
}

#endif /*MDL_AUXILIARY_CONFIG_REAL_CPP_*/
