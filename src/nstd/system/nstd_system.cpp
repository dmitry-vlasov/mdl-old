/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_system.cpp                                          */
/* Description:     system interface module                                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#ifdef __WIN32__
//#include <windows.h>
#endif

namespace nstd {
namespace system {
	
	Size_t 
	getFileSize (const char* const fileName)
	{
		Size_t length = 0;
		InputFileStream file;
		file.open (fileName, std :: ios :: binary);

		// get length of file:
		file.seekg (0, std :: ios :: end);
		length = file.tellg();
		file.close();

		return length;
	}
	inline bool
	directoryExists (const char* const path)
	{
#ifdef __linux__
		struct stat statBuffer;
		return (stat (path, &statBuffer) == 0 && S_ISDIR(statBuffer.st_mode));
#endif
#ifdef __WIN32__
		//return :: CreateDirectory (directory, NULL);
#endif
	}
	inline bool
	createDirectory (const char* const directory)
	{
#ifdef __linux__
		return (mkdir (directory, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0);
#endif
#ifdef __WIN32__
		//return :: CreateDirectory (directory, NULL);
#endif
	}
	inline Time_t
	getTime() {
		return :: time (NULL);
	}
	inline Clock_t
	getClock()
	{
		struct timeval time;
		:: gettimeofday (&time, NULL);
		return time.tv_usec;
	}
	/*
	inline Clock_t
	getClock() {
		return :: clock();
	}
	 */
	inline Clock_t
	getClocksPerSecond()
	{
		return 1000000;
		//return CLOCKS_PER_SEC;
	}
	inline Clock_t
	getClocksPerMinute() {
		return getClocksPerSecond() * 60;
	}
	inline Clock_t
	getClocksPerHour() {
		return getClocksPerMinute() * 60;
	}
}
}


