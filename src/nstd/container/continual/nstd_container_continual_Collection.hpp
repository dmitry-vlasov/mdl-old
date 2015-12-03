/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_container_continual_Collection.hpp                  */
/* Description:     base class for all array-based containers                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_CONTAINER_CONTINUAL_COLLECTION_HPP_
#define NSTD_CONTAINER_CONTINUAL_COLLECTION_HPP_

namespace nstd {
namespace container {
namespace continual {

template
<
	class T,                ///< stored type
	template<class> class H ///< storage policy (by value, by pointer, etc.)
>
class Collection {
public :
	typedef Size_t Index_;
	typedef H<T> Storage_;
	typedef typename Storage_ :: Type_ Type_;
	typedef typename Storage_ :: Argument_ Argument_;
	typedef typename Storage_ :: Value_ Value_;
	typedef typename Storage_ :: Reference_ Reference_;
	typedef typename Storage_ :: const_Reference_ const_Reference_;

	Collection();
	template<class T1, template<class> class H1>
	Collection (const Collection<T1, H1>&);

	bool contains (Argument_ value) const;
	Index_ find (Argument_ value) const;

	Reference_ operator [] (const Index_);
	const_Reference_ operator [] (const Index_) const;
	Value_ getValue (const Index_) const;
	Reference_ getReference (const Index_);
	const_Reference_ getReference (const Index_) const;
	Value_ getLastValue() const;
	Value_ getFirstValue() const;
	Reference_ getLastReference();
	Reference_ getFirstReference();
	const_Reference_ getLastReference() const;
	const_Reference_ getFirstReference() const;

	void set (const Index_, const Argument_);

	template<class T1, template<class> class H1>
	bool operator == (const Collection<T1, H1>&) const;
	template<class T1, template<class> class H1>
	bool operator != (const Collection<T1, H1>&) const;
	template<class T1, template<class> class H1>
	bool isEqual (const Collection<T1, H1>&) const;
	bool isEqual (const Type_*, const Index_) const;

	void swap (const Index_, const Index_);
	bool isNull() const;
	bool isEmpty() const;
	bool isSingleton() const;

	void clear();
	void erase();
	void reverse();

	Index_ getSize() const;
	Size_t getRawVolume() const;
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	template<class S>
	void show (S&) const;

	const Storage_* getData() const;

protected :
	template<class, template<class> class>
	friend class Collection;

	template<class T1, template<class> class H1>
	void copy (const Collection<T1, H1>&);
	void copy (const Collection&);
	void copy (const Type_* const, const Index_);
	template<class V>
	static void memMove
	(
		Storage_* destination,
		const V* const source,
		Index_ const count,
		const bool backwards = false
	);
	static void memMove
	(
		Storage_* destination,
		const Type_* source,
		Index_ const count,
		const bool backwards = false
	);
	void undefineArray ();

	Size_t size_;
	Storage_* data_;
};

	template<class S, class T, template<class> class H >
	S&
	operator << (S&, const Collection<T, H>&);
}
}
}

#endif /*NSTD_CONTAINER_CONTINUAL_COLLECTION_HPP_*/
