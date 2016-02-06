/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_debug.hpp                                    */
/* Description:     declarations for memory managers module                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

/*****************************************************************************/
/*       Memory debugging flags                                              */
/*                                                                           */
/* DEBUG_ALL_MEMORY_LEAKS:       map and bind with types all memory          */
/* DEBUG_HEAP_MEMORY_LEAKS:      map and bind with types heap memory         */
/* DEBUG_BOXED_MEMORY_LEAKS:     map and bind with types boxed memory        */
/* DEBUG_SOME_MEMORY_LEAKS:      map and bind with types some memory         */
/* DEBUG_DISPOSED                debugging of disposed memory manager        */
/*                                                                           */
/* DEBUG_HEAP_CONTROL_ALLOCATION check allocation of a proper memory chunk   */
/* DEBUG_BOXED_CONTROL_ALLOCATION check allocation of a proper memory chunk  */
/*                                                                           */
/* DEBUG_HEAP_MAP                use detailed memory map for heap memory     */
/* DEBUG_BOXED_MAP               use detailed memory map for boxed memory    */
/* DEBUG_STANDARD_MAP            use detailed memory map for standard memory */
/*****************************************************************************/


#ifdef DEBUG_DISPOSED
#endif

#ifdef DEBUG_ALL_MEMORY_LEAKS
	#define DEBUG_HEAP_MEMORY_LEAKS
	#define DEBUG_BOXED_MEMORY_LEAKS
	#define DEBUG_STANDARD_MEMORY_LEAKS
#endif

#ifdef DEBUG_HEAP_MEMORY_LEAKS
	#define DEBUG_HEAP_MAP
#endif

#ifdef DEBUG_BOXED_MEMORY_LEAKS
    #define DEBUG_BOXED_MAP
#endif

#ifdef DEBUG_STANDARD_MEMORY_LEAKS
    #define DEBUG_STANDARD_MAP
#endif

// initialization of DEBUG_SOME_MEMORY_LEAKS
#ifdef DEBUG_HEAP_MEMORY_LEAKS
	#define DEBUG_SOME_MEMORY_LEAKS
#elif defined(DEBUG_BOXED_MEMORY_LEAKS)
	#define DEBUG_SOME_MEMORY_LEAKS
#elif defined(DEBUG_STANDARD_MEMORY_LEAKS)
	#define DEBUG_SOME_MEMORY_LEAKS
#endif

//#define DEBUG_HEAP_ALLOCATION
//#define DEBUG_HEAP_CONTROL_ALLOCATION

#ifdef DEBUG_HEAP_ALLOCATION
	#define DEBUG_HEAP_MAP
#endif

#ifdef DEBUG_BOXED_ALLOCATION
	#define DEBUG_BOXED_MAP
#endif

// initialization of DEBUG_SOME_MAP
#ifdef DEBUG_HEAP_MAP
	#define DEBUG_SOME_MAP
#elif defined(DEBUG_BOXED_MAP)
	#define DEBUG_SOME_MAP
#elif defined(DEBUG_STANDARD_MAP)
	#define DEBUG_SOME_MAP
#endif

#ifdef DEBUG_SOME_MEMORY_LEAKS
	#define MAP_IS_INITIALLY_ON
#endif


