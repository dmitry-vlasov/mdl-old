/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_Memory.hpp                          */
/* Description:     static class for mdl memory options                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_CONFIG_MEMORY_HPP_
#define MDL_AUXILIARY_CONFIG_MEMORY_HPP_

#include "mdl/types/mdl_types.hpp"
#include "mdl/auxiliary/config/mdl_auxiliary_config.dpp"

namespace mdl {
namespace auxiliary {
namespace config {

class Memory {
public :
	enum VolumeOption_ {
		STACK_VOLUME       = 0,
		PROVER_VOLUME      = 1,
		RESERVE_VOLUME     = 2,
		VOLUME_OPTIONS_NUM = 3
	};

	// volume for stack memory space
	static Size_t getStackVolume();
	// volume of memory needed by prover
	static Size_t getProverVolume();
	// volume of reserve memory needed by prover
	static Size_t getReserveVolume();

	enum MemoryOption_ {
		PROVE_IN_HEAP      = 0,
		PROVE_IN_BOXED     = 1,
		FAST_BOXED_MEMORY  = 2,
		CLEAR_BOXED_MEMORY = 3,
		DELETE_BOXED_TREE  = 4,
		MEMORY_OPTIONS_NUM = 5
	};

	// use heap memory space for proving
	static bool proveInHeap();
	// use boxed memory space for proving
	static bool proveInBoxed();
	// fast boxed memory: do not track disposed
	static bool fastBoxedMemory();
	// clear boxed memory at initialization / finalization
	static bool clearBoxedMemory();
	// delete prover tree in boxed memory
	static bool deleteBoxedTree();

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
	static bool initMemorySize (const bool lookup, bool& exit, bool& error);

private :
	enum {
		DEFAULT_STACK_VOLUME   = 16  * size :: MEGABYTE,
		DEFAULT_PROVER_VOLUME  = 256 * size :: MEGABYTE,
		DEFAULT_RESERVE_VOLUME = 4   * size :: MEGABYTE,
		DEFAULT_MEMORY_USAGE_PERCENT = 30,   // %
	};
	static option :: Size* volumeOptions_ [VOLUME_OPTIONS_NUM];
	static option :: Bool* memoryOptions_ [MEMORY_OPTIONS_NUM];
	static const char* optionGroupName_;
};

}
}
}

#endif /*MDL_AUXILIARY_CONFIG_MEMORY_HPP_*/
