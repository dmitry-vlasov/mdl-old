/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_Concurrency.cpp                     */
/* Description:     concurrency options                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_CONFIG_CONCURENCY_CPP_
#define MDL_AUXILIARY_CONFIG_CONCURENCY_CPP_

namespace mdl {
namespace auxiliary {
namespace config {

	/****************************
	 *		Public members
	 ****************************/

	option :: Integer&
	Concurrency :: getConcurrencyOption (const ConcurrencyOption_ o) {
		return *concurrencyOptions_ [o];
	}
	value :: Integer
	Concurrency :: getConcurrency (const ConcurrencyOption_ o) {
		return concurrencyOptions_ [o]->getValue();
	}

	template<class S>
	void
	Concurrency :: showUsageMessage (S& os, const List& groupList)
	{
		if (groupList.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int i = 0; i < CONCURENCY_OPTIONS_NUM; ++ i) {
				concurrencyOptions_[i]->showUsageMessage (os);
			}
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	void
	Concurrency :: showOptionValues (S& os, const List& groupList)
	{
		if (groupList.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int i = 0; i < CONCURENCY_OPTIONS_NUM; ++ i) {
				concurrencyOptions_[i]->showOptionValues (os);
			}
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	inline void
	Concurrency :: showGroupName (S& os) {
		os << "\t" << optionGroupName_ << chars :: NEW_LINE;
	}

	/****************************
	 *		Protected members
	 ****************************/

	bool
	Concurrency :: proceedStringOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		for (int k = 0; k < CONCURENCY_OPTIONS_NUM; ++ k) {
			if (concurrencyOptions_[k]->proceedStringOption (opt, argCount, argValues, i)) {
				return true;
			}
		}
		return false;
	}
	bool
	Concurrency :: proceedOneCharOption (const char* opt, const int argCount, const char* argValues[], int& i) {
		return false;
	}

	bool
	Concurrency :: isCorrect()
	{
		for (int i = 0; i < CONCURENCY_OPTIONS_NUM; ++ i) {
			if (!concurrencyOptions_[i]->isCorrect()) {
				return false;
			}
		}
		return true;
	}

	inline void
	Concurrency :: init ()
	{
		concurrencyOptions_ [PROCESSES] = new option :: Integer (4, "processes", "use <int> processes.");
		concurrencyOptions_ [THREADS]   = new option :: Integer (4, "threads",   "use <int> threads in each process.");
	}
	inline void
	Concurrency :: release()
	{
		for (value :: Integer i = 0; i < CONCURENCY_OPTIONS_NUM; ++ i) {
			delete concurrencyOptions_ [i];
			concurrencyOptions_ [i] = NULL;
		}
	}
	inline Size_t
	Concurrency :: getVolume()
	{
		Size_t volume = 0;
		for (value :: Integer i = 0; i < CONCURENCY_OPTIONS_NUM; ++ i) {
			volume += object :: Object :: getAggregateVolume (concurrencyOptions_ [i]);
		}
		return volume;
	}

	/*************************************
	 *		Private static attributes
	 *************************************/

	option :: Integer* Concurrency :: concurrencyOptions_ [CONCURENCY_OPTIONS_NUM];
	const char* Concurrency :: optionGroupName_ = "concurrency";
}
}
}

#endif /*MDL_AUXILIARY_CONFIG_CONCURENCY_CPP_*/
