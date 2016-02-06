/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_Object.hpp                                          */
/* Description:     abstract object base class                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "nstd_String.hpp"

namespace nstd {

class Object {
public :
	virtual void commitSuicide() = 0;
	virtual Size_t getVolume() const = 0;
	virtual Size_t getSizeOf() const = 0;
	virtual void show (String<>&) const = 0;
	virtual void show (std :: ostream&) const;

	static Size_t getStringVolume();

	static void release();
	template<class T>
	static Size_t getAggregateVolume (const T*);
	static Size_t shrinkTo (const Size_t, const char k = 32 /* digits */);

protected :
	template<class>
	friend class Static;

	template<class T>
	void deleteAggregateObject (T*&);
	template<class T>
	void deleteAggregateObject (T* const&);

	template<class T>
	void deleteObject (T*&) const;
	template<class T>
	void deleteObject (T* const&) const;

	friend std :: ostream&
	operator << (std :: ostream&,  const Object&);
	template<class A>
	friend String<A>&
	operator << (String<A>&, const Object&);

	enum {
		INITAIL_STRING_CAPACITY = size :: KILOBYTE * 4
	};
	static String<>* string_;
};
}

#include <ostream>

namespace nstd {

	std :: ostream&
	operator << (std :: ostream&, const Object&);
	std :: ostream&
	operator << (std :: ostream&, const Object* const);
	String<>&
	operator << (String<>&, const Object&);
	template<class A>
	String<A>&
	operator << (String<A>&, const Object&);
}


