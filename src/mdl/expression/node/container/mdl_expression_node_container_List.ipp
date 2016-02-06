/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_container_List.ipp                   */
/* Description:     list container for values                                */
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
namespace container {

	/****************************
	 *		Public members
	 ****************************/

	template<class V, template<class> class H, class A>
	inline
	List<V, H, A> :: List() :
	list_ () {
	}
	template<class V, template<class> class H, class A>
	inline
	List<V, H, A> :: List (Value_ value) :
	list_ ()
	{
		if (value != Undefined<Value_> :: getValue()) {
			addValue (value);
		}
	}
	template<class V, template<class> class H, class A>
	inline
	List<V, H, A> :: ~ List() {
	}

	template<class V, template<class> class H, class A>
	inline const typename List<V, H, A> :: Node_*
	List<V, H, A> :: getFirst() const {
		return list_.getFirst();
	}
	template<class V, template<class> class H, class A>
	inline const typename List<V, H, A> :: Node_*
	List<V, H, A> :: getLast() const {
		return list_.getLast();
	}
	template<class V, template<class> class H, class A>
	inline void
	List<V, H, A> :: addValue (Value_ value) {
		list_.addLast (value);
	}
	template<class V, template<class> class H, class A>
	inline typename List<V, H, A> :: Value_
	List<V, H, A> :: getValue() const
	{
		const Node_* const
			node = list_.getFirst();
		return node->getValue();
	}

	template<class V, template<class> class H, class A>
	inline typename List<V, H, A> :: Container_&
	List<V, H, A> :: container() {
		return list_;
	}
	template<class V, template<class> class H, class A>
	inline const typename List<V, H, A> :: Container_&
	List<V, H, A> :: getContainer() const {
		return list_;
	}

	template<class V, template<class> class H, class A>
	inline void
	List<V, H, A> :: copy (const List& list) {
		list_.copy (list.list_);
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Object implementation
	template<class V, template<class> class H, class A>
	inline void
	List<V, H, A> :: commitSuicide() {
		delete this;
	}
	template<class V, template<class> class H, class A>
	inline Size_t
	List<V, H, A> :: getVolume() const {
		return list_.getVolume();
	}
	template<class V, template<class> class H, class A>
	inline Size_t
	List<V, H, A> :: getSizeOf() const {
		return sizeof (List);
	}
	template<class V, template<class> class H, class A>
	void
	List<V, H, A> :: show (String& string) const {
		list_.show (string);
	}
	template<class V, template<class> class H, class A>
	void
	List<V, H, A> :: dump() const
	{
		enum {
			INITIAL_STRING_CAPACITY = 64
		};
		String string (INITIAL_STRING_CAPACITY);
		show (string);
		std :: cout << string;
	}

	/******************************
	 *		Overloaded operators
	 ******************************/

	template<class V, template<class> class H, class A>
	String&
	operator << (String& string, const List<V, H, A>& list)
	{
		list.show (string);
		return string;
	}
}
}
}
}


