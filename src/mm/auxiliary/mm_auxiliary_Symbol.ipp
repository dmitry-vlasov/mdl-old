/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_auxiliary_Symbol.ipp                                  */
/* Description:     metamath symbol table class                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AUXILIARY_SYMBOL_IPP_
#define MM_AUXILIARY_SYMBOL_IPP_

namespace mm {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	template<class T>
	inline
	Symbol<T> :: Symbol (const Size_t nameVectorCapacity) :
	table_ (nameVectorCapacity),
	unicode_ (nameVectorCapacity),
	latex_ (nameVectorCapacity) {
	}
	template<class T>
	Symbol<T> :: ~ Symbol() {
	}

using manipulator :: endLine;

	template<class T>
	inline void
	Symbol<T> :: addTriple
	(
		const String& ascii,
		const String* unicode,
		const String* latex
	)
	{
		table_.add (ascii);
		if (!table_.addedNew()) {
			Error* error = new Error (Error :: SEMANTIC);
			error->message() << "symbol " << ascii << " is already declared." << endLine;
			throw error;
		}
		unicode_.add (unicode);
		latex_.add (latex);
	}
	template<class T>
	inline const typename Symbol<T> :: String_*
	Symbol<T> :: getAscii (const Value_ ind) const {
		return &(table_.get (ind));
	}
	template<class T>
	inline const typename Symbol<T> :: String_*
	Symbol<T> :: getUnicode (const Value_ ind) const {
		return unicode_.getValue (ind);
	}
	template<class T>
	inline const typename Symbol<T> :: String_*
	Symbol<T> :: getLatex (const Value_ ind) const {
		return latex_.getValue (ind);
	}

	// nstd :: Symbol implementation
	template<class T>
	inline const typename Symbol<T> :: String_&
	Symbol<T> :: get (const Value_ value) const {
		return table_.get (value);
	}
	template<class T>
	inline typename Symbol<T> :: Value_
	Symbol<T> :: add (const String& string)
	{
		const Value_ result = table_.add (string);
		if (table_.addedNew()) {
			unicode_.add (NULL);
			latex_.add (NULL);
		}
		return result;
	}
	template<class T>
	inline typename Symbol<T> :: Value_
	Symbol<T> :: add (const char* const string)
	{
		const Value_ result = table_.add (string);
		if (table_.addedNew()) {
			unicode_.add (NULL);
			latex_.add (NULL);
		}
		return result;
	}
	template<class T>
	inline typename Symbol<T> :: Value_
	Symbol<T> :: find (const String& string) const {
		return table_.find (string);
	}
	template<class T>
	inline typename Symbol<T> :: Value_
	Symbol<T> :: find (const char* const string) const {
		return table_.find (string);
	}
	template<class T>
	inline bool
	Symbol<T> :: contains (const String& string) const {
		return table_.contains (string);
	}
	template<class T>
	inline bool
	Symbol<T> :: contains (const char* const string) const {
		return table_.contains (string);
	}

	// nstd :: Object implementation
	template<class T>
	void
	Symbol<T> :: commitSuicide() {
		delete this;
	}
	template<class T>
	Size_t
	Symbol<T> :: getVolume () const
	{
		Size_t result = 0;
		result += table_.getVolume();
		result += unicode_.getVolume();
		result += latex_.getVolume();
		return result;
	}
	template<class T>
	Size_t
	Symbol<T> :: getSizeOf () const {
		return sizeof (Symbol);
	}
	template<class T>
	void
	Symbol<T> :: show (nstd :: String<>& string) const {
		table_.show (string);
	}
}
}

#endif /*MM_AUXILIARY_SYMBOL_IPP_*/
