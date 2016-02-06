/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_config_MemoryInfo.hpp                               */
/* Description:     memory info config flags                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "config/nstd_config_Base.hpp"

namespace nstd {
namespace config {

class MemoryInfo : public Base {
public :
	enum MemoryInfoOption_ {
		SHOW_MEMORY_INFO_ALL      = 0,
		SHOW_MEMORY_INFO_USAGE    = 1,
		SHOW_MEMORY_INFO_SUMMARY  = 2,
		SHOW_MEMORY_INFO_DETAILS  = 3,

		SHOW_MEMORY_INFO_HEAP     = 4,
		SHOW_MEMORY_INFO_STACK    = 5,
		SHOW_MEMORY_INFO_BOXED    = 6,
		SHOW_MEMORY_INFO_STANDARD = 7,

		SHOW_MEMORY_INFO_BALANCE  = 8,
		SHOW_MEMORY_INFO_DISPOSED = 9,
		SHOW_MEMORY_INFO_FRAGMENTATION = 10,
		OPTION_NUM  = 11
	};

	static option :: Bool& showMemory (MemoryInfoOption_);
	static bool showMemory();
	static bool showMemoryUsage();
	static bool showMemorySummary();
	static bool showMemoryDetails();

	static bool showMemoryHeap();
	static bool showMemoryStack();
	static bool showMemoryBoxed();
	static bool showMemoryStandard();

	static bool showMemoryBalance();
	static bool showMemoryDisposed();
	static bool showMemoryFragmentation();

	// Shows the usage message.
	template<class S>
	static void showUsageMessage (S&, const List& = List());
	template<class S>
	static void showOptionValues (S&, const List& = List());
	template<class S>
	static void showGroupName (S&);

protected :
	static void init();
	static void release();
	static Size_t getVolume();

	static bool proceedStringOption (const char* opt, const int argCount, const char* argValues[], int& i);
	static bool proceedOneCharOption (const char* opt, const int argCount, const char* argValues[], int& i);

private :
	static option :: Bool* memoryOptions_[OPTION_NUM];
	static const char* optionGroupName_;
};

}
}


