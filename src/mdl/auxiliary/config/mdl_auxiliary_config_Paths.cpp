/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_Paths.cpp                           */
/* Description:     path options                                             */
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

	inline Paths :: Path_&
	Paths :: universe() {
		return pathOptions_[UNIVERSE_PATH]->value();
	}
	inline const Paths :: Path_&
	Paths :: getUniverse() {
		return pathOptions_[UNIVERSE_PATH]->getValue();
	}

	template<class S>
	void
	Paths :: showUsageMessage (S& os, const List& groupList)
	{
		if (groupList.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int i = 0; i < PATHS_NUM; ++ i) {
				pathOptions_[i]->showUsageMessage (os);
			}
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	void
	Paths :: showOptionValues (S& os, const List& groupList)
	{
		if (groupList.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int i = 0; i < PATHS_NUM; ++ i) {
				pathOptions_[i]->showOptionValues (os);
			}
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	inline void
	Paths :: showGroupName (S& os) {
		os << "\t" << optionGroupName_ << chars :: NEW_LINE;
	}

	/****************************
	 *		Protected members
	 ****************************/

using std :: endl;
using std :: cout;

	bool
	Paths :: proceedStringOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		for (int j = 0; j < PATHS_NUM; ++ j) {
			if (pathOptions_[j]->proceedStringOption (opt, argCount, argValues, i)) {
				return true;
			}
		}
		return false;
	}
	inline bool
	Paths :: proceedOneCharOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		for (int j = 0; j < PATHS_NUM; ++ j) {
			if (pathOptions_[j]->proceedOneCharOption (opt, argCount, argValues, i)) {
				return true;
			}
		}
		return false;
	}

	inline bool
	Paths :: isCorrect() {
		return true;
	}

	inline void
	Paths :: init () {
		pathOptions_[UNIVERSE_PATH] = new option :: Path ("universe", "universe file for all math.");
	}
	void
	Paths :: release ()
	{
		for (int i = 0; i < PATHS_NUM; ++ i) {
			delete pathOptions_ [i];
			pathOptions_ [i] = NULL;
		}
	}
	Size_t
	Paths :: getVolume()
	{
		Size_t volume = 0;
		for (int i = 0; i < PATHS_NUM; ++ i) {
			volume += object :: Object :: getAggregateVolume (pathOptions_ [i]);
		}
		return volume;
	}
	bool
	Paths :: checkPaths()
	{
		if (!checkUniverse()) {
			return false;
		}
		return true;
	}

	/****************************
	 *		Private members
	 ****************************/

	bool
	Paths :: checkUniverse()
	{
		if (getUniverse().isUndefined()) {
			return true;
		}
		if (!getUniverse().isFile()) {
			cout << "universe: " << getUniverse() << " is not a file." << endl;
			return false;
		}
		const Size_t
			universeSize = system :: getFileSize (getUniverse().getString().c_str());
		if (universeSize == 0) {
			cout << "universe file: " << getUniverse() << " is empty." << endl;
			return false;
		}
		if (universeSize == Undefined<Size_t> :: getValue()) {
			cout << "universe file: " << getUniverse() << " is not found." << endl;
			return false;
		}
		return true;
	}

	/************************************
	 *		Static private attributes
	 ************************************/

	option :: Path* Paths :: pathOptions_[PATHS_NUM];
	const char* Paths :: optionGroupName_ = "mdl_paths";
}
}
}


