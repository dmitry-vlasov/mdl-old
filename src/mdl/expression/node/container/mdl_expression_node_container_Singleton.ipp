/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_container_Singleton.ipp              */
/* Description:     singleton container for values                           */
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
	Singleton<V, H, A> :: Singleton() :
	node_ (NULL) {
	}
	template<class V, template<class> class H, class A>
	inline
	Singleton<V, H, A> :: Singleton (Value_ value) :
	node_ (NULL)
	{
		if (value != Undefined<Value_> :: getValue()) {
			addValue (value);
		}
	}
	template<class V, template<class> class H, class A>
	inline
	Singleton<V, H, A> :: ~ Singleton()
	{
		if (node_ != NULL) {
			delete node_;
			node_ = NULL;
		}
	}

	template<class V, template<class> class H, class A>
	inline const typename Singleton<V, H, A> :: Node_*
	Singleton<V, H, A> :: getFirst() const {
		return node_;
	}
	template<class V, template<class> class H, class A>
	inline const typename Singleton<V, H, A> :: Node_*
	Singleton<V, H, A> :: getLast() const {
		return node_;
	}
	template<class V, template<class> class H, class A>
	inline void
	Singleton<V, H, A> :: addValue (Value_ value)
	{
		if (node_ == NULL) {
			node_ = new Node_ ();
		}
		node_->getReference() = value;
	}
	template<class V, template<class> class H, class A>
	inline typename Singleton<V, H, A> :: Value_
	Singleton<V, H, A> :: getValue() const
	{
		if (node_ != NULL) {
			return node_->getValue();
		} else {
			return Undefined<Value_> :: getValue();
		}
	}

	template<class V, template<class> class H, class A>
	inline void
	Singleton<V, H, A> :: copy (const Singleton& singleton) {
		node_->copy (*singleton.node_);
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Object implementation
	template<class V, template<class> class H, class A>
	inline void
	Singleton<V, H, A> :: commitSuicide() {
		delete this;
	}
	template<class V, template<class> class H, class A>
	inline Size_t
	Singleton<V, H, A> :: getVolume () const
	{
		Size_t volume = 0;
		if (node_ != NULL) {
			volume += node_->getVolume();
			volume += node_->getSizeOf();
		}
		return volume;
	}
	template<class V, template<class> class H, class A>
	inline Size_t
	Singleton<V, H, A> :: getSizeOf() const {
		return sizeof (Singleton);
	}
	template<class V, template<class> class H, class A>
	void
	Singleton<V, H, A> :: show (String& string) const
	{
		if (node_ != NULL) {
			node_->show (string);
		} else {
			string << "NULL";
		}
	}
	template<class V, template<class> class H, class A>
	void
	Singleton<V, H, A> :: dump() const
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
	operator << (String& string, const Singleton<V, H, A>& singleton)
	{
		singleton.show (string);
		return string;
	}
}
}
}
}

#include "mdl/expression/node/container/mdl_expression_node_container_Singleton_Node.ipp"


