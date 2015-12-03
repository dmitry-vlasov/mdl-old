/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_storage_ByPointer.hpp                     */
/* Description:     storage policy by pointer for containers                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONTAINER_STORAGE_BY_POINTER_HPP_
#define NSTD_CONTAINER_STORAGE_BY_POINTER_HPP_

#include "container/storage/nstd_container_storage_ByAggregation.hpp"

namespace nstd {
namespace container {
namespace storage {

template
<
	class T	// Stored type
>
class ByPointer : public ByAggregation<T*> {
	typedef ByAggregation<T*> Ancestor_;
public :
	typedef T UnpointerType_;
	typedef typename Ancestor_ :: Type_ Type_;
	typedef typename Ancestor_ :: Argument_ Argument_;
	typedef typename Ancestor_ :: Value_ Value_;
	typedef typename Ancestor_ :: Reference_ Reference_;
	typedef typename Ancestor_ :: const_Reference_ const_Reference_;

	ByPointer ();
	ByPointer (typename Ancestor_ :: Argument_);
	ByPointer (const ByPointer&);
	~ ByPointer();

	void clear();
	void erase();
	void init();

	// operators with Argument_
	bool operator == (Argument_) const;
	bool operator != (Argument_) const;
	bool operator < (Argument_) const;
	bool operator <= (Argument_) const;
	bool operator > (Argument_) const;
	bool operator >= (Argument_) const;
	void operator = (Argument_);

	// operators with ByValue<Type_>
	bool operator == (const ByValue<Type_>&) const;
	bool operator != (const ByValue<Type_>&) const;
	bool operator < (const ByValue<Type_>&) const;
	bool operator <= (const ByValue<Type_>&) const;
	bool operator > (const ByValue<Type_>&) const;
	bool operator >= (const ByValue<Type_>&) const;
	void operator = (const ByValue<Type_>&);

	// operators with ByPointer
	bool operator == (const ByPointer&) const;
	bool operator != (const ByPointer&) const;
	bool operator < (const ByPointer&) const;
	bool operator <= (const ByPointer&) const;
	bool operator > (const ByPointer&) const;
	bool operator >= (const ByPointer&) const;
	void operator = (const ByPointer&);

	// nstd :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	template<class S>
	void show (S&) const;
};

	template<class T, class S>
	S&
	operator << (S&, const ByPointer<T>&);
}
}
}

#endif /*NSTD_CONTAINER_STORAGE_BY_POINTER_HPP_*/
