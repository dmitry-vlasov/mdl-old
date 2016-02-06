/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_map_Vector.hpp                                      */
/* Description:     vector mapping                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "map/nstd_map_Node.hpp"

namespace nstd {
namespace map {

template
<
	class V, ///< vector (key type)
	class T  ///< value type
>
class Vector :
	public memory :: storage :: Scalar
	<
		Vector<V, T>,
		typename V :: Allocator_
	> {
public :
	typedef V Vector_;
	typedef T Value_;
	typedef typename Vector_ :: Value_ Key_;
	typedef typename Vector_ :: Allocator_ Allocator_;
	typedef typename Vector_ :: Index_ Index_;

	Vector ();
	virtual ~ Vector();

	void clear();
	void erase();
	void init();

	template<template<class> class H1, class A1>
	Value_ addFind (const container :: Vector<Key_, H1, A1>* const, const Value_);
	Value_ addFind (const Key_* const, const Index_ size, const Value_);
	template<template<class> class H1, class A1>
	Value_ find (const container :: Vector<Key_, H1, A1>* const) const;
	template<template<class> class H1, class A1>
	Value_ find (const container :: Vector<Key_, H1, A1>&) const;
	Value_ find (const Key_* const vector, const Index_ size) const;
	template<template<class> class H1, class A1>
	void setAdd (const container :: Vector<Key_, H1, A1>* const, const Value_);
	void setAdd (const Key_* const, const Index_ size, const Value_);

	// nstd :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	template<class S>
	void show (S&) const;

private :
	typedef Node<Vector_, Value_> Node_;

	Node_* node_;
};

	template<class V, class T, class S>
	S&
	operator << (S&, const Vector<V, T>&);
}
}


