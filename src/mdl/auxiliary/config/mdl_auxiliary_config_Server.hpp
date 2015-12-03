/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_Server.hpp                          */
/* Description:     static class for mdl server parameters                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_CONFIG_SERVER_HPP_
#define MDL_AUXILIARY_CONFIG_SERVER_HPP_

#include "mdl/types/mdl_types.hpp"
#include "mdl/auxiliary/config/mdl_auxiliary_config.dpp"

namespace mdl {
namespace auxiliary {
namespace config {

class Server {
public :
	enum {
		SOCKET = 0,
		PORT   = 1,
		SERVER_OPTIONS_NUM  = 2
	};

	static value :: Integer serverSocket();
	static value :: Integer serverPort();

	template<class S>
	static void showUsageMessage (S&, const List& groupList = List());
	template<class S>
	static void showOptionValues (S&, const List& groupList = List());
	template<class S>
	static void showGroupName    (S&);

protected :
	static bool proceedStringOption (const char*, const int, const char* [], int&);
	static bool proceedOneCharOption (const char*, const int, const char* [], int&);

	static bool isCorrect();

	static void init();
	static void release();
	static Size_t getVolume();

private :
	static option :: Integer* serverOptions_ [SERVER_OPTIONS_NUM];
	static const char* optionGroupName_;
};

}
}
}

#endif /*MDL_AUXILIARY_CONFIG_SERVER_HPP_*/
