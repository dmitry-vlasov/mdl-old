/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_memory_Interval.hpp                                 */
/* Description:     template memory interval                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MEMORY_INTERVAL_HPP_
#define NSTD_MEMORY_INTERVAL_HPP_

#include "memory/exception/nstd_memory_exception.hpp"

namespace nstd {
namespace memory {

template<class T = Byte_t>
class Interval {
public :
	typedef  T Type_;
	Interval ();
	Interval (const Interval& interval);
	Interval (Type_* const, Type_* const);
	Interval (Type_* const, const Size_t = 1);

	bool isClear() const;
	bool isEmpty() const;
	bool isNull() const;
	bool isRegular() const;
	bool isValid() const;

	bool operator == (const Interval& interval) const;
	bool operator != (const Interval& interval) const;
	bool isEqual (const Interval& interval) const;
	bool isDisjointed (const Interval& interval) const;
	bool intersectsWith (const Interval& interval) const;
	bool contains (const Type_* pointer) const;
	bool contains (const void* pointer) const;

	Type_* const beg() const;
	Type_* const end() const;

	void operator = (const Interval&);
	void copy (const Interval&);

	void shiftBeg (const Size_t);
	void shiftEnd (const Size_t);

	void setBeg (Type_* const);
	void setEnd (Type_* const);
	void setNull();

	void verify() const;

	Interval<> byteRepresentation() const;

	// interval integer parameters
	Size_t getLength() const;
	Size_t getVolume() const;
	Size_t getSizeOf() const;

	template<class S>
	void show (S&) const;
	template<class S>
	void showContents (S&) const;

private :
	template<class, class>
	friend class storage :: Scalar;
	template<class, class, class>
	friend class storage :: Vector;
	template<class>
	friend class Interval;

	friend class Space;
	friend class allocator :: Direct;
	friend class unit :: Block;
	friend class unit :: Boxed;
	friend class unit :: Disposed;
	friend class unit :: Heap;
	friend class unit :: Stack;
	friend class unit :: Standard;
	friend class unit :: Tank;
	friend class unit :: Map;

	template<class T_1>
	Interval (const Interval<T_1>&);
	void allocateScalar (const Size_t) throw (exception :: OutOfMemory);
	void allocateVector (const Size_t) throw (exception :: OutOfMemory);

	template<class S>
	S* const beg() const;
	template<class S>
	S* const end() const;

	template<class S>
	void operator = (const Interval<S>&);
	template<class S>
	void copy (const Interval<S>&);

	void empty();
	void clear();
	void destroy();

	Type_* beg_;
	Type_* end_;
};

	template<class T, class S>
	S&
	operator << (S&, Interval<T>);

	template<class T>
	bool
	operator <= (const Interval<T>&, const Interval<T>&);
	template<class T>
	bool
	operator < (const Interval<T>&, const Interval<T>&);
	template<class T>
	bool
	operator >= (const Interval<T>&, const Interval<T>&);
	template<class T>
	bool
	operator > (const Interval<T>&, const Interval<T>&);
}
}

#endif /*NSTD_MEMORY_INTERVAL_HPP_*/
