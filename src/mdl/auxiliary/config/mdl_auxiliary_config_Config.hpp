/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_config_Config.hpp                          */
/* Description:     static class for command line arguments                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_CONFIG_CONFIG_HPP_
#define MDL_AUXILIARY_CONFIG_CONFIG_HPP_

#include "mdl/types/mdl_types.hpp"

#include "mdl/auxiliary/config/mdl_auxiliary_config_Concurrency.hpp"
#include "mdl/auxiliary/config/mdl_auxiliary_config_Info.hpp"
#include "mdl/auxiliary/config/mdl_auxiliary_config_Integer.hpp"
#include "mdl/auxiliary/config/mdl_auxiliary_config_Location.hpp"
#include "mdl/auxiliary/config/mdl_auxiliary_config_Memory.hpp"
#include "mdl/auxiliary/config/mdl_auxiliary_config_Mining.hpp"
#include "mdl/auxiliary/config/mdl_auxiliary_config_Misc.hpp"
#include "mdl/auxiliary/config/mdl_auxiliary_config_Mode.hpp"
#include "mdl/auxiliary/config/mdl_auxiliary_config_Paths.hpp"
#include "mdl/auxiliary/config/mdl_auxiliary_config_Real.hpp"
#include "mdl/auxiliary/config/mdl_auxiliary_config_Refactor.hpp"
#include "mdl/auxiliary/config/mdl_auxiliary_config_Search.hpp"
#include "mdl/auxiliary/config/mdl_auxiliary_config_Server.hpp"
#include "mdl/auxiliary/config/mdl_auxiliary_config_String.hpp"
#include "mdl/auxiliary/config/mdl_auxiliary_config_Timing.hpp"

namespace mdl {
namespace auxiliary {
namespace config {

// Class which contain boolean flags and string parameters for mdl.
class Config :
	public nstd :: Config<Config>,
	public Concurrency,
	public Info,
	public Integer,
	public Location,
	public Memory,
	public Mining,
	public Misc,
	public Mode,
	public Paths,
	public Real,
	public Refactor,
	public Search,
	public Server,
	public String,
	public Timing {
	typedef nstd :: Config<Config> Ancestor_;
public :
	typedef int Percent_;

	static RunMode getRunMode();
	static void setRunMode (const RunMode);

	static bool useProver();
	static bool useLearning();
	static bool useWriting();

	// volume for stack memory space
	static Size_t getStackVolume();
	// volume of memory needed by prover
	static Size_t getProverVolume();
	// volume of reserve memory needed by prover
	static Size_t getReserveVolume();
	// Russell files extension
	static const char* russellExtension();

	static bool proceed (const int, const char* []);
	static bool proceedStringOption (const char*, const int, const char* [], int&);
	static bool proceedOneCharOption (const char*, const int, const char* [], int&);
	static bool analyseArguments();

	template<class S>
	static void showUsageMessage (S&, const List& groupList = List());
	template<class S>
	static void showOptionValues (S&, const List& groupList = List());
	template<class S>
	static void showGroupNames (S&);
	static void showUsageMessage();

	static void show();
	static void init();
	static void release();
	static Size_t getVolume();

protected :

	static bool initRunMode();
	static bool isConsistent();
	static bool checkPaths();

	static bool checkCorrectness();
	static bool checkConsistency();

	// general mode option
	static RunMode runMode_;
};

}
}
}

#include "mdl/auxiliary/config/mdl_auxiliary_config_Config.ipp"

#endif /*MDL_AUXILIARY_CONFIG_CONFIG_HPP_*/
