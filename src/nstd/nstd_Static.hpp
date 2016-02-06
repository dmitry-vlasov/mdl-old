/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_Static.hpp                                          */
/* Description:     pure static object base class                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include <ostream>

#include "nstd_String.hpp"

namespace nstd {

template<class T>
class Static {
public :
	static void init();
	static void init (const Size_t);
	static void release();

	static Size_t getVolume();
	template<class A>
	static void show (String<A>&);
	static void show (std :: ostream&);

	static bool isInitialized();
	static bool isCounted();
	static bool isShowed();

protected :
	template<class S>
	static Size_t getAggregateVolume (const S* const);
	template<class S>
	static void deleteAggregateObject (S*&);
	template<class S>
	static void deleteAggregateObject (S* const&);

private :
	/// This flag shows iff the current static object is already initialized.
	static bool initialized_;
	/// This flag shows iff the volume of the current static object is already counted.
	static bool counted_;
	/// This flag shows iff the current static object is already showed.
	static bool showed_;

	typedef String<> String_;

	static String_* string_;
};

}


