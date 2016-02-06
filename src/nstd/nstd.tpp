/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd.tpp                                                 */
/* Description:     basic nstd typedefs                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include <exception>
#include <ostream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <sstream>
#include <fstream>
#include <typeinfo>
#include <assert.h>

#include <pthread.h>

#include <time.h>
#include <stddef.h>
#include <stdint.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>

namespace nstd {

	typedef :: ptrdiff_t Ptrdiff_t;
	typedef :: size_t    Size_t;
	typedef :: time_t    Time_t;   // UNIX time, seconds
	typedef :: clock_t   Clock_t;  // microseconds ??..

	typedef std :: type_info Type_info;

	enum {
		MAX_THREAD_NUMBER = 16
	};
}

#include "nstd_chars.hpp"
#include "nstd_size.hpp"
#include "nstd_time.hpp"

namespace nstd {

	typedef :: uint8_t    Byte_t;
	typedef :: uint8_t    U_int8_t;
	typedef :: uint16_t   U_int16_t;
	typedef :: uint32_t   U_int32_t;
	typedef :: uint64_t   U_int64_t;

	typedef :: int8_t   Int8_t;
	typedef :: int16_t  Int16_t;
	typedef :: int32_t  Int32_t;
	typedef :: int64_t  Int64_t;

	typedef float Float;
	typedef double Double;

	typedef
		std :: ifstream
		InputFileStream;

	typedef
		std :: ofstream
		OutputFileStream;
}


