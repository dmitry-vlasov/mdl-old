/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_auxiliary_Symbol.hpp                                  */
/* Description:     metamath symbol table class                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mm/types/mm_types.hpp"
#include "mm/auxiliary/mm_auxiliary.dpp"

namespace mm {
namespace auxiliary {

template<class T>
class Symbol :
	public nstd :: Object,
	public Scalar<Symbol<T> > {
private :
	typedef
		nstd :: NameTable<T, allocator :: Heap>
		NameTable_;
public :
	typedef
		typename NameTable_ :: NameString_
		String_;
	typedef
		typename NameTable_ :: Value_
		Value_;

	Symbol (const Size_t = NameTable_ :: INITIAL_SYMBOL_VECTOR_CAPACITY);
	virtual ~ Symbol();

	void addTriple (const String&, const String*, const String*);
	const String_* getAscii (const Value_) const;
	const String_* getUnicode (const Value_) const;
	const String_* getLatex (const Value_) const;

	// nstd :: Table interface
	const String_& get (const Value_) const;
	Value_ add (const String&);
	Value_ add (const char* const);
	Value_ find (const String&) const;
	Value_ find (const char* const) const;
	bool contains (const String&) const;
	bool contains (const char* const) const;

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (nstd :: String<>&) const;

private:
	typedef
		Vector
		<
			const String_*,
			storage :: ByValue,
			allocator :: Heap
		>
		Vector_;

	NameTable_ table_;
	Vector_ unicode_;
	Vector_ latex_;

	enum {
		INITIAL_SYMBOL_VECTOR_CAPACITY = 512
	};
};

}
}

#include "mm/auxiliary/mm_auxiliary_Symbol.ipp"


