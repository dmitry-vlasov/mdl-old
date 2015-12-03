/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_String.cpp                          */
/* Description:     static class for string prover options                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_CONFIG_STRING_CPP_
#define MDL_AUXILIARY_CONFIG_STRING_CPP_

namespace mdl {
namespace auxiliary {
namespace config {

	/****************************
	 *		Public members
	 ****************************/

	option :: String*
	String :: stringOption (const char* name)
	{
		for (int k = 0; k < optionVector_->getSize(); ++ k) {
			if (nstd :: config :: Base :: equalStrings (optionVector_->getValue(k)->getName(), name)) {
				return optionVector_->getValue(k);
			}
		}
		return NULL;
	}
	bool
	String :: hasStringOption (const char* name)
	{
		for (int k = 0; k < optionVector_->getSize(); ++ k) {
			if (nstd :: config :: Base :: equalStrings (optionVector_->getValue(k)->getName(), name)) {
				return true;
			}
		}
		return false;
	}
	const String :: String_*
	String :: getString (const char* name)
	{
		for (int k = 0; k < optionVector_->getSize(); ++ k) {
			if (nstd :: config :: Base :: equalStrings (optionVector_->getValue(k)->getName(), name)) {
				return &optionVector_->getValue(k)->getValue();
			}
		}
		return NULL;
	}

	template<class S>
	void
	String :: showUsageMessage (S& os, const List& groupList)
	{
		/*if (groupList.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << std :: endl;
			for (int i = 0; i < CONCURENCY_OPTIONS_NUM; ++ i) {
				concurrencyOptions_[i]->showUsageMessage (os);
			}
			os << std :: endl;
		}*/
	}
	template<class S>
	void
	String :: showOptionValues (S& os, const List& groupList)
	{
		/*if (groupList.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << std :: endl;
			for (int i = 0; i < CONCURENCY_OPTIONS_NUM; ++ i) {
				concurrencyOptions_[i]->showOptionValuesshowOptionValues (os);
			}
			os << std :: endl;
		}*/
	}
	template<class S>
	inline void
	String :: showGroupName (S& os) {
		//os << "\t" << optionGroupName_ << std :: endl;
	}

	/****************************
	 *		Protected members
	 ****************************/

	bool
	String :: proceedStringOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		option :: String* realOption = new option :: String();
		if (realOption->proceedStringOption (opt, argCount, argValues, i)) {
			optionVector_->add (realOption);
			return true;
		} else {
			delete realOption;
		}
		return false;
	}
	inline bool
	String :: proceedOneCharOption (const char* opt, const int argCount, const char* argValues[], int& i) {
		return false;
	}

	inline bool
	String :: isCorrect() {
		return true;
	}

	inline void
	String :: init() {
		optionVector_ = new OptionVector_ (INITIAL_OPTION_VECTOR_CAPACITY);
	}
	inline void
	String :: release()
	{
		delete optionVector_;
		optionVector_ = NULL;
	}
	inline Size_t
	String :: getVolume()
	{
		Size_t volume = 0;
		volume += object :: Object :: getAggregateVolume (optionVector_);
		return volume;
	}

	/*************************************
	 *		Private static attributes
	 *************************************/

	String :: OptionVector_* String :: optionVector_ = NULL;
	const char* String :: optionGroupName_ = "string";
}
}
}

#endif /*MDL_AUXILIARY_CONFIG_STRING_CPP_*/
