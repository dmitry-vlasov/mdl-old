/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_storage_ByInheritance.cpp                 */
/* Description:     inheritance storage policy for containers                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONTAINER_STORAGE_BY_INHERITANCE_CPP_
#define NSTD_CONTAINER_STORAGE_BY_INHERITANCE_CPP_

namespace nstd {
namespace container {
namespace storage {

	/****************************
	 *		Public members
	 ****************************/

	template<class T>
	inline
	ByInheritance<T> :: ByInheritance() :
	Ancestor_ () {
	}
	template<class T>
	inline
    ByInheritance<T> :: ByInheritance (Argument_ data) :
	Ancestor_ (data) {
	}
    template<class T>
    inline
    ByInheritance<T> :: ByInheritance (const ByInheritance& data) :
    Ancestor_ (data) {
    }

    template<class T>
	inline typename ByInheritance<T> :: Value_
	ByInheritance<T> :: getValue() const {
		return *this;
	}
    template<class T>
	inline typename ByInheritance<T> :: Reference_
	ByInheritance<T> :: getReference() {
		return *this;
	}
    template<class T>
	inline typename ByInheritance<T> :: const_Reference_
	ByInheritance<T> :: getReference() const {
		return *this;
	}

    template<class T>
	inline void
	ByInheritance<T> :: undefine() {
		Ancestor_ :: undefine();
	}
    template<class T>
	inline void
	ByInheritance<T> :: clear() {
		Ancestor_ :: clear();
	}
    template<class T>
	inline void
	ByInheritance<T> :: erase() {
		Ancestor_ :: undefine();
	}
    template<class T>
	inline void
	ByInheritance<T> :: init() {
		Ancestor_ :: init();
	}

    // nstd :: Object implementation
    template<class T>
	inline void
	ByInheritance<T> :: commitSuicide() {
    	Ancestor_ :: commitSuicide();
    }
    template<class T>
	inline Size_t
	ByInheritance<T> :: getVolume() const {
		return Ancestor_ :: getVolume();
	}
    template<class T>
	inline Size_t
	ByInheritance<T> :: getSizeOf() const {
		return sizeof (ByInheritance);
	}
    template<class T>
	template<class S>
	void
	ByInheritance<T> :: show (S& string) const {
		Ancestor_ :: show (string);
	}

    /****************************
	 *		Overloaded operators
	 ****************************/

	template<class T, class S>
	S&
	operator << (S& s, const ByInheritance<T>& storage)
	{
		storage.show (s);
		return s;
	}
}
}
}

#endif /*NSTD_CONTAINER_STORAGE_BY_INHERITANCE_CPP_*/
