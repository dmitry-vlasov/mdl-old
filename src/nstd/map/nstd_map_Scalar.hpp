/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_map_Scalar.hpp                                      */
/* Description:     scalar mapping                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_MAP_SCALAR_HPP_
#define NSTD_MAP_SCALAR_HPP_

#include "container/nstd_container_Vector.hpp"
#include "container/nstd_container_Set.hpp"

namespace nstd {
namespace map {

template
<
	class K, ///< key type
	class T, ///< value type
	class A  ///< allocator
>
class Scalar :
	public memory :: storage :: Scalar
	<
		Scalar<K, T, A>,
		A
	> {
enum { INITIAL_CAPACITY = 64 };
public :
	typedef A Allocator_;
	typedef K Key_;
	typedef T Value_;

	typedef
		typename container :: Set
		<
			Key_,
			container :: storage :: ByValue,
			Allocator_
		>
		KeyContainer_;
	typedef
		typename container :: Vector
		<
			Value_,
			container :: storage :: ByValue,
			Allocator_
		>
		ValueContainer_;
	typedef
		typename KeyContainer_ :: Index_
		Index_;

	Scalar ();
	Scalar (const Index_);
	virtual ~ Scalar();

	void add (const Key_, const Value_);
	void set (const Key_, const Value_);
	void remove (const Key_);
	void removeDec (const Key_, const Value_);
	void replaceKey (const Key_, const Key_);
	void replaceValue (const Value_, const Value_);
	void decValue (const Value_);
	Value_ find (const Key_) const;
	Value_ addFind (const Key_, const Value_);
	Index_ findIndex (const Key_) const;
	Index_ findPlace (const Key_) const;
	Index_ getSize() const;
	bool containsKey (const Key_) const;

	Key_ getKey (const Index_) const;
	Value_ getValue (const Index_) const;
	Key_ getFirstKey() const;
	Value_ getFirstValue() const;
	Key_ getLastKey() const;
	Value_ getLastValue() const;
	Key_& key (const Index_);
	Value_& value (const Index_);
	Key_& firstKey();
	Value_& firstValue();
	Key_& lastKey();
	Value_& lastValue();

	void clear();
	void init();

	// nstd :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	template<class S>
	void show (S&) const;

private :
	KeyContainer_ keyContainer_;
	ValueContainer_ valueContainer_;
};

	template<class K, class T, class A, class S>
	S&
	operator << (S&, const Scalar<K, T, A>&);
}
}

#endif /*NSTD_MAP_SCALAR_HPP_*/
