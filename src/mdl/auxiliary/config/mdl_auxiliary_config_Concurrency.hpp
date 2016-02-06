/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_Concurrency.hpp                     */
/* Description:     concurrency options                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/types/mdl_types.hpp"

namespace mdl {
namespace auxiliary {
namespace config {

class Concurrency {
public :
	enum ConcurrencyOption_ {
		PROCESSES              = 0,
		THREADS                = 1,
		CONCURENCY_OPTIONS_NUM = 2
	};

	static option :: Integer& getConcurrencyOption (const ConcurrencyOption_);
	static value :: Integer getConcurrency (const ConcurrencyOption_);

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
	static option :: Integer* concurrencyOptions_ [CONCURENCY_OPTIONS_NUM];
	static const char* optionGroupName_;
};

}
}
}


