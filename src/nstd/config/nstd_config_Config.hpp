/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_config_Config.hpp                                   */
/* Description:     resulting config class                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONFIG_CONFIG_HPP_
#define NSTD_CONFIG_CONFIG_HPP_

#include "config/nstd_config_General.hpp"
#include "config/nstd_config_Paths.hpp"
#include "config/nstd_config_ProgramInfo.hpp"
#include "config/nstd_config_MemoryInfo.hpp"

namespace nstd {
namespace config {

template<class C>
class Config :
	public General,
	public Paths,
	public ProgramInfo,
	public MemoryInfo {
public :
	// Shows the usage message.
	template<class S>
	static void showUsageMessage (S&, const List& = List());
	template<class S>
	static void showOptionValues (S&, const List& = List());
	template<class S>
	static void showGroupNames (S&);

protected :
	typedef C Config_;

	static bool proceedOptions (const int, const char* []);
	static bool proceedFile (const char*);
	static int  countArguments (const int size, const char buffer[]);
	static void evalArguments (const int size, char buffer[], const char* argValues[]);
	static bool isWhitespace (const char);

	static void init();
	static void release();
	static Size_t getVolume();

	static bool proceedStringOption (const char*, const int, const char* [], int&);
	static bool proceedOneCharOption (const char*, const int, const char* [], int&);
};

}
}

#endif /*NSTD_CONFIG_CONFIG_HPP_*/
