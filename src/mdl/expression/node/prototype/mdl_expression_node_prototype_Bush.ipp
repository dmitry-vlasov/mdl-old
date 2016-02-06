/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_prototype_Bush.ipp                   */
/* Description:     represents a node of a bush (tree with a boolean flag)   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace expression {
namespace node {
namespace prototype {

	/****************************
	 *		Public members
	 ****************************/

	template<class T, class N, template<class, class> class S, class A>
	inline
	Bush<T, N, S, A> :: Bush
	(
		const Node_* const node,
		const Direction direction
	) :
	Tree_ (node, direction),
	isAccessible_ (false) {
	}
	template<class T, class N, template<class, class> class S, class A>
	inline
	Bush<T, N, S, A> :: Bush
	(
		const Symbol& symbol,
		const bool isAccessible,
		const Node_* const node,
		const Direction direction
	) :
	Tree_ (symbol, node, direction),
	isAccessible_ (isAccessible) {
	}
	template<class T, class N, template<class, class> class S, class A>
	inline
	Bush<T, N, S, A> :: ~ Bush() {
	}

	template<class T, class N, template<class, class> class S, class A>
	inline typename Bush<T, N, S, A> :: const_Iterator_
	Bush<T, N, S, A> :: getIterator() const {
		return const_Iterator_ (this);
	}
	template<class T, class N, template<class, class> class S, class A>
	inline typename Bush<T, N, S, A> :: Iterator_
	Bush<T, N, S, A> :: getIterator() {
		return Iterator_ (this);
	}

	template<class T, class N, template<class, class> class S, class A>
	inline bool
	Bush<T, N, S, A> :: isAccessible() const {
		return isAccessible_;
	}
	template<class T, class N, template<class, class> class S, class A>
	inline void
	Bush<T, N, S, A> :: setAccessible (const bool isAccessible) {
		isAccessible_ = isAccessible;
	}

	template<class T, class N, template<class, class> class S, class A>
	inline void
	Bush<T, N, S, A> :: operator = (const Symbol& symbol) {
		Tree_ :: operator = (symbol);
	}

using manipulator :: endLine;
using manipulator :: tab;

	template<class T, class N, template<class, class> class S, class A>
	void
	Bush<T, N, S, A> :: showSymbol (String& string) const {
		Tree_ :: showSymbol (string);
	}
	template<class T, class N, template<class, class> class S, class A>
	void
	Bush<T, N, S, A> :: showTerms (String& string) const {
		Tree_ :: showTerms (string);
	}
	template<class T, class N, template<class, class> class S, class A>
	void
	Bush<T, N, S, A> :: showBush (String& string) const
	{
		if (Tree_ :: right_ == NULL) {
			showBack (string);
			string << endLine;
		} else {
			Tree_ :: right_->showBush (string);
		}
		if (Tree_ :: up_ != NULL) {
			Tree_ :: up_->showBush (string);
		}
	}
	template<class T, class N, template<class, class> class S, class A>
	void
	Bush<T, N, S, A> :: showBack (String& string) const
	{
		if (Tree_ :: left_ != NULL) {
			Tree_ :: left_->showBack (string);
		} else {
			string << tab;
		}
		Tree_ :: show (string);
		if (isAccessible_) {
			string << "[+] ";
		} else {
			string << "[-] ";
		}
	}
	template<class T, class N, template<class, class> class S, class A>
	void
	Bush<T, N, S, A> :: showKind (String& string) {
		string << "Bush" << endLine;
	}

	// object :: Object implementation
	template<class T, class N, template<class, class> class S, class A>
	inline void
	Bush<T, N, S, A> :: commitSuicide() {
		delete this;
	}
	template<class T, class N, template<class, class> class S, class A>
	inline Size_t
	Bush<T, N, S, A> :: getVolume () const {
		return Tree_ :: getVolume();
	}
	template<class T, class N, template<class, class> class S, class A>
	inline Size_t
	Bush<T, N, S, A> :: getSizeOf() const {
		return sizeof (Bush);
	}
	template<class T, class N, template<class, class> class S, class A>
	void
	Bush<T, N, S, A> :: show (String& string) const {
		Tree_ :: show (string);
	}
	template<class T, class N, template<class, class> class S, class A>
	void
	Bush<T, N, S, A> :: dump() const
	{
		enum {
			INITIAL_STRING_CAPACITY = 64
		};
		String string (INITIAL_STRING_CAPACITY);
		show (string);
		std :: cout << string;
	}
}
}
}
}


