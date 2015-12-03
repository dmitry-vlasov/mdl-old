/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_Object.cpp                                          */
/* Description:     abstract object base class                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_OBJECT_CPP_
#define NSTD_OBJECT_CPP_

#include "nstd_Object.hpp"

namespace nstd {

	/****************************
	 *		Public members
	 ****************************/

	void
	Object :: show (std :: ostream& os) const
	{
		if (Object :: string_ == NULL) {
			Object :: string_ = new String<> (Object :: INITAIL_STRING_CAPACITY);
		} else {
			Object :: string_->clear();
		}
		show (*(Object :: string_));
		os << *(Object :: string_);
	}

	Size_t
	Object :: getStringVolume() {
		return getAggregateVolume (string_);
	}

	inline void
	Object :: release()
	{
		if (string_ != NULL) {
			delete string_;
			string_ = NULL;
		}
	}
	template<class T>
	inline Size_t
	Object :: getAggregateVolume (const T* const aggregate)
	{
		Size_t result = 0;
		if (aggregate != NULL) {
			result += aggregate->getVolume();
			result += aggregate->getSizeOf();
		}
		return result;
	}
	Size_t
	Object :: shrinkTo (const Size_t value, const char k)
	{
		Size_t v = value;
		v = v >> k;
		v = v << k;
		return value - v;
	}

	/****************************
	 *		Protected members
	 ****************************/

	template<class T>
	inline void
	Object :: deleteAggregateObject (T*& aggregate) {
		deleteObject (aggregate);
	}
	template<class T>
	inline void
	Object :: deleteAggregateObject (T* const& aggregate) {
		deleteObject (aggregate);
	}

	template<class T>
	inline void
	Object :: deleteObject (T*& aggregate) const
	{
		if (aggregate == NULL) {
			return;
		}
		typedef
			typename type :: Unconst<T> :: Result_
			Unconst;
		const_cast<Unconst*>(aggregate)->commitSuicide();
		aggregate = NULL;
	}
	template<class T>
	inline void
	Object :: deleteObject (T* const& aggregate) const
	{
		if (aggregate == NULL) {
			return;
		}
		typedef
			typename type :: Unconst<T> :: Result_
			Unconst;
		const_cast<Unconst*>(aggregate)->commitSuicide();
		const_cast<T*&>(aggregate) = NULL;
	}

	/****************************
	 *		Operators
	 ****************************/

	inline std :: ostream&
	operator << (std :: ostream& os, const Object& object)
	{
		object.show (os);
		return os;
	}
	inline std :: ostream&
	operator << (std :: ostream& os, const Object* const object) {
		return operator << (os, *object);
	}

	inline String<>&
	operator << (String<>& string, const Object& object) {
		object.show (string);
		return string;
	}

	template<class A>
	String<A>&
	operator << (String<A>& string, const Object& object)
	{
		if (Object :: string_ == NULL) {
			Object :: string_ = new String<> (Object :: INITAIL_STRING_CAPACITY);
		} else {
			Object :: string_->clear();
		}
		object.show (*(Object :: string_));
		string << *(Object :: string_);
		return string;
	}

	/***********************************
	 *		Private static attributes
	 ***********************************/

	String<>* Object :: string_ = NULL;
}

#endif /*NSTD_OBJECT_CPP_*/
