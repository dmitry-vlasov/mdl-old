/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_auxiliary_Name.hpp                                    */
/* Description:     metamath identificator table class                       */
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
class Name :
	public nstd :: Object,
	public Scalar<Name<T> > {
private :
	typedef
		nstd :: NameTable<T, allocator :: Heap>
		NameTable_;
public :
	typedef
		typename NameTable_ :: NameString_
		NameString_;
	typedef
		typename NameTable_ :: Value_
		Value_;

	Name (const Size_t = NameTable_ :: INITIAL_NAME_VECTOR_CAPACITY);
	virtual ~ Name();

	const NameString_& getCorrectName (const Value_) const;
	bool isDefinition (const Value_) const;

	// nstd :: Table interface
	const NameString_& get (const Value_) const;
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
	NameTable_ table_;
	mutable NameString_ correctName_;

	enum {
		INITIAL_CORRECT_NAME_CAPACITY = 256
	};
};

}
}

#include "mm/auxiliary/mm_auxiliary_Name.ipp"


