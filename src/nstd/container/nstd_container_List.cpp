/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_List.cpp                                  */
/* Description:     list container                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONTAINER_LIST_CPP_
#define NSTD_CONTAINER_LIST_CPP_

namespace nstd {
namespace container {

	/****************************
	 *		Public members
	 ****************************/

	template
	<
		class T,
		template<class> class H,
		class A,
		template<class, class, class> class N
	>
	inline
	List<T, H, A, N> :: List () :
	first_ (NULL),
	last_ (NULL) {
	}
	template
	<
		class T,
		template<class> class H,
		class A,
		template<class, class, class> class N
	>
	inline
	List<T, H, A, N> :: List (const List& list) :
	first_ (list.first_),
	last_ (list.last_) {
	}
	template
	<
		class T,
		template<class> class H,
		class A,
		template<class, class, class> class N
	>
	List<T, H, A, N> :: ~ List()
	{
		if (first_ == NULL) {
			return;
		}
		const Node_* node = first_;
		while (node != last_) {
			const Node_* next = node->getNext();
			const_cast<Node_*>(node)->commitSuicide();
			node = next;
		}
		const_cast<Node_*>(node)->commitSuicide();
		first_ = NULL;
		last_ = NULL;
	}

	template
	<
		class T,
		template<class> class H,
		class A,
		template<class, class, class> class N
	>
	inline
	List<T, H, A, N> :: Node_ :: Node_
	(
		const Argument_ argument,
		const discrete :: Direction direction,
		const Node_* node
	) :
	Ancestor_ (argument, direction, node) {
	}

	template
	<
		class T,
		template<class> class H,
		class A,
		template<class, class, class> class N
	>
	inline void
	List<T, H, A, N> :: operator = (const List& list) {
		first_ = list.first_;
		last_ = list.last_;
	}
	template
	<
		class T,
		template<class> class H,
		class A,
		template<class, class, class> class N
	>
	void
	List<T, H, A, N> :: copy (const List& list)
	{
		clear();
		const Node_* node = list.getFirst();
		while (node != NULL) {
			addLast (node->getValue());
			node = node->getNext();
		}
	}

	template
	<
		class T,
		template<class> class H,
		class A,
		template<class, class, class> class N
	>
	inline const typename List<T, H, A, N> :: Node_*
	List<T, H, A, N> :: getFirst() const {
		return first_;
	}
	template
	<
		class T,
		template<class> class H,
		class A,
		template<class, class, class> class N
	>
	inline const typename List<T, H, A, N> :: Node_*
	List<T, H, A, N> :: getLast() const {
		return last_;
	}

	template
	<
		class T,
		template<class> class H,
		class A,
		template<class, class, class> class N
	>
	void
	List<T, H, A, N> :: addFirst (Argument_ argument)
	{
		if (first_ == NULL) {
			last_ = new Node_ (argument, discrete :: RIGHT);
			first_ = last_;
		} else {
			first_ = new Node_ (argument, discrete :: RIGHT, first_);
		}
	}
	template
	<
		class T,
		template<class> class H,
		class A,
		template<class, class, class> class N
	>
	void
	List<T, H, A, N> :: addLast (Argument_ argument)
	{
		if (first_ == NULL) {
			first_ = new Node_ (argument, discrete :: LEFT);
			last_ = first_;
		} else {
			last_ = new Node_ (argument, discrete :: LEFT, last_);
		}
	}
	template
	<
		class T,
		template<class> class H,
		class A,
		template<class, class, class> class N
	>
	void
	List<T, H, A, N> :: insertNextTo (Argument_ argument, const Argument_ sibling)
	{
		if (first_ == NULL) {
			first_ = new Node_ (argument, discrete :: LEFT);
			last_ = first_;
		} else if (last_->getValue() == sibling) {
			addLast (argument);
		} else {
			const Node_*
			node = first_;
			while (node != last_) {
				if (node->getValue() == sibling) {
					const Node_* next = node->getNext();
					Node_* insertion = new Node_ (argument, discrete :: LEFT, node);
					insertion->setNext (next);
					return;
				}
				node = node->getNext();
			}
		}
	}

	template
	<
		class T,
		template<class> class H,
		class A,
		template<class, class, class> class N
	>
	void
	List<T, H, A, N> :: intersect (const List& list)
	{
		if (isEmpty()) {
			return;
		}
		const Node_* node = first_;
		const Node_* prev = NULL;
		const Node_* next = NULL;
		const Node_* first = NULL;
		const Node_* last = NULL;
		while (node != NULL) {
			next = node->getNext();
			if (!list.contains (node->getValue())) {
				Node_ :: remove (prev, node, next);
			} else {
				if (first == NULL) {
					first = node;
				}
				last = node;
				prev = node;
			}
			node = next;
		}
		first_ = first;
		last_ = last;
	}
	template
	<
		class T,
		template<class> class H,
		class A,
		template<class, class, class> class N
	>
	bool
	List<T, H, A, N> :: contains (Argument_ value) const
	{
		if (isEmpty()) {
			return false;
		}
		const Node_*
			node = first_;
		while (node != last_) {
			if (node->getValue() == value) {
				return true;
			}
			node = node->getNext();
		}
		return (last_->getValue() == value);
	}

	template
	<
		class T,
		template<class> class H,
		class A,
		template<class, class, class> class N
	>
	void
	List<T, H, A, N> :: join (const List& list)
	{
		if (list.isEmpty()) {
			return;
		}
		if (first_ == NULL) {
			first_ = list.first_;
			last_ = list.last_;
			return;
		}
		last_->setNext (list.first_);
		last_ = list.last_;
	}
	template
	<
		class T,
		template<class> class H,
		class A,
		template<class, class, class> class N
	>
	void
	List<T, H, A, N> :: unite (const List& list)
	{
		if (list.isEmpty()) {
			return;
		}
		const Node_* node = list.getFirst();
		while (node != list.getLast()) {
			addLast (node->getValue());
			node = node->getNext();
		}
		addLast (list.getLast()->getValue());
	}
	template
	<
		class T,
		template<class> class H,
		class A,
		template<class, class, class> class N
	>
	void
	List<T, H, A, N> :: clear()
	{
		if (isEmpty()) {
			return;
		}
		const Node_* node = first_;
		const Node_* next = NULL;
		while (node != NULL) {
			next = node->getNext();
			delete node;
			node = next;
		}
		first_ = NULL;
		last_ = NULL;
	}

	template
	<
		class T,
		template<class> class H,
		class A,
		template<class, class, class> class N
	>
	inline bool
	List<T, H, A, N> :: isEmpty () const {
		return first_ == NULL;
	}
	template
	<
		class T,
		template<class> class H,
		class A,
		template<class, class, class> class N
	>
	inline bool
	List<T, H, A, N> :: isSingleton() const {
		return !(isEmpty()) && (first_ == last_);
	}
	template
	<
		class T,
		template<class> class H,
		class A,
		template<class, class, class> class N
	>
	bool
	List<T, H, A, N> :: hasNoRepeats() const
	{
		if (isEmpty()) {
			return true;
		}
		const Node_* node_1 = first_;
		while (node_1 != last_) {
			const Node_* node_2 = node_1->getNext();
			while (node_2 != NULL) {
				if (node_1->getValue() == node_2->getValue()) {
					return false;
				}
				node_2 = node_2->getNext();
			}
			node_1 = node_1->getNext();
		}
		return true;
	}
	template
	<
		class T,
		template<class> class H,
		class A,
		template<class, class, class> class N
	>
	Size_t
	List<T, H, A, N> :: getSize() const
	{
		if (first_ == NULL) {
			return 0;
		}
		Size_t size = 1;
		const Node_*
			node = first_;
		while (node != last_) {
			++ size;
			node = node->getNext();
		}
		return size;
	}

	// nstd :: Object implementation
	template
	<
		class T,
		template<class> class H,
		class A,
		template<class, class, class> class N
	>
	inline void
	List<T, H, A, N> :: commitSuicide() {
		delete this;
	}
	template
	<
		class T,
		template<class> class H,
		class A,
		template<class, class, class> class N
	>
	Size_t
	List<T, H, A, N> :: getVolume () const
	{
		Size_t volume = 0;
		const Node_*
			node = first_;
		while (node != last_) {
			volume += node->getVolume();
			volume += node->getSizeOf();
			node = node->getNext();
		}
		if (node != NULL) {
			volume += node->getVolume();
			volume += node->getSizeOf();
		}
		return volume;
	}
	template
	<
		class T,
		template<class> class H,
		class A,
		template<class, class, class> class N
	>
	inline Size_t
	List<T, H, A, N> :: getSizeOf() const {
		return sizeof (List);
	}
	template
	<
		class T,
		template<class> class H,
		class A,
		template<class, class, class> class N
	>
	template<class S>
	void
	List<T, H, A, N> :: show (S& s) const
	{
		const Node_*
			node = first_;
		while (node != last_) {
			node->show (s);
			node = node->getNext();
		}
		if (node != NULL) {
			node->show (s);
		}
	}

	/********************************
	 *		Overloaded operators
	 ********************************/

	template
	<
		class T,
		template<class> class H,
		class A,
		template<class, class, class> class N,
		class S
	>
	S&
	operator << (S& s, const List<T, H, A, N>& list)
	{
		list.show (s);
		return s;
	}
}
}

#endif /* NSTD_CONTAINER_LIST_CPP_ */
