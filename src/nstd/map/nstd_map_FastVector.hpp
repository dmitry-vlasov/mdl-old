/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_map_FastVector.hpp                                  */
/* Description:     fast vector mapping                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {
namespace map {

template
<
	class V,            ///< vector (key type)
	class T,            ///< value type
	class S = U_int32_t ///< rate type
>
class FastVector :
	public memory :: storage :: Scalar
	<
		FastVector<V, T, S>,
		typename V :: Allocator_
	> {
public :
	typedef T Value_;
	typedef S Rate_;
	typedef typename V :: Value_ Key_;
	typedef typename V :: Allocator_ Allocator_;
	typedef typename V :: Index_ Index_;
	template<class T_1>
	class StoragePolicy : public V :: template StoragePolicy<T_1> {
	};

	FastVector();
	virtual ~ FastVector();

	template<template<class> class H1, class A1>
	Value_ addFind (const container :: Vector<Key_, H1, A1>* const, const Value_);
	template<template<class> class H1, class A1>
	Value_ find (const container :: Vector<Key_, H1, A1>* const) const;
	template<template<class> class H1, class A1>
	Value_ find (const container :: Vector<Key_, H1, A1>&) const;
	Value_ find (const Key_* const vector, const Index_ size) const;

	// nstd :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	template<class N>
	void show (N&) const;

private :
	template<template<class> class H1, class A1>
	Value_ addFind
	(
		const container :: Vector<Key_, H1, A1>* const vector,
		Index_ position,
		const Index_ length,
		const Value_ value
	);

	template<template<class> class H1, class A1>
	Value_ find
	(
		const container :: Vector<Key_, H1, A1>* const vector,
		Index_ position,
		const Index_ length
	) const;

	Value_ find
	(
		const Key_* const vector,
		Index_ position,
		const Index_ size
	) const;

	class Node_ : public memory :: storage :: Scalar<Node_, Allocator_> {
	public :
		Node_ ();
		virtual ~ Node_();

		Size_t getVolume() const;
		Size_t getSizeOf() const;

		Key_ key_;
		Value_ value_;
		FastVector* child_;
		mutable Node_* next_;
		mutable Rate_ rate_;
	};

	template<template<class> class H1, class A1>
	Value_ add
	(
		const container :: Vector<Key_, H1, A1>* const vector,
		Index_ position,
		const Index_ length,
		const Value_ value,
		const Key_ x,
		Node_*& newNode
	);

	mutable Node_* list_;
};

	template<class V, class T, class S, class N>
	N&
	operator << (N&, const FastVector<V, T, S>&);
}
}


