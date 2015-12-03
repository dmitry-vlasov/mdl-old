/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_config_MemoryInfo.cpp                               */
/* Description:     memory info config flags                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONFIG_MEMORY_INFO_CPP_
#define NSTD_CONFIG_MEMORY_INFO_CPP_

namespace nstd {
namespace config {

	/****************************
	 *		Public members
	 ****************************/

	option :: Bool&
	MemoryInfo :: showMemory (MemoryInfoOption_ index) {
		return *memoryOptions_[index];
	}
	inline bool
	MemoryInfo :: showMemory()
	{
		return
			showMemorySummary()  ||
			showMemoryDetails()  ||
			showMemoryHeap()     ||
			showMemoryStack()    ||
			showMemoryBoxed()    ||
			showMemoryStandard() ||
			showMemoryDisposed() ||
			showMemoryFragmentation();
	}
	inline bool
	MemoryInfo :: showMemoryUsage() {
		return memoryOptions_[SHOW_MEMORY_INFO_USAGE]->getValue();
	}
	inline bool
	MemoryInfo :: showMemorySummary() {
		return memoryOptions_[SHOW_MEMORY_INFO_SUMMARY]->getValue();
	}
	inline bool
	MemoryInfo :: showMemoryDetails() {
		return memoryOptions_[SHOW_MEMORY_INFO_DETAILS]->getValue();
	}

	inline bool
	MemoryInfo :: showMemoryHeap() {
		return memoryOptions_[SHOW_MEMORY_INFO_HEAP]->getValue();
	}
	inline bool
	MemoryInfo :: showMemoryStack() {
		return memoryOptions_[SHOW_MEMORY_INFO_STACK]->getValue();
	}
	inline bool
	MemoryInfo :: showMemoryBoxed() {
		return memoryOptions_[SHOW_MEMORY_INFO_BOXED]->getValue();
	}
	inline bool
	MemoryInfo :: showMemoryStandard() {
		return memoryOptions_[SHOW_MEMORY_INFO_STANDARD]->getValue();
	}

	inline bool
	MemoryInfo :: showMemoryBalance() {
		return memoryOptions_[SHOW_MEMORY_INFO_BALANCE]->getValue();
	}
	inline bool
	MemoryInfo :: showMemoryDisposed() {
		return memoryOptions_[SHOW_MEMORY_INFO_DISPOSED]->getValue();
	}
	inline bool
	MemoryInfo :: showMemoryFragmentation() {
		return memoryOptions_[SHOW_MEMORY_INFO_FRAGMENTATION]->getValue();
	}

	template<class S>
	void
	MemoryInfo :: showUsageMessage (S& os, const List& list)
	{
		if (!list.contains (optionGroupName_)) {
			return;
		}
		os << optionGroupName_ << ':' << chars :: NEW_LINE;
		for (int j = 0; j < OPTION_NUM; ++ j) {
			memoryOptions_[j]->showUsageMessage (os);
		}
		os << chars :: NEW_LINE;
	}
	template<class S>
	void
	MemoryInfo :: showOptionValues (S& os, const List& list)
	{
		if (list.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int j = 0; j < OPTION_NUM; ++ j) {
				memoryOptions_[j]->showOptionValues (os);
			}
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	inline void
	MemoryInfo :: showGroupName (S& os) {
		os << "\t" << optionGroupName_ << chars :: NEW_LINE;
	}

	/****************************
	 *		Protected members
	 ****************************/

using std :: cout;
using std :: endl;

	inline void
	MemoryInfo :: init()
	{
		memoryOptions_[SHOW_MEMORY_INFO_ALL]      = new option :: Bool (false, "mem-all",      "show all memory usage info (except for  --mem-fragmentation)");
		memoryOptions_[SHOW_MEMORY_INFO_USAGE]    = new option :: Bool (false, "mem-usage",    "show memory usage info");
		memoryOptions_[SHOW_MEMORY_INFO_SUMMARY]  = new option :: Bool (false, "mem-summary",  "show brief memory allocation info");
		memoryOptions_[SHOW_MEMORY_INFO_DETAILS]  = new option :: Bool (false, "mem-details",  "show detailed memory allocation info");

		memoryOptions_[SHOW_MEMORY_INFO_HEAP]     = new option :: Bool (false, "mem-heap",     "show heap memory allocation info");
		memoryOptions_[SHOW_MEMORY_INFO_STACK]    = new option :: Bool (false, "mem-stack",    "show stack memory allocation info");
		memoryOptions_[SHOW_MEMORY_INFO_BOXED]    = new option :: Bool (false, "mem-boxed",    "show boxed memory allocation info");
		memoryOptions_[SHOW_MEMORY_INFO_STANDARD] = new option :: Bool (false, "mem-standard", "show standard heap memory allocation info");

		memoryOptions_[SHOW_MEMORY_INFO_BALANCE]  = new option :: Bool (false, "mem-balance",  "show memory balance info");
		memoryOptions_[SHOW_MEMORY_INFO_DISPOSED] = new option :: Bool (false, "mem-disposed", "show disposed memory info");
		memoryOptions_[SHOW_MEMORY_INFO_FRAGMENTATION] = new option :: Bool (false, "mem-fragmentation", "show memory fragmentation info");
	}
	inline void
	MemoryInfo :: release()
	{
		for (int i = 0; i < OPTION_NUM; ++ i) {
			delete memoryOptions_ [i];
			memoryOptions_ [i] = NULL;
		}
	}
	inline Size_t
	MemoryInfo :: getVolume()
	{
		Size_t volume = 0;
		for (int i = 0; i < OPTION_NUM; ++ i) {
			volume += Object :: getAggregateVolume (memoryOptions_ [i]);
		}
		return volume;
	}

	bool
	MemoryInfo :: proceedStringOption (const char* option, const int argCount, const char* argValues[], int& i)
	{
		for (int j = 0; j < OPTION_NUM; ++ j) {
			if (memoryOptions_[j]->proceedStringOption (option, argCount, argValues, i)) {
				return true;
			}
		}
		if (memoryOptions_[SHOW_MEMORY_INFO_ALL]->getValue()) {
			memoryOptions_[SHOW_MEMORY_INFO_USAGE]->value()    = true;
			memoryOptions_[SHOW_MEMORY_INFO_DETAILS]->value()  = true;
			memoryOptions_[SHOW_MEMORY_INFO_HEAP]->value()     = true;
			memoryOptions_[SHOW_MEMORY_INFO_STACK]->value()    = true;
			memoryOptions_[SHOW_MEMORY_INFO_BOXED]->value()    = true;
			memoryOptions_[SHOW_MEMORY_INFO_STANDARD]->value() = true;
			memoryOptions_[SHOW_MEMORY_INFO_BALANCE]->value()  = true;
			memoryOptions_[SHOW_MEMORY_INFO_DISPOSED]->value() = true;
		}
		return false;
	}

	inline bool
	MemoryInfo :: proceedOneCharOption (const char* option, const int argCount, const char* argValues[], int& i) {
		return false;
	}

	/************************************
	 *		Static private attributes
	 ************************************/

	option :: Bool* MemoryInfo :: memoryOptions_[OPTION_NUM];
	const char* MemoryInfo :: optionGroupName_ = "memory_info";
}
}

#endif /*NSTD_CONFIG_MEMORY_INFO_CPP_*/
