/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_auxiliary_Name.ipp                                    */
/* Description:     metamath identificator table class                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mm {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	template<class T>
	inline
	Name<T> :: Name (const Size_t nameVectorCapacity) :
	table_ (nameVectorCapacity),
	correctName_ (INITIAL_CORRECT_NAME_CAPACITY) {
	}
	template<class T>
	Name<T> :: ~ Name() {
	}

	template<class T>
	inline const typename Name<T> :: NameString_&
	Name<T> :: getCorrectName (const Value_ ind) const
	{
		const NameString_&
			name = table_.get (ind);
		correctName_.clear();

		if ('0' <= name.getValue (0) && name.getValue (0) <= '9' ) {
			correctName_.add ('_');
		}
		if (name.getSize() >= 3 &&
			name.getValue (0) == 'd'&&
			name.getValue (1) == 'i' &&
			name.getValue (2) == 's' ) {
			correctName_.add ('_');
		}
		for (typename NameString_ :: Index_ i = 0; i < name.getSize(); i ++) {
			const char s = name.getValue (i);
			if (s == '.') {
				correctName_.add ('_');
			} else {
				correctName_.add (s);
			}
		}
		return correctName_;
	}
	template<class T>
	inline bool
	Name<T> :: isDefinition(const Value_ label) const
	{
		const NameString_&
			labelString = get (label);
		if (labelString.getSize() < 4) {
			return false;
		}
		return
			(labelString [0] == 'd') &&
			(labelString [1] == 'f') &&
			(labelString [2] == '-');
	}

	// nstd :: Name implementation
	template<class T>
	inline const typename Name<T> :: NameString_&
	Name<T> :: get (const Value_ value) const {
		return table_.get (value);
	}
	template<class T>
	inline typename Name<T> :: Value_
	Name<T> :: add (const String& string) {
		return table_.add (string);
	}
	template<class T>
	inline typename Name<T> :: Value_
	Name<T> :: add (const char* const string) {
		return table_.add (string);
	}
	template<class T>
	inline typename Name<T> :: Value_
	Name<T> :: find (const String& string) const {
		return table_.find (string);
	}
	template<class T>
	inline typename Name<T> :: Value_
	Name<T> :: find (const char* const string) const {
		return table_.find (string);
	}
	template<class T>
	inline bool
	Name<T> :: contains (const String& string) const {
		return table_.contains (string);
	}
	template<class T>
	inline bool
	Name<T> :: contains (const char* const string) const {
		return table_.contains (string);
	}

	// nstd :: Object implementation
	template<class T>
	void
	Name<T> :: commitSuicide() {
		delete this;
	}
	template<class T>
	Size_t
	Name<T> :: getVolume () const
	{
		Size_t result = 0;
		result += correctName_.getVolume();
		result += table_.getVolume();
		return result;
	}
	template<class T>
	Size_t
	Name<T> :: getSizeOf () const {
		return sizeof (Name);
	}
	template<class T>
	void
	Name<T> :: show (nstd :: String<>& string) const {
		table_.show (string);
	}
}
}


