/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_map_String.cpp                                      */
/* Description:     string mapping                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MAP_STRING_CPP_
#define NSTD_MAP_STRING_CPP_

namespace nstd {
namespace map {

	/****************************
	 *		Public members
	 ****************************/

	template<class T, class A>
	template<template<class> class H1, class A1>
	inline typename String<T, A> :: Value_
	String<T, A> :: addFind
	(
		const container :: Vector<Key_, H1, A1>* const vector,
		const Value_ value
	) {
		return Ancestor_ :: addFind (vector, value);
	}
	template<class T, class A>
	template<template<class> class H1, class A1>
	inline typename String<T, A> :: Value_
	String<T, A> :: addFind
	(
		const container :: Vector<Key_, H1, A1>& vector,
		const Value_ value
	) {
		return Ancestor_ :: addFind (&vector, value);
	}
	template<class T, class A>
	inline typename String<T, A> :: Value_
	String<T, A> :: addFind
	(
		const char* const string,
		const Value_ value
	) {
		return Ancestor_ :: addFind (string, StringKey_ :: getStringLength (string), value);
	}

	template<class T, class A>
	inline typename String<T, A> :: Value_
	String<T, A> :: find (const char* const string) const {
		return Ancestor_ :: find (string, StringKey_ :: getStringLength (string));
	}
	template<class T, class A>
	template<class A1>
	inline typename String<T, A> :: Value_
	String<T, A> :: find (const nstd :: String<A1>* const vector) const {
		return Ancestor_ :: find (vector);
	}
	template<class T, class A>
	template<class A1>
	inline typename String<T, A> :: Value_
	String<T, A> :: find (const nstd :: String<A1>& vector) const {
		return Ancestor_ :: find (vector);
	}

	template<class T, class A>
	template<template<class> class H1, class A1>
	inline void
	String<T, A> :: setAdd
	(
		const container :: Vector<Key_, H1, A1>* const vector,
		const Value_ value
	) {
		return Ancestor_ :: setAdd (vector, value);
	}
	template<class T, class A>
	template<template<class> class H1, class A1>
	inline void
	String<T, A> :: setAdd
	(
		const container :: Vector<Key_, H1, A1>& vector,
		const Value_ value
	) {
		Ancestor_ :: setAdd (&vector, value);
	}
	template<class T, class A>
	inline void
	String<T, A> :: setAdd
	(
		const char* const string,
		const Value_ value
	) {
		Ancestor_ :: setAdd (string, StringKey_ :: getStringLength (string), value);
	}
}
}

#endif /*NSTD_MAP_STRING_CPP_*/
