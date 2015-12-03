/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_NameTable.cpp                                       */
/* Description:     general class tables of identificators                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_NAME_TABLE_CPP_
#define NSTD_NAME_TABLE_CPP_

namespace nstd {

	/****************************
	 *		Public members
	 ****************************/

	template<class T, class A>
	inline
	NameTable<T, A> :: NameTable (const Size_t capacity) :
	nameMap_(),
	nameVector_ (capacity),
	freshVariable_ (INITIAL_FRESH_VARIABLE_CAPACITY),
	freshCounter_ (0),
	freshIndexMap_ (),
	freshNameVector_ (INITIAL_FRESH_NAME_VECTOR_CAPACITY),
	addedNew_ (true) {
	}
	template<class T, class A>
	NameTable<T, A> :: NameTable (const NameTable& nameTable) :
	nameMap_(),
	nameVector_ (nameTable.nameVector_),
	freshVariable_ (nameTable.freshVariable_),
	freshCounter_ (nameTable.freshCounter_),
	freshIndexMap_ (),
	freshNameVector_ (nameTable.freshNameVector_),
	addedNew_ (nameTable.addedNew_)
	{
		for (Index_ i = 0; i < nameTable.nameVector_.getSize(); ++ i) {
			const NameString_* nameString = nameTable.nameVector_.getValue (i);
			const Value_ value = nameTable.nameMap_.find (nameString);
			nameMap_.setAdd (nameString, value);
		}
		for (Index_ i = 0; i < nameTable.freshNameVector_.getSize(); ++ i) {
			const NameString_* nameString = nameTable.freshNameVector_.getValue (i);
			const FreshIndex_ freshIndex = nameTable.freshIndexMap_.find (nameString);
			freshIndexMap_.setAdd (nameString, freshIndex);
		}
	}
	template<class T, class A>
	NameTable<T, A> :: ~ NameTable() {
	}

	template<class T, class A>
	void
	NameTable<T, A> :: init() {
	}
	template<class T, class A>
	void
	NameTable<T, A> :: clear()
	{
		nameMap_.clear();
		for (Index_ i = 0;i < nameVector_.getSize(); ++ i) {
			const NameString_*& nameString = nameVector_.getReference (i);
			deleteObject (nameString);
			nameString = NULL;
		}
		nameVector_.clear();
		freshVariable_.clear();
		freshCounter_ = 0;
		freshIndexMap_.clear();
		for (Index_ i = 0;i < freshNameVector_.getSize(); ++ i) {
			const NameString_*& nameString = freshNameVector_.getReference (i);
			deleteObject (nameString);
			nameString = NULL;
		}
		freshNameVector_.clear();
		addedNew_ = true;
	}
	template<class T, class A>
	inline const typename NameTable<T, A> :: NameString_&
	NameTable<T, A> :: get (const Value_ value) const {
		return *nameVector_ [value];
	}
	template<class T, class A>
	void
	NameTable<T, A> :: operator = (const NameTable& nameTable){
		copy (&nameTable);
	}
	template<class T, class A>
	void
	NameTable<T, A> :: copy (const NameTable* nameTable)
	{
		nameVector_.erase();
		for (Index_ i = 0; i < nameTable->nameVector_.getSize(); ++ i) {
			const NameString_* nameString = nameTable->nameVector_.getValue (i);
			const NameString_* const name = new NameString_ (*nameString);
			nameVector_.add (name);
		}
		freshVariable_ = nameTable->freshVariable_;
		freshCounter_ = nameTable->freshCounter_;
		freshNameVector_.erase();
		for (Index_ i = 0; i < nameTable->freshNameVector_.getSize(); ++ i) {
			const NameString_* nameString = nameTable->nameVector_.getValue (i);
			const NameString_* const name = new NameString_ (*nameString);
			freshNameVector_.add (name);
		}
		freshNameVector_ = nameTable->freshNameVector_;
		addedNew_  = nameTable->addedNew_;
		nameMap_.erase();
		freshIndexMap_.erase();
		for (Index_ i = 0; i < nameTable->nameVector_.getSize(); ++ i) {
			const NameString_* nameString = nameTable->nameVector_.getValue (i);
			const Value_ value = nameTable->nameMap_.find (nameString);
			nameMap_.setAdd (nameString, value);
		}
		for (Index_ i = 0; i < nameTable->freshNameVector_.getSize(); ++ i) {
			const NameString_* nameString = nameTable->freshNameVector_.getValue (i);
			const FreshIndex_ freshIndex = nameTable->freshIndexMap_.find (nameString);
			freshIndexMap_.setAdd (nameString, freshIndex);
		}
	}

	template<class T, class A>
	template<class A1>
	inline typename NameTable<T, A> :: Value_
	NameTable<T, A> :: add (const String<A1>& token)
	{
		const Size_t size = nameVector_.getSize();
		const Value_ result = nameMap_.addFind (token, size);
		addedNew_ = (result == size);

		if (addedNew_) {
			const NameString_* const
				name = new NameString_ (token);
			nameVector_.add (name);
		}
		return result;
	}
	template<class T, class A>
	inline typename NameTable<T, A> :: Value_
	NameTable<T, A> :: add (const char* const token)
	{
		const Size_t size = nameVector_.getSize();
		const Value_ result = nameMap_.addFind (token, size);

		if (result == size) {
			const NameString_* const
				name = new NameString_ (token);
			nameVector_.add (name);
		}
		return result;
	}
	template<class T, class A>
	template<class A1>
	inline typename NameTable<T, A> :: Value_
	NameTable<T, A> :: find (const String<A1>& token) const {
		return nameMap_.find (token);
	}
	template<class T, class A>
	inline typename NameTable<T, A> :: Value_
	NameTable<T, A> :: find (const char* const token) const {
		return nameMap_.find (token);
	}
	template<class T, class A>
	template<class A1>
	inline typename NameTable<T, A> :: Value_
	NameTable<T, A> :: fresh (const String<A1>& token)
	{
		freshCounter_ = freshIndexMap_.addFind (token, 0);
		while (true) {
			freshVariable_.clear();
			freshVariable_ << token << manipulator :: underline << freshCounter_;
			if (find (freshVariable_) == Undefined<Value_> :: getValue()) {
				freshIndexMap_.setAdd (token, freshCounter_ + 1);
				return add (freshVariable_);
			}
			++ freshCounter_;
		}
	}
	template<class T, class A>
	inline typename NameTable<T, A> :: Value_
	NameTable<T, A> :: fresh (const char* const token)
	{
		freshCounter_ = freshIndexMap_.addFind (token, 0);
		while (true) {
			freshVariable_.clear();
			freshVariable_ << token << manipulator :: underline << freshCounter_;
			if (find (freshVariable_) == Undefined<Value_> :: getValue()) {
				freshIndexMap_.setAdd (token, freshCounter_ + 1);
				return add (freshVariable_);
			}
			++ freshCounter_;
		}
	}
	template<class T, class A>
	template<class A1>
	inline typename NameTable<T, A> :: Value_
	NameTable<T, A> :: addPostfix (const String<A1>& token, const char* const postfix)
	{
		freshVariable_.clear();
		freshVariable_ << token << postfix;
		return add (freshVariable_);
		/*if (find (freshVariable_) == Undefined<Value_> :: getValue()) {
			return add (freshVariable_);
		} else {
			return Undefined<Value_> :: getValue();
		}*/
	}
	template<class T, class A>
	template<class A1>
	inline typename NameTable<T, A> :: Value_
	NameTable<T, A> :: addPostfix (const String<A1>& token, const char postfix)
	{
		freshVariable_.clear();
		freshVariable_ << token << postfix;
		return add (freshVariable_);
		/*if (find (freshVariable_) == Undefined<Value_> :: getValue()) {
			return add (freshVariable_);
		} else {
			return Undefined<Value_> :: getValue();
		}*/
	}
	template<class T, class A>
	inline typename NameTable<T, A> :: Value_
	NameTable<T, A> :: addPostfix (const Value_ value, const char* const postfix)
	{
		const NameString_* token = nameVector_.getValue (value);
		return addPostfix (*token, postfix);
	}
	template<class T, class A>
	inline typename NameTable<T, A> :: Value_
	NameTable<T, A> :: addPostfix (const Value_ value, const char postfix)
	{
		const NameString_* token = nameVector_.getValue (value);
		return addPostfix (*token, postfix);
	}
	template<class T, class A>
	template<class A1>
	inline bool
	NameTable<T, A> :: contains (const String<A1>& token) const {
		return (nameMap_.find (token) != Undefined<Value_> :: getValue());
	}
	template<class T, class A>
	inline bool
	NameTable<T, A> :: contains (const char* const token) const {
		return (nameMap_.find (token) != Undefined<Value_> :: getValue());
	}

	template<class T, class A>
	inline bool
	NameTable<T, A> :: addedNew() const {
		return addedNew_;
	}

	template<class T, class A>
	template<class A1>
	inline void
	NameTable<T, A> :: showTable (String<A1>& string) const  {
		nameMap_.template show<String<A1> > (string);
	}

	template<class T, class A>
	void
	NameTable<T, A> :: dumpName (Value_ value) const
	{
		const NameString_& name = get (value);
		name.dump();
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// nstd :: Object implementation
	template<class T, class A>
	void
	NameTable<T, A> :: commitSuicide() {
		delete this;
	}
	template<class T, class A>
	Size_t
	NameTable<T, A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += nameMap_.getVolume();
		volume += nameVector_.getVolume();
		volume += freshVariable_.getVolume();
		volume += freshIndexMap_.getVolume();
		volume += freshNameVector_.getVolume();
		return volume;
	}
	template<class T, class A>
	Size_t
	NameTable<T, A> :: getSizeOf() const {
		return sizeof (NameTable);
	}
	template<class T, class A>
	void
	NameTable<T, A> :: show (String<>& string) const {
		string << "volume = " << space << tab << getVolume() << space;
	}
}

#endif /*NSTD_NAME_TABLE_CPP_*/
