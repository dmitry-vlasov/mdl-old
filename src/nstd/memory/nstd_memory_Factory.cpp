/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_Factory.cpp                                  */
/* Description:     template factory for objects                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace nstd {
namespace memory {

	/****************************
	 *		Public members
	 ****************************/

	template<class T, class A>
	inline typename Factory<T, A> :: Type_*
	Factory<T, A> :: create() {
		void* place = Storage_ :: operator new (sizeof (Type_));
		return new (place) Type_ ();
	}
	template<class T, class A>
	template<class A_1>
	inline typename Factory<T, A> :: Type_*
	Factory<T, A> :: create (A_1 value) {
		void* place = Storage_ :: operator new (sizeof (Type_));
		return new (place) Type_ (value);
	}
	template<class T, class A>
	template<class A_1, class A_2>
	inline typename Factory<T, A> :: Type_*
	Factory<T, A> :: create (A_1 value_1, A_2 value_2) {
		void* place = Storage_ :: operator new (sizeof (Type_));
		return new (place) Type_ (value_1, value_2);
	}
	template<class T, class A>
	template<class A_1, class A_2, class A_3>
	inline typename Factory<T, A> :: Type_*
	Factory<T, A> :: create (A_1 value_1, A_2 value_2, A_3 value_3) {
		void* place = Storage_ :: operator new (sizeof (Type_));
		return new (place) Type_ (value_1, value_2, value_3);
	}
	template<class T, class A>
	template<class A_1, class A_2, class A_3, class A_4>
	inline typename Factory<T, A> :: Type_*
	Factory<T, A> :: create (A_1 value_1, A_2 value_2, A_3 value_3, A_4 value_4) {
		void* place = Storage_ :: operator new (sizeof (Type_));
		return new (place) Type_ (value_1, value_2, value_3, value_4);
	}
	template<class T, class A>
	template<class A_1, class A_2, class A_3, class A_4, class A_5>
	inline typename Factory<T, A> :: Type_*
	Factory<T, A> :: create (A_1 value_1, A_2 value_2, A_3 value_3, A_4 value_4, A_5 value_5)
	{
		void* place = Storage_ :: operator new (sizeof (Type_));
		return new (place) Type_ (value_1, value_2, value_3, value_4, value_5);
	}
	template<class T, class A>
	template<class A_1, class A_2, class A_3, class A_4, class A_5, class A_6>
	inline typename Factory<T, A> :: Type_*
	Factory<T, A> :: create (A_1 value_1, A_2 value_2, A_3 value_3, A_4 value_4, A_5 value_5, A_6 value_6)
	{
		void* place = Storage_ :: operator new (sizeof (Type_));
		return new (place) Type_ (value_1, value_2, value_3, value_4, value_5, value_6);
	}
}
}


