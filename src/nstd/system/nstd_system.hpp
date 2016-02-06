/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_system.hpp                                          */
/* Description:     system interface module                                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {
namespace system {

	Size_t getFileSize (const char* const);
	bool directoryExists (const char* const);
	bool createDirectory (const char* const);
	Time_t getTime();
	Clock_t getClock();
	Clock_t getClocksPerSecond();
	Clock_t getClocksPerMinute();
	Clock_t getClocksPerHour();
}
}


