/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_container_Singleton_Node.ipp         */
/* Description:     singleton node container for values                      */
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
	Singleton<V, H, A> :: Node_ :: Node_() :
	data_ () {
	}
	template<class V, template<class> class H, class A>
	inline
	Singleton<V, H, A> :: Node_ :: ~ Node_() {
	}

	template<class V, template<class> class H, class A>
	inline typename Singleton<V, H, A> :: Value_
	Singleton<V, H, A> :: Node_ :: getValue() const {
		return data_.getValue();
	}
	template<class V, template<class> class H, class A>
	inline typename Singleton<V, H, A> :: Value_&
	Singleton<V, H, A> :: Node_ :: getReference() {
		return data_.getReference();
	}
	template<class V, template<class> class H, class A>
	inline const typename Singleton<V, H, A> :: Value_&
	Singleton<V, H, A> :: Node_ :: getReference() const {
		return data_.getReference();
	}
	template<class V, template<class> class H, class A>
	inline const typename Singleton<V, H, A> :: Node_*
	Singleton<V, H, A> :: Node_ :: getNext() const {
		return NULL;
	}

	template<class V, template<class> class H, class A>
	inline void
	Singleton<V, H, A> :: Node_ :: copy (const Node_& node) {
		data_ = node.data_;
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Object implementation
	template<class V, template<class> class H, class A>
	inline void
	Singleton<V, H, A> :: Node_ :: commitSuicide() {
		delete this;
	}
	template<class V, template<class> class H, class A>
	inline Size_t
	Singleton<V, H, A> :: Node_ :: getVolume() const {
		return data_.getVolume();
	}
	template<class V, template<class> class H, class A>
	inline Size_t
	Singleton<V, H, A> :: Node_ :: getSizeOf() const {
		return sizeof (Node_);
	}
	template<class V, template<class> class H, class A>
	void
	Singleton<V, H, A> :: Node_ :: show (String& string) const {
		data_.show (string);
	}
	template<class V, template<class> class H, class A>
	void
	Singleton<V, H, A> :: Node_ :: dump() const
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

	/*template<class V, template<class> class H, class A>
	String&
	operator << (String& string, const Singleton<V, H, A> :: Node_& node)
	{
		node.show (string);
		string << endLine;
		return string;
	}*/
}
}
}
}


