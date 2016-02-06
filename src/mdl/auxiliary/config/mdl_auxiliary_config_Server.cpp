/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_Server.cpp                          */
/* Description:     static class for mdl server parameters                   */
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

	inline value :: Integer
	Server :: serverSocket() {
		return serverOptions_ [SOCKET]->getValue();
	}
	inline value :: Integer
	Server :: serverPort() {
		return serverOptions_ [PORT]->getValue();
	}

	template<class S>
	void
	Server :: showUsageMessage (S& os, const List& groupList)
	{
		if (groupList.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int i = 0; i < SERVER_OPTIONS_NUM; ++ i) {
				serverOptions_ [i]->showUsageMessage (os);
			}
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	void
	Server :: showOptionValues (S& os, const List& groupList)
	{
		if (groupList.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int i = 0; i < SERVER_OPTIONS_NUM; ++ i) {
				serverOptions_ [i]->showOptionValues (os);
			}
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	inline void
	Server :: showGroupName (S& os) {
		os << "\t" << optionGroupName_ << chars :: NEW_LINE;
	}

	/****************************
	 *		Protected members
	 ****************************/

	bool
	Server :: proceedStringOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		for (int j = 0; j < SERVER_OPTIONS_NUM; ++ j) {
			if (serverOptions_[j]->proceedStringOption (opt, argCount, argValues, i)) {
				return true;
			}
		}
		return false;
	}
	bool
	Server :: proceedOneCharOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		for (int j = 0; j < SERVER_OPTIONS_NUM; ++ j) {
			if (serverOptions_[j]->proceedOneCharOption (opt, argCount, argValues, i)) {
				return true;
			}
		}
		return false;
	}

	bool
	Server :: isCorrect()
	{
		for (int i = 0; i < SERVER_OPTIONS_NUM; ++ i) {
			if (!serverOptions_ [i]->isCorrect()) {
				return false;
			}
		}
		return true;
	}

	inline void
	Server :: init ()
	{
		serverOptions_ [SOCKET] = new option :: Integer (0,    "socket", "mdl server socket.");
		serverOptions_ [PORT]   = new option :: Integer (1872, "port",   "mdk server port");
	}
	inline void
	Server :: release()
	{
		for (int i = 0; i < SERVER_OPTIONS_NUM; ++ i) {
			delete serverOptions_ [i];
			serverOptions_ [i] = NULL;
		}
	}
	inline Size_t
	Server :: getVolume()
	{
		Size_t volume = 0;
		for (int i = 0; i < SERVER_OPTIONS_NUM; ++ i) {
			volume += object :: Object :: getAggregateVolume (serverOptions_ [i]);
		}
		return volume;
	}

	/*************************************
	 *		Private static attributes
	 *************************************/

	option :: Integer* Server :: serverOptions_ [SERVER_OPTIONS_NUM];

	const char* Server :: optionGroupName_ = "server";
}
}
}


