/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_container_Set.ipp                    */
/* Description:     set container for values                                 */
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
	Set<V, H, A> :: Set() :
	set_ () {
	}
	template<class V, template<class> class H, class A>
	inline
	Set<V, H, A> :: Set (Value_ value) :
	set_ ()
	{
		if (value != Undefined<Value_> :: getValue()) {
			addValue (value);
		}
	}
	template<class V, template<class> class H, class A>
	inline
	Set<V, H, A> :: ~ Set() {
	}

	template<class V, template<class> class H, class A>
	inline void
	Set<V, H, A> :: addValue (Value_ value) {
		set_.add (value);
	}
	template<class V, template<class> class H, class A>
	inline typename Set<V, H, A> :: Value_
	Set<V, H, A> :: getValue() const {
		return set_.getFirstValue();
	}

	template<class V, template<class> class H, class A>
	inline typename Set<V, H, A> :: Container_&
	Set<V, H, A> :: container() {
		return set_;
	}
	template<class V, template<class> class H, class A>
	inline const typename Set<V, H, A> :: Container_&
	Set<V, H, A> :: getContainer() const {
		return set_;
	}

	template<class V, template<class> class H, class A>
	inline void
	Set<V, H, A> :: copy (const Set& set) {
		set_.copy (set.set_);
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Object implementation
	template<class V, template<class> class H, class A>
	inline void
	Set<V, H, A> :: commitSuicide() {
		delete this;
	}
	template<class V, template<class> class H, class A>
	inline Size_t
	Set<V, H, A> :: getVolume() const {
		return set_.getVolume();
	}
	template<class V, template<class> class H, class A>
	inline Size_t
	Set<V, H, A> :: getSizeOf() const {
		return sizeof (Set);
	}
	template<class V, template<class> class H, class A>
	void
	Set<V, H, A> :: show (String& string) const {
		set_.show (string);
	}
	template<class V, template<class> class H, class A>
	void
	Set<V, H, A> :: dump() const
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
	operator << (String& string, const Set<V, H, A>& set)
	{
		set.show (string);
		return string;
	}
}
}
}
}


