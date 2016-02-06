/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_map_Node.hpp                                        */
/* Description:     vector mapping node                                      */
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
	class V, ///< vector (key type)
	class T  ///< value type
>
class Node :
	public memory :: storage :: Scalar
	<
		Node<V, T>,
		typename V :: Allocator_
	> {
public :
	typedef V Vector_;
	typedef T Value_;
	typedef typename Vector_ :: Value_ Key_;
	typedef typename Vector_ :: Allocator_ Allocator_;
	typedef typename Vector_ :: Index_ Index_;

	template<template<class> class H1, class A1>
	Node
	(
		const container :: Vector<Key_, H1, A1>* const vector,
		const Value_ value,
		Index_ position = 0,
		const Node* parent = NULL
	);
	Node
	(
		const Key_* const vector,
		const Index_ size,
		const Value_ value,
		Index_ position = 0,
		const Node* parent = NULL
	);
	~ Node();

	template<template<class> class H1, class A1>
	Value_ addFind
	(
		const container :: Vector<Key_, H1, A1>* const vector,
		const Value_ value
	);
	Value_ addFind
	(
		const Key_* const vector,
		const Index_ size,
		const Value_ value
	);
	template<template<class> class H1, class A1>
	Value_ find (const container :: Vector<Key_, H1, A1>* const vector) const;
	Value_ find (const Key_* const vector, const Index_ size) const;
	template<template<class> class H1, class A1>
	void setAdd
	(
		const container :: Vector<Key_, H1, A1>* const vector,
		const Value_ value
	);
	void setAdd
	(
		const Key_* const vector,
		const Index_ size,
		const Value_ value
	);

	bool isDefined() const;
	void clear();

	// nstd :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	template<class N>
	void show (N&) const;

private :
	template<template<class> class H1, class A1>
	Node* addFindNode
	(
		const container :: Vector<Key_, H1, A1>* const vector,
		Index_ position = 0
	);
	Node* addFindNode
	(
		const Key_* const vector,
		const Index_ size,
		Index_ position = 0
	);

	template<template<class> class H1, class A1>
	const Node* findNode
	(
		const container :: Vector<Key_, H1, A1>* const vector,
		Index_ position = 0
	) const;
	const Node* findNode
	(
		const Key_* const vector,
		const Index_ size,
		Index_ position = 0
	) const;

	template<class N>
	void showBack (N&) const;

	const Key_ key_;
	const Node* parent_;
	Value_ value_;
	Node* child_;
	Node* next_;
};

	template<class V, class T, class S>
	S&
	operator << (S&, const Node<V, T>&);
}
}


