/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_Memory.cpp                          */
/* Description:     static class for mdl memory options                      */
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

	inline Size_t
	Memory :: getStackVolume() {
		return volumeOptions_ [STACK_VOLUME]->getSize();
	}
	inline Size_t
	Memory :: getProverVolume() {
		return volumeOptions_ [PROVER_VOLUME]->getSize();
	}
	inline Size_t
	Memory :: getReserveVolume() {
		return volumeOptions_ [RESERVE_VOLUME]->getSize();
	}

	inline bool
	Memory :: proveInHeap() {
		return memoryOptions_ [PROVE_IN_HEAP]->getValue();
	}
	inline bool
	Memory :: proveInBoxed() {
		return memoryOptions_ [PROVE_IN_BOXED]->getValue();
	}
	inline bool
	Memory :: fastBoxedMemory() {
		return memoryOptions_ [FAST_BOXED_MEMORY]->getValue();
	}
	inline bool
	Memory :: clearBoxedMemory() {
		return memoryOptions_ [CLEAR_BOXED_MEMORY]->getValue();
	}
	inline bool
	Memory :: deleteBoxedTree() {
		return memoryOptions_ [DELETE_BOXED_TREE]->getValue();
	}

	template<class S>
	void
	Memory :: showUsageMessage (S& os, const List& groupList)
	{
		if (groupList.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int i = 0; i < VOLUME_OPTIONS_NUM; ++ i) {
				volumeOptions_ [i]->showUsageMessage (os);
			}
			for (int i = 0; i < MEMORY_OPTIONS_NUM; ++ i) {
				memoryOptions_ [i]->showUsageMessage (os);
			}
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	void
	Memory :: showOptionValues (S& os, const List& groupList)
	{
		if (groupList.contains (optionGroupName_)) {
			os << optionGroupName_ << ':' << chars :: NEW_LINE;
			for (int i = 0; i < VOLUME_OPTIONS_NUM; ++ i) {
				volumeOptions_ [i]->showOptionValues (os);
			}
			for (int i = 0; i < MEMORY_OPTIONS_NUM; ++ i) {
				memoryOptions_ [i]->showOptionValues (os);
			}
			os << chars :: NEW_LINE;
		}
	}
	template<class S>
	inline void
	Memory :: showGroupName (S& os) {
		os << "\t" << optionGroupName_ << chars :: NEW_LINE;
	}

	/****************************
	 *		Protected members
	 ****************************/

	bool
	Memory :: proceedStringOption (const char* opt, const int argCount, const char* argValues[], int& i)
	{
		for (int j = 0; j < VOLUME_OPTIONS_NUM; ++ j) {
			if (volumeOptions_[j]->proceedStringOption (opt, argCount, argValues, i)) {
				return true;
			}
		}
		for (int j = 0; j < MEMORY_OPTIONS_NUM; ++ j) {
			if (memoryOptions_[j]->proceedStringOption (opt, argCount, argValues, i)) {
				return true;
			}
		}
		return false;
	}
	bool
	Memory :: proceedOneCharOption (const char* opt, const int argCount, const char* argValues[], int& i) {
		return false;
	}

	bool
	Memory :: isCorrect()
	{
		for (int i = 0; i < VOLUME_OPTIONS_NUM; ++ i) {
			if (!volumeOptions_ [i]->isCorrect()) {
				return false;
			}
		}
		for (int i = 0; i < MEMORY_OPTIONS_NUM; ++ i) {
			if (!memoryOptions_ [i]->isCorrect()) {
				return false;
			}
		}
		return true;
	}

	void
	Memory :: init ()
	{
		volumeOptions_[STACK_VOLUME]   = new option :: Size (DEFAULT_STACK_VOLUME,   "stack-volume",   "use <size> volume for stack (megabytes).");
		volumeOptions_[PROVER_VOLUME]  = new option :: Size (DEFAULT_PROVER_VOLUME,  "prover-volume",  "use <size> volume for proving (megabytes).");
		volumeOptions_[RESERVE_VOLUME] = new option :: Size (DEFAULT_RESERVE_VOLUME, "reserve-volume", "use <size> volume for reserve (megabytes).");

		memoryOptions_[PROVE_IN_HEAP]      = new option :: Bool (false, "prove-in-heap",      "use heap memory space for proving.");
		memoryOptions_[PROVE_IN_BOXED]     = new option :: Bool (true,  "prove-in-boxed",     "use boxed memory space for proving.");
		memoryOptions_[FAST_BOXED_MEMORY]  = new option :: Bool (false, "fast-boxed-memory",  "do not track disposed boxed memory.");
		memoryOptions_[CLEAR_BOXED_MEMORY] = new option :: Bool (false, "clear-boxed-memory", "clear boxed memory at initialization / finalization.");
		memoryOptions_[DELETE_BOXED_TREE]  = new option :: Bool (false, "delete-boxed-tree",  "delete prover tree in boxed memory at finalization.");
	}
	void
	Memory :: release()
	{
		for (int i = 0; i < VOLUME_OPTIONS_NUM; ++ i) {
			delete volumeOptions_ [i];
			volumeOptions_ [i] = NULL;
		}
		for (int i = 0; i < MEMORY_OPTIONS_NUM; ++ i) {
			delete memoryOptions_ [i];
			memoryOptions_ [i] = NULL;
		}
	}
	Size_t
	Memory :: getVolume()
	{
		Size_t volume = 0;
		for (int i = 0; i < VOLUME_OPTIONS_NUM; ++ i) {
			volume += object :: Object :: getAggregateVolume (volumeOptions_ [i]);
		}
		for (int i = 0; i < MEMORY_OPTIONS_NUM; ++ i) {
			volume += object :: Object :: getAggregateVolume (memoryOptions_ [i]);
		}
		return volume;
	}
	bool
	Memory :: initMemorySize (const bool lookup, bool& exit, bool& error)
	{
		if (lookup) {
			volumeOptions_ [STACK_VOLUME]->setSize (size :: MEGABYTE);
		}
		if (volumeOptions_ [STACK_VOLUME]->getSize() < size :: MEGABYTE) {
			std :: cout << "stack size is too small." << std :: endl;
			exit = true;
			error = true;
			return false;
		}
		if (volumeOptions_ [PROVER_VOLUME]->getSize() < size :: MEGABYTE * 32) {
			std :: cout << "prover memory space size is too small." << std :: endl;
			exit = true;
			error = true;
			return false;
		}
		if (volumeOptions_ [RESERVE_VOLUME]->getSize() * 2 > volumeOptions_ [PROVER_VOLUME]->getSize()) {
			std :: cout << "too large reserve in comparence with main memory volume." << std :: endl;
			exit = true;
			error = true;
			return false;
		}
		return true;
	}

	/*************************************
	 *		Private static attributes
	 *************************************/

	option :: Size* Memory :: volumeOptions_ [VOLUME_OPTIONS_NUM];
	option :: Bool* Memory :: memoryOptions_ [MEMORY_OPTIONS_NUM];
	const char* Memory :: optionGroupName_ = "memory";
}
}
}


