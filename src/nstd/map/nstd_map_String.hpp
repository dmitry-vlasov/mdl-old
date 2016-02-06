/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_map_String.hpp                                      */
/* Description:     string mapping                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "nstd_String.hpp"
#include "map/nstd_map_Vector.hpp"

namespace nstd {
namespace map {

template
<
	class T, ///< value type
	class A  ///< allocator
>
class String : public Vector<nstd :: String<A>, T> {
public :
	typedef typename nstd :: String<A> StringKey_;
private :
	typedef Vector<StringKey_, T> Ancestor_;
public :
	typedef typename Ancestor_ :: Value_ Value_;
	typedef typename Ancestor_ :: Key_ Key_;
	typedef typename Ancestor_ :: Allocator_ Allocator_;
	typedef typename Ancestor_ :: Index_ Index_;

	template<template<class> class H1, class A1>
	Value_ addFind (const container :: Vector<Key_, H1, A1>* const, const Value_);
	template<template<class> class H1, class A1>
	Value_ addFind (const container :: Vector<Key_, H1, A1>&, const Value_);
	Value_ addFind (const char* const, const Value_);

	Value_ find (const char* const) const;
	template<class A1>
	Value_ find (const nstd :: String<A1>* const) const;
	template<class A1>
	Value_ find (const nstd :: String<A1>&) const;

	template<template<class> class H1, class A1>
	void setAdd (const container :: Vector<Key_, H1, A1>* const, const Value_);
	template<template<class> class H1, class A1>
	void setAdd (const container :: Vector<Key_, H1, A1>&, const Value_);
	void setAdd (const char* const, const Value_);
};

}
}


