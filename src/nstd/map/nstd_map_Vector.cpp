/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_map_Vector.cpp                                      */
/* Description:     vector mapping                                           */
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

	/****************************
	 *		Public members
	 ****************************/

	template<class V, class T>
	inline
	Vector<V, T> :: Vector () : node_ (NULL) {
	}
	template<class V, class T>
	Vector<V, T> :: ~ Vector ()
	{
		if (node_ == NULL) {
			return;
		}
		delete node_;
		node_ = NULL;
	}

	template<class V, class T>
	inline void
	Vector<V, T> :: clear()
	{
		if (node_ != NULL) {
			node_->clear();
		}
	}
	template<class V, class T>
	void
	Vector<V, T> :: erase()
	{
		if (node_ == NULL) {
			return;
		}
		delete node_;
		node_ = NULL;
	}
	template<class V, class T>
	inline void
	Vector<V, T> :: init() {
	}

	template<class V, class T>
	template<template<class> class H1, class A1>
	typename Vector<V, T> :: Value_
	Vector<V, T> :: addFind
	(
		const container :: Vector<Key_, H1, A1>* const vector,
		const Value_ value
	)
	{
		if (vector->isEmpty()) {
			return Undefined<Value_> :: getValue ();
		} else {
			if (node_ == NULL) {
				node_ = new Node_ (vector, value);
				return value;
			} else {
				return node_->addFind (vector, value);
			}
		}
	}
	template<class V, class T>
	typename Vector<V, T> :: Value_
	Vector<V, T> :: addFind
	(
		const Key_* const vector,
		const Index_ size,
		const Value_ value
	)
	{
		if ((vector == NULL) || (size == 0)) {
			return Undefined<Value_> :: getValue ();
		} else {
			if (node_ == NULL) {
				node_ = new Node_ (vector, size, value);
				return value;
			} else {
				return node_->addFind (vector, size, value);
			}
		}
	}
	template<class V, class T>
	template<template<class> class H1, class A1>
	typename Vector<V, T> :: Value_
	Vector<V, T> :: find
	(
		const container :: Vector<Key_, H1, A1>* const vector
	) const
	{
		if (vector->isEmpty() || (node_ == NULL)) {
			return Undefined<Value_> :: getValue ();
		} else {
			return node_->find (vector);
		}
	}
	template<class V, class T>
	template<template<class> class H1, class A1>
	inline typename Vector<V, T> :: Value_
	Vector<V, T> :: find
	(
		const container :: Vector<Key_, H1, A1>& vector
	) const {
		return find (&vector);
	}
	template<class V, class T>
	typename Vector<V, T> :: Value_
	Vector<V, T> :: find (const Key_* const vector, const Index_ size) const
	{
		if ((size == 0) || (node_ == NULL)) {
			return Undefined<Value_> :: getValue ();
		} else {
			return node_->find (vector, size);
		}
	}
	template<class V, class T>
	template<template<class> class H1, class A1>
	void
	Vector<V, T> :: setAdd
	(
		const container :: Vector<Key_, H1, A1>* const vector,
		const Value_ value
	)
	{
		if (!vector->isEmpty()) {
			if (node_ == NULL) {
				node_ = new Node_ (vector, value);
			} else {
				node_->setAdd (vector, value);
			}
		}
	}
	template<class V, class T>
	void
	Vector<V, T> :: setAdd
	(
		const Key_* const vector,
		const Index_ size,
		const Value_ value
	)
	{
		if ((vector != NULL) && (size != 0)) {
			if (node_ == NULL) {
				node_ = new Node_ (vector, size, value);
			} else {
				node_->setAdd (vector, size, value);
			}
		}
	}

	// nstd :: Object implementation
	template<class V, class T>
	inline void
	Vector<V, T> :: commitSuicide() {
		delete this;
	}
	template<class V, class T>
	Size_t
	Vector<V, T> :: getVolume() const
	{
		if (node_ == NULL) {
			return 0;
		}
		Size_t volume = 0;
		volume += node_->getVolume();
		volume += node_->getSizeOf();
		return volume;
	}
	template<class V, class T>
	inline Size_t
	Vector<V, T> :: getSizeOf() const {
		return sizeof (Vector);
	}
	template<class V, class T>
	template<class S>
	inline void
	Vector<V, T> :: show (S& n) const
	{
		if (node_ == NULL) {
			return;
		}
		node_->show (n);
	}

	/********************************
	 *		Overloaded operators
	 ********************************/

	template<class V, class T, class S>
	inline S&
	operator << (S& s, const Vector<V, T>& map)
	{
		map.show (s);
		return s;
	}
}
}



