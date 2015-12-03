/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_prototype_List.ipp                   */
/* Description:     represents a node of a list (1-dimensional)              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_NODE_PROTOTYPE_LIST_IPP_
#define MDL_EXPRESSION_NODE_PROTOTYPE_LIST_IPP_

namespace mdl {
namespace expression {
namespace node {
namespace prototype {

	/****************************
	 *		Public members
	 ****************************/

	template<class T, class N, template<class, class> class S, class A>
	inline
	List<T, N, S, A> :: List
	(
		const Node_* const node,
		const Direction dir
	) :
	Singleton_ (),
	left_ (dir == direction :: RIGHT ? const_cast<Node_*>(node) : NULL),
	right_ (dir == direction :: LEFT ? const_cast<Node_*>(node) : NULL) {
	}
	template<class T, class N, template<class, class> class S, class A>
	inline
	List<T, N, S, A> :: List
	(
		const Symbol& symbol,
		const Node_* const node,
		const Direction dir
	) :
	Singleton_ (symbol),
	left_ (dir == direction :: RIGHT ? const_cast<Node_*>(node) : NULL),
	right_ (dir == direction :: LEFT ? const_cast<Node_*>(node) : NULL) {
	}
	template<class T, class N, template<class, class> class S, class A>
	inline
	List<T, N, S, A> :: ~ List() {
	}

	template<class T, class N, template<class, class> class S, class A>
	inline void
	List<T, N, S, A> :: deleteNodes() const
	{
		Singleton_ :: deleteNodes();
		if (right_ != NULL) {
			right_->deleteNodes();
			delete right_;
			right_ = NULL;
		}
	}

	template<class T, class N, template<class, class> class S, class A>
	inline typename List<T, N, S, A> :: const_Iterator_
	List<T, N, S, A> :: getIterator() const {
		return const_Iterator_ (this);
	}
	template<class T, class N, template<class, class> class S, class A>
	inline typename List<T, N, S, A> :: Iterator_
	List<T, N, S, A> :: getIterator() {
		return Iterator_ (this);
	}

	template<class T, class N, template<class, class> class S, class A>
	inline typename List<T, N, S, A> :: Node_*
	List<T, N, S, A> :: getLeft (Node_* node)
	{
		if (Symbol :: isLambda()) {
			if (left_ == NULL) {
				return node;
			}
		}
		return left_;
	}
	template<class T, class N, template<class, class> class S, class A>
	inline typename List<T, N, S, A> :: Node_*
	List<T, N, S, A> :: getRight (Node_* node)
	{
		if (Symbol :: isLambda()) {
			if (right_ == NULL) {
				return node;
			}
		}
		return right_;
	}
	template<class T, class N, template<class, class> class S, class A>
	inline const typename List<T, N, S, A> :: Node_*
	List<T, N, S, A> :: getLeft (const Node_* node) const
	{
		if (Symbol :: isLambda()) {
			if (left_ == NULL) {
				return node;
			}
		}
		return left_;
	}
	template<class T, class N, template<class, class> class S, class A>
	inline const typename List<T, N, S, A> :: Node_*
	List<T, N, S, A> :: getRight (const Node_* node) const
	{
		if (Symbol :: isLambda()) {
			if (right_ == NULL) {
				return node;
			}
		}
		return right_;
	}

	template<class T, class N, template<class, class> class S, class A>
	inline const typename List<T, N, S, A> :: Node_*
	List<T, N, S, A> :: goLeft (const Node_* node) const
	{
		if (Symbol :: isLambda()) {
			if (left_ == NULL) {
				return node;
			}
		}
		return left_;
	}
	template<class T, class N, template<class, class> class S, class A>
	inline const typename List<T, N, S, A> :: Node_*
	List<T, N, S, A> :: goRight (const Node_* node) const
	{
		if (Symbol :: isLambda()) {
			if (right_ == NULL) {
				return node;
			}
		}
		return right_;
	}
	template<class T, class N, template<class, class> class S, class A>
	void
	List<T, N, S, A> :: setLeft (const Node_* left) const {
		const_cast<const Node_*&>(left_) = left;
	}
	template<class T, class N, template<class, class> class S, class A>
	void
	List<T, N, S, A> :: setRight (const Node_* right) const {
		const_cast<const Node_*&>(right_) = right;
	}

	template<class T, class N, template<class, class> class S, class A>
	inline void
	List<T, N, S, A> :: operator = (const Symbol& symbol) {
		Singleton_ :: operator = (symbol);
	}

	template<class T, class N, template<class, class> class S, class A>
	template<Direction D>
	inline void
	List<T, N, S, A> :: link (const Node_* node)
	{
		if (D == direction :: LEFT) {
			left_ = const_cast<Node_*>(node);
		}
		if (D == direction :: RIGHT) {
			right_ = const_cast<Node_*>(node);
		}
	}
	template<class T, class N, template<class, class> class S, class A>
	template<Direction D>
	inline bool
	List<T, N, S, A> :: isTerminal() const
	{
		if (D == direction :: LEFT) {
			return (left_ == NULL);
		}
		if (D == direction :: RIGHT) {
			return (right_ == NULL);
		}
		return true;
	}

using manipulator :: endLine;
using manipulator :: space;

	template<class T, class N, template<class, class> class S, class A>
	void
	List<T, N, S, A> :: showSymbol (String& string) const {
		Singleton_ :: showSymbol (string);
	}
	template<class T, class N, template<class, class> class S, class A>
	void
	List<T, N, S, A> :: showTerms (String& string) const {
		Singleton_ :: showTerms (string);
	}
	template<class T, class N, template<class, class> class S, class A>
	void
	List<T, N, S, A> :: showBack (String& string) const
	{
		if (left_ != NULL) {
			left_->showBack (string);
		} else {
			string << tab;
		}
		Singleton_ :: showBack (string);
		string << space;
	}
	template<class T, class N, template<class, class> class S, class A>
	void
	List<T, N, S, A> :: showKind (String& string) {
		string << "List" << endLine;
	}

	// object :: Object implementation
	template<class T, class N, template<class, class> class S, class A>
	inline void
	List<T, N, S, A> :: commitSuicide() {
		delete this;
	}
	template<class T, class N, template<class, class> class S, class A>
	inline Size_t
	List<T, N, S, A> :: getVolume() const {
		return Singleton_ :: getVolume();
	}
	template<class T, class N, template<class, class> class S, class A>
	inline Size_t
	List<T, N, S, A> :: getSizeOf() const {
		return sizeof (List);
	}
	template<class T, class N, template<class, class> class S, class A>
	void
	List<T, N, S, A> :: show (String& string) const {
		Singleton_ :: show (string);
	}
	template<class T, class N, template<class, class> class S, class A>
	void
	List<T, N, S, A> :: dump() const
	{
		enum {
			INITIAL_STRING_CAPACITY = 64
		};
		String string (INITIAL_STRING_CAPACITY);
		show (string);
		std :: cout << string;
	}

	/****************************
	 *		Protected  members
	 ****************************/

	template<class T, class N, template<class, class> class S, class A>
	inline typename List<T, N, S, A> :: Node_*
	List<T, N, S, A> :: goLeft (Node_* right)
	{
		if (left_ == NULL) {
			left_ = new Node_ (right, direction :: LEFT);
		}
		return left_;
	}
	template<class T, class N, template<class, class> class S, class A>
	inline typename List<T, N, S, A> :: Node_*
	List<T, N, S, A> :: goRight (Node_* left)
	{
		if (right_ == NULL) {
			right_ = new Node_ (left, direction :: RIGHT);
		}
		return right_;
	}
}
}
}
}

#endif /*MDL_EXPRESSION_NODE_PROTOTYPE_LIST_IPP_*/
