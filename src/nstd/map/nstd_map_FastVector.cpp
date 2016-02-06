/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_map_FastVector.cpp                                  */
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

	/****************************
	 *		Public members
	 ****************************/

	template<class V, class T, class S>
	inline
	FastVector<V, T, S> :: FastVector () :
	list_ (new Node_()) {
	}
	template<class V, class T, class S>
	FastVector<V, T, S> :: ~ FastVector ()
	{
		if (list_ == NULL) {
			return;
		}
		delete list_;
		list_ = NULL;
	}

	template<class V, class T, class S>
	template<template<class> class H1, class A1>
	inline typename FastVector<V, T, S> :: Value_
	FastVector<V, T, S> :: addFind
	(
		const container :: Vector<Key_, H1, A1>* const vector,
		const Value_ value
	)
	{
		if (vector->isEmpty()) {
			return Undefined<Value_> :: getValue ();
		} else {
			return addFind (vector, 0, vector->getSize(), value);
		}
	}
	template<class V, class T, class S>
	template<template<class> class H1, class A1>
	inline typename FastVector<V, T, S> :: Value_
	FastVector<V, T, S> :: find
	(
		const container :: Vector<Key_, H1, A1>* const vector
	) const
	{
		if (vector->isEmpty()) {
			return Undefined<Value_> :: getValue ();
		} else {
			return find (vector, 0, vector->getSize());
		}
	}
	template<class V, class T, class S>
	template<template<class> class H1, class A1>
	inline typename FastVector<V, T, S> :: Value_
	FastVector<V, T, S> :: find
	(
		const container :: Vector<Key_, H1, A1>& vector
	) const {
		return find (&vector, 0, vector.getSize());
	}
	template<class V, class T, class S>
	inline typename FastVector<V, T, S> :: Value_
	FastVector<V, T, S> :: find (const Key_* const vector, const Index_ size) const
	{
		if (size == 0) {
			return Undefined<Value_> :: getValue ();
		} else {
			return find (vector, 0, size);
		}
	}

	// nstd :: Object implementation
	template<class V, class T, class S>
	inline void
	FastVector<V, T, S> :: commitSuicide() {
		delete this;
	}
	template<class V, class T, class S>
	Size_t
	FastVector<V, T, S> :: getVolume() const
	{
		Size_t result = 0;
		result += getSizeOf();
		Node_* node = list_;
		while (node != NULL) {
			result += node->getVolume();
			node = node->next_;
		}
		return result;
	}
	template<class V, class T, class S>
	inline Size_t
	FastVector<V, T, S> :: getSizeOf() const {
		return sizeof (FastVector);
	}
	template<class V, class T, class S>
	template<class N>
	inline void
	FastVector<V, T, S> :: show (N& n) const {
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class V, class T, class S>
	template<template<class> class H1, class A1>
	typename FastVector<V, T, S> :: Value_
	FastVector<V, T, S> :: addFind
	(
		const container :: Vector<Key_, H1, A1>* const vector,
		Index_ position,
		const Index_ length,
		const Value_ value
	)
	{
		const Key_ x = vector->getValue (position);
		Node_* node = list_;

		while (true) {
			if (node->key_ == x) {
				if (length == position + 1) {
					if (node->value_ == Undefined<Value_> :: getValue ()) {
						node->value_ = value;
						return value;
					} else {
						return node->value_;
					}
				} else {
					if (node->child_ == NULL) {
						node->child_ = new FastVector();
						return node->child_->addFind (vector, ++position, length, value);
					} else {
						return node->child_->addFind (vector, ++position, length, value);
					}
				}
			}
			if (node->next_ == NULL) {
				break;
			} else {
				node = node->next_;
			}
		}
		return add
			(
				vector,
				position,
				length,
				value,
				x,
				node->next_
			);
	}

	template <class V, class T, class S>
	template<template<class> class H1, class A1>
	typename FastVector<V, T, S> :: Value_
	FastVector<V, T, S> :: add
	(
		const container :: Vector<Key_, H1, A1>* const vector,
		Index_ position,
		const Index_ length,
		const Value_ value,
		const Key_ x,
		Node_*& newNode
	)
	{
		newNode = new Node_();

		newNode->key_ = x;
		if (length == position + 1) {
			newNode->value_ = value;
		} else {
			FastVector* const child = new FastVector();
			child->addFind (vector, ++position, length, value);
			newNode->child_ = child;
		}
		return value;
	}


	template<class V, class T, class S>
	template<template<class> class H1, class A1>
	typename FastVector<V, T, S> :: Value_
	FastVector<V, T, S> :: find
	(
		const container :: Vector<Key_, H1, A1>* const vector,
		Index_ position,
		const Index_ length
	) const
	{
		const Key_ x = vector->getValue (position);

		Node_* first = list_;

		if (first->key_ == x) {
			first->rate_ ++;
			if (length == position + 1) {
				return first->value_;
			} else {
				if (first->child_ == NULL) {
					return Undefined<Value_> :: getValue ();
				} else {
					return first->child_->find (vector, ++position, length);
				}
			}
		}

		Node_* second = first;
		first = first->next_;

		if (first == NULL) {
			return Undefined<Value_> :: getValue ();
		}

		if (first->key_ == x) {
			first->rate_ ++;
			if (first->rate_ > second->rate_) {
				second->next_ = first->next_;
				first->next_ = second;
				list_ = first;
			}
			if (length == position + 1) {
				return first->value_;
			} else {
				if (first->child_ == NULL) {
					return Undefined<Value_> :: getValue ();
				} else {
					return first->child_->find (vector, ++position, length);
				}
			}
		}

		Node_* third = second;
		second = first;
		first = first->next_;

		if (first == NULL) {
			return Undefined<Value_> :: getValue ();
		}

		while (first != NULL) {
			if (first->key_ == x) {
				first->rate_ ++;
				if (first->rate_ > second->rate_) {
					second->next_ = first->next_;
					first->next_ = second;
					third->next_ = first;
				}
				if (length == position + 1) {
					return first->value_;
				} else {
					if (first->child_ == NULL) {
						return Undefined<Value_>:: getValue ();
					} else {
						return first->child_->find (vector, ++position, length);
					}
				}
			}
			third = second;
			second = first;
			first = first->next_;
		}
		return Undefined<Value_> :: getValue ();
	}

	template <class V, class T, class S>
	typename FastVector<V, T, S> :: Value_
	FastVector<V, T, S> :: find
	(
		const Key_* const vector,
		Index_ position,
		const Index_ length
	) const
	{
		const Node_* node = list_;
		while (node != NULL) {
			if (node->key_ == vector [position]) {
				if (length == position + 1) {
					return node->value_;
				} else {
					if (node->child_ == NULL) {
						return Undefined<Value_> :: getValue();
					} else {
						return node->child_->find (vector, ++position, length);
					}
				}
			}
			node = node->next_;
		}
		return Undefined<Value_> :: getValue();
	}

	/*********************************************************
	 *		FastVector<V, T, S> :: Node_ public members
	 *********************************************************/

	template<class V, class T, class S>
	inline
	FastVector<V, T, S> :: Node_ :: Node_ () :
	key_ (Undefined<Key_> :: getValue()),
	value_ (Undefined<Value_> :: getValue()),
	child_ (NULL),
	next_ (NULL),
	rate_ (0) {
	}
	template<class V, class T, class S>
	FastVector<V, T, S> :: Node_ :: ~ Node_ ()
	{
		if (child_ != NULL) {
			delete child_;
			child_ = NULL;
		}
		if (next_ != NULL) {
			delete next_;
			next_ = NULL;
		}
	}

	template<class V, class T, class S>
	Size_t
	FastVector<V, T, S> :: Node_ :: getVolume() const
	{
		Size_t result = 0;
		result += getSizeOf();
		if (child_ != NULL) {
			result += child_->getVolume();
		}
		return result;
	}
	template<class V, class T, class S>
	inline Size_t
	FastVector<V, T, S> :: Node_ :: getSizeOf() const {
		return sizeof (Node_);
	}

	/********************************
	 *		Overloaded operators
	 ********************************/

	template<class V, class T, class S, class N>
	inline N&
	operator << (N& n, const FastVector<V, T, S>& map)
	{
		map.show (n);
		return n;
	}
}
}



