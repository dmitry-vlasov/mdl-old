/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_map_Node.cpp                                        */
/* Description:     vector mapping node                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MAP_NODE_CPP_
#define NSTD_MAP_NODE_CPP_

namespace nstd {
namespace map {

	/****************************
	 *		Public members
	 ****************************/

	template<class V, class T>
	template<template<class> class H1, class A1>
	Node<V, T> :: Node
	(
		const container :: Vector<Key_, H1, A1>* const vector,
		const Value_ value,
		Index_ position,
		const Node* parent
	) :
	key_ (vector->getValue (position)),
	parent_ (parent),
	value_
	(
		vector->getSize() == position + 1 ?
		value :
		Undefined<Value_> :: getValue()
	),
	child_
	(
		vector->getSize() == position + 1 ?
		NULL :
		new Node (vector, value, ++ position, this)
	),
	next_ (NULL) {
	}
	template<class V, class T>
	Node<V, T> :: Node
	(
		const Key_* const vector,
		const Index_ size,
		const Value_ value,
		Index_ position,
		const Node* parent
	) :
	key_ (vector [position]),
	parent_ (parent),
	value_
	(
		size == position + 1 ?
		value :
		Undefined<Value_> :: getValue()
	),
	child_
	(
		size == position + 1 ?
		NULL :
		new Node (vector, size, value, ++ position, this)
	),
	next_ (NULL) {
	}
	template<class V, class T>
	Node<V, T> :: ~ Node()
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

	template<class V, class T>
	template<template<class> class H1, class A1>
	inline typename Node<V, T> :: Value_
	Node<V, T> :: addFind
	(
		const container :: Vector<Key_, H1, A1>* const vector,
		const Value_ value
	)
	{
		Node* node = addFindNode (vector);
		if (!node->isDefined()) {
			node->value_ = value;
		}
		return node->value_;
	}
	template<class V, class T>
	inline typename Node<V, T> :: Value_
	Node<V, T> :: addFind
	(
		const Key_* const vector,
		const Index_ size,
		const Value_ value
	)
	{
		Node* node = addFindNode (vector, size);
		if (!node->isDefined()) {
			node->value_ = value;
		}
		return node->value_;
	}

	template<class V, class T>
	template<template<class> class H1, class A1>
	inline typename Node<V, T> :: Value_
	Node<V, T> :: find (const container :: Vector<Key_, H1, A1>* const vector) const
	{
		const Node* node = findNode (vector);
		if (node == NULL) {
			return Undefined<Value_> :: getValue();
		} else {
			return node->value_;
		}
	}
	template <class V, class T>
	inline typename Node<V, T> :: Value_
	Node<V, T> :: find (const Key_* const vector, const Index_ length) const
	{
		const Node* node = findNode (vector, length);
		if (node == NULL) {
			return Undefined<Value_> :: getValue();
		} else {
			return node->value_;
		}
	}

	template<class V, class T>
	template<template<class> class H1, class A1>
	inline void
	Node<V, T> :: setAdd
	(
		const container :: Vector<Key_, H1, A1>* const vector,
		const Value_ value
	)
	{
		Node* node = addFindNode (vector);
		node->value_ = value;
	}
	template<class V, class T>
	inline void
	Node<V, T> :: setAdd
	(
		const Key_* const vector,
		const Index_ size,
		const Value_ value
	)
	{
		Node* node = addFindNode (vector, size);
		node->value_ = value;
	}

	template<class V, class T>
	inline bool
	Node<V, T> :: isDefined() const {
		return (value_ != Undefined<Value_> :: getValue());
	}
	template<class V, class T>
	void
	Node<V, T> :: clear()
	{
		value_ = Undefined<Value_> :: getValue();
		if (child_ != NULL) {
			child_->clear();
		}
		if (next_ != NULL) {
			next_->clear();
		}
	}

	// nstd :: Object implementation
	template<class V, class T>
	inline void
	Node<V, T> :: commitSuicide() {
		delete this;
	}
	template<class V, class T>
	Size_t
	Node<V, T> :: getVolume() const
	{
		Size_t result = 0;
		if (child_ != NULL) {
			result += child_->getVolume();
			result += child_->getSizeOf();
		}
		if (next_ != NULL) {
			result += next_->getVolume();
			result += next_->getSizeOf();
		}
		return result;
	}
	template<class V, class T>
	inline Size_t
	Node<V, T> :: getSizeOf() const {
		return sizeof (Node);
	}
	template<class V, class T>
	template<class N>
	inline void
	Node<V, T> :: show (N& n) const
	{
		if (isDefined()) {
			showBack (n);
			n << " -----> " << value_ << chars :: NEW_LINE;
		}
		if (child_ != NULL) {
			child_->show (n);
		}
		if (next_ != NULL) {
			next_->show (n);
		}
	}

	/***************************
	 *		Private members
	 ***************************/

	template<class V, class T>
	template<template<class> class H1, class A1>
	Node<V, T>*
	Node<V, T> :: addFindNode
	(
		const container :: Vector<Key_, H1, A1>* const vector,
		Index_ position
	)
	{
		if (key_ == vector->getValue (position)) {
			if (vector->getSize() == position + 1) {
				return this;
			} else {
				if (child_ == NULL) {
					child_ = new Node (vector, Undefined<Value_> :: getValue(), position + 1, this);
				}
				return child_->addFindNode (vector, ++ position);
			}
		}
		if (next_ == NULL) {
			next_ = new Node (vector, Undefined<Value_> :: getValue(), position, parent_);
		}
		return next_->addFindNode (vector, position);
	}
	template<class V, class T>
	Node<V, T>*
	Node<V, T> :: addFindNode
	(
		const Key_* const vector,
		const Index_ size,
		Index_ position
	)
	{
		if (key_ == vector [position]) {
			if (size == position + 1) {
				return this;
			} else {
				if (child_ == NULL) {
					child_ = new Node (vector, size, Undefined<Value_> :: getValue(), position + 1, this);
				}
				return child_->addFindNode (vector, size, ++ position);
			}
		}
		if (next_ == NULL) {
			next_ = new Node (vector, size, Undefined<Value_> :: getValue(), position, parent_);
		}
		return next_->addFindNode (vector, size, position);
	}

	template<class V, class T>
	template<template<class> class H1, class A1>
	const Node<V, T>*
	Node<V, T> :: findNode
	(
		const container :: Vector<Key_, H1, A1>* const vector,
		Index_ position
	) const
	{
		if (key_ == vector->getValue (position)) {
			if (vector->getSize() == position + 1) {
				return this;
			} else {
				if (child_ == NULL) {
					return NULL;
				} else {
					return child_->findNode (vector, ++ position);
				}
			}
		}
		if (next_ == NULL) {
			return NULL;
		} else {
			return next_->findNode (vector, position);
		}
	}
	template <class V, class T>
	const Node<V, T>*
	Node<V, T> :: findNode
	(
		const Key_* const vector,
		const Index_ length,
		Index_ position
	) const
	{
		if (key_ == vector [position]) {
			if (length == position + 1) {
				return this;
			} else {
				if (child_ == NULL) {
					return NULL;
				} else {
					return child_->findNode (vector, length, ++ position);
				}
			}
		}
		if (next_ == NULL) {
			return NULL;
		} else {
			return next_->findNode (vector, length, position);
		}
	}

	template<class V, class T>
	template<class N>
	inline void
	Node<V, T> :: showBack (N& n) const
	{
		if (parent_ != NULL) {
			parent_->showBack (n);
		} else {
			n << chars :: TAB;
		}
		n << key_;
	}

	/********************************
	 *		Overloaded operators
	 ********************************/

	template<class V, class T, class S>
	inline S&
	operator << (S& s, const Node<V, T>& node)
	{
		node.show (s);
		return s;
	}
}
}

#endif /*NSTD_MAP_NODE_CPP_*/

