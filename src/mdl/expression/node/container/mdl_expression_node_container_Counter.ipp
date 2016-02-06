/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_container_Counter.ipp                */
/* Description:     fictive container for values: it only counts them        */
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
	Counter<V, H, A> :: Counter() :
	count_ (0) {
	}
	template<class V, template<class> class H, class A>
	inline
	Counter<V, H, A> :: Counter (Value_ value) :
	count_ (0)
	{
		if (value != Undefined<Value_> :: getValue()) {
			addValue (value);
		}
	}
	template<class V, template<class> class H, class A>
	inline
	Counter<V, H, A> :: ~ Counter() {
	}

	template<class V, template<class> class H, class A>
	inline void
	Counter<V, H, A> :: addValue (Value_ value) {
		++ count_;
	}
	template<class V, template<class> class H, class A>
	inline value :: Integer
	Counter<V, H, A> :: getCount() const {
		return count_;
	}

	template<class V, template<class> class H, class A>
	inline void
	Counter<V, H, A> :: copy (const Counter& counter) {
		count_ = counter.count_;
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Object implementation
	template<class V, template<class> class H, class A>
	inline void
	Counter<V, H, A> :: commitSuicide() {
		delete this;
	}
	template<class V, template<class> class H, class A>
	inline Size_t
	Counter<V, H, A> :: getVolume() const {
		return 0;
	}
	template<class V, template<class> class H, class A>
	inline Size_t
	Counter<V, H, A> :: getSizeOf() const {
		return sizeof (Counter);
	}
	template<class V, template<class> class H, class A>
	void
	Counter<V, H, A> :: show (String& string) const {
		string << "count = " << count_ << ", ";
	}
	template<class V, template<class> class H, class A>
	void
	Counter<V, H, A> :: dump() const
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
	operator << (String& string, const Counter<V, H, A>& counter)
	{
		counter.show (string);
		return string;
	}
}
}
}
}


