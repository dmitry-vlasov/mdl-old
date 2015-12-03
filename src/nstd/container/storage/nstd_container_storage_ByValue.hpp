/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_storage_ByValue.hpp                       */
/* Description:     storage policy by value for containers                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONTAINER_STORAGE_BY_VALUE_HPP_
#define NSTD_CONTAINER_STORAGE_BY_VALUE_HPP_

#include "container/storage/nstd_container_storage_ByAggregation.hpp"

namespace nstd {
namespace container {
namespace storage {

template
<
	class T	// Stored type
>
class ByValue : public ByAggregation<T> {
	typedef ByAggregation<T> Ancestor_;
public :
	typedef typename Ancestor_ :: Type_ Type_;
	typedef typename Ancestor_ :: Argument_ Argument_;
	typedef typename Ancestor_ :: Value_ Value_;
	typedef typename Ancestor_ :: Reference_ Reference_;
	typedef typename Ancestor_ :: const_Reference_ const_Reference_;

	ByValue();
    ByValue (typename Ancestor_ :: Argument_);
    ByValue (const ByValue&);
    ~ ByValue();

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

	// operators with ByValue
	bool operator == (const ByValue&) const;
	bool operator != (const ByValue&) const;
	bool operator < (const ByValue&) const;
	bool operator <= (const ByValue&) const;
	bool operator > (const ByValue&) const;
	bool operator >= (const ByValue&) const;
	void operator = (const ByValue&);

	// nstd :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	template<class S>
	void show (S&) const;
};

	template<class T, class S>
	S& operator << (S&, const ByValue<T>&);
}
}
}

#endif /*NSTD_CONTAINER_STORAGE_BY_VALUE_HPP_*/
