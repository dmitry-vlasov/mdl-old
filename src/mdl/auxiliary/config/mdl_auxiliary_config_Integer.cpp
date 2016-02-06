/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_Integer.cpp                         */
/* Description:     static class for integer mdl prover factors              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace auxiliary {
namespace config {

	/****************************
	 *		Public members
	 ****************************/

	option :: Integer&
	Integer :: getIntegerOption (const IntegerOption_ o) {
		return *integerOptions_ [o];
	}
	value :: Integer
	Integer :: getInteger (const IntegerOption_ o) {
		return integerOptions_ [o]->getValue();
	}

	template<class S>
	void
	Integer :: showUsageMessage (S& os, const List& groupList)
	{
		if (groupList.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int i = 0; i < INTEGER_OPTIONS_NUM; ++ i) {
				integerOptions_[i]->showUsageMessage (os);
			}
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	void
	Integer :: showOptionValues (S& os, const List& groupList)
	{
		if (groupList.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int i = 0; i < INTEGER_OPTIONS_NUM; ++ i) {
				integerOptions_[i]->showOptionValues (os);
			}
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	inline void
	Integer :: showGroupName (S& os) {
		os << "\t" << optionGroupName_ << chars :: NEW_LINE;
	}

	/****************************
	 *		Protected members
	 ****************************/

	bool
	Integer :: proceedStringOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		for (int k = 0; k < INTEGER_OPTIONS_NUM; ++ k) {
			if (integerOptions_[k]->proceedStringOption (opt, argCount, argValues, i)) {
				return true;
			}
		}
		return false;
	}
	bool
	Integer :: proceedOneCharOption (const char* opt, const int argCount, const char* argValues[], int& i) {
		return false;
	}

	bool
	Integer :: isCorrect()
	{
		for (int i = 0; i < INTEGER_OPTIONS_NUM; ++ i) {
			if (!integerOptions_[i]->isCorrect()) {
				return false;
			}
		}
		return true;
	}

	inline void
	Integer :: init ()
	{
		integerOptions_ [PRECISION]   = new option :: Integer (5,  "precision",   "precision of parameters while learning.");
		integerOptions_ [GROUPING]    = new option :: Integer (5,  "grouping",    "number of groups of learning.");
		integerOptions_ [THRESHOLD]   = new option :: Integer (10, "threshold",   "fris threshold.");
		integerOptions_ [SAMPLE_SIZE] = new option :: Integer (20, "sample-size", "sample size for fitness evaluation.");
		integerOptions_ [INDEX]       = new option :: Integer (-1, "index",       "index of a proof variant tree node. Used to grow it up.");
	}
	inline void
	Integer :: release()
	{
		for (value :: Integer i = 0; i < INTEGER_OPTIONS_NUM; ++ i) {
			delete integerOptions_ [i];
			integerOptions_ [i] = NULL;
		}
	}
	inline Size_t
	Integer :: getVolume()
	{
		Size_t volume = 0;
		for (value :: Integer i = 0; i < INTEGER_OPTIONS_NUM; ++ i) {
			volume += object :: Object :: getAggregateVolume (integerOptions_ [i]);
		}
		return volume;
	}

	/*************************************
	 *		Private static attributes
	 *************************************/

	option :: Integer* Integer :: integerOptions_ [INTEGER_OPTIONS_NUM];
	const char* Integer :: optionGroupName_ = "integer_options";
}
}
}


