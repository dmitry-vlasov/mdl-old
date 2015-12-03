/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_NameTable.hpp                                       */
/* Description:     general class tables of identificators                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_NAME_TABLE_HPP_
#define NSTD_NAME_TABLE_HPP_

#include "nstd_Object.hpp"

namespace nstd {

/* Table of symbolic names for parsers. */
template
<
	class T, //< value type
	class A  //< allocator
>
class NameTable :
	public memory :: storage :: Scalar
	<
		NameTable<T, A>,
		A
	>,
	public Object {
public :
	enum {
		INITIAL_NAME_VECTOR_CAPACITY = 4 * size :: KILOBYTE
	};

	typedef A Allocator_;
	typedef T Value_;
	typedef
		typename map :: String<Value_, Allocator_>
		NameMap_;
	typedef
		typename NameMap_ :: StringKey_
		NameString_;
	typedef
		typename container :: Vector
		<
			const NameString_,
			container :: storage :: ByPointer,
			Allocator_
		>
		NameVector_;
	typedef
		typename NameVector_ :: Index_
		Index_;

public :
	NameTable (const Size_t = INITIAL_NAME_VECTOR_CAPACITY);
	NameTable (const NameTable&);
	virtual ~ NameTable();

	void init();
	void clear();
	const NameString_& get (const Value_) const;
	void operator = (const NameTable&);
	void copy (const NameTable*);

	template<class A1>
	Value_ add (const String<A1>&);
	Value_ add (const char* const);
	template<class A1>
	Value_ find (const String<A1>&) const;
	Value_ find (const char* const) const;
	template<class A1>
	Value_ fresh (const String<A1>&);
	Value_ fresh (const char* const);
	template<class A1>
	Value_ addPostfix (const String<A1>&, const char* const);
	template<class A1>
	Value_ addPostfix (const String<A1>&, const char);
	Value_ addPostfix (const Value_, const char* const);
	Value_ addPostfix (const Value_, const char);
	template<class A1>
	bool contains (const String<A1>&) const;
	bool contains (const char* const) const;

	bool addedNew() const;

	template<class A1>
	void showTable (String<A1>&) const;

	void dumpName (Value_) const;

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String<>&) const;

protected :
	NameMap_ nameMap_;
	NameVector_ nameVector_;

	typedef int FreshIndex_;
	NameString_ freshVariable_;
	FreshIndex_ freshCounter_;
	typedef
		typename map :: String<FreshIndex_, Allocator_>
		FreshIndexMap_;
	FreshIndexMap_ freshIndexMap_;
	NameVector_ freshNameVector_;
	bool addedNew_;
	enum {
		INITIAL_FRESH_NAME_VECTOR_CAPACITY = 32,
		INITIAL_FRESH_VARIABLE_CAPACITY = 64
	};
};

}

#endif /*NSTD_NAME_TABLE_HPP_*/
