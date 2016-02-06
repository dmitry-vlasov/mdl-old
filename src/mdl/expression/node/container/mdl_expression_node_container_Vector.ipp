/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_container_Vector.ipp                 */
/* Description:     vector container for values                              */
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
	Vector<V, H, A> :: Vector() :
	vector_ () {
	}
	template<class V, template<class> class H, class A>
	inline
	Vector<V, H, A> :: Vector (Value_ value) :
	vector_ ()
	{
		if (value != Undefined<Value_> :: getValue()) {
			addValue (value);
		}
	}
	template<class V, template<class> class H, class A>
	inline
	Vector<V, H, A> :: ~ Vector() {
	}

	template<class V, template<class> class H, class A>
	inline void
	Vector<V, H, A> :: addValue (Value_ value) {
		vector_.add (value);
	}
	template<class V, template<class> class H, class A>
	inline typename Vector<V, H, A> :: Value_
	Vector<V, H, A> :: getValue() const {
		return vector_.getFirstValue();
	}

	template<class V, template<class> class H, class A>
	inline typename Vector<V, H, A> :: Container_&
	Vector<V, H, A> :: container() {
		return vector_;
	}
	template<class V, template<class> class H, class A>
	inline const typename Vector<V, H, A> :: Container_&
	Vector<V, H, A> :: getContainer() const {
		return vector_;
	}

	template<class V, template<class> class H, class A>
	inline void
	Vector<V, H, A> :: copy (const Vector& vector) {
		vector_.copy (vector.vector_);
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Object implementation
	template<class V, template<class> class H, class A>
	inline void
	Vector<V, H, A> :: commitSuicide() {
		delete this;
	}
	template<class V, template<class> class H, class A>
	inline Size_t
	Vector<V, H, A> :: getVolume() const {
		return vector_.getVolume();
	}
	template<class V, template<class> class H, class A>
	inline Size_t
	Vector<V, H, A> :: getSizeOf() const {
		return sizeof (Vector);
	}
	template<class V, template<class> class H, class A>
	void
	Vector<V, H, A> :: show (String& string) const {
		vector_.show (string);
	}
	template<class V, template<class> class H, class A>
	void
	Vector<V, H, A> :: dump() const
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
	operator << (String& string, const Vector<V, H, A>& vector)
	{
		vector.show (string);
		return string;
	}
}
}
}
}


