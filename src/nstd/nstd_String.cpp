/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_String.cpp                                          */
/* Description:     nstd string class                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include <sstream>

namespace nstd {

	/****************************
	 *		Public members
	 ****************************/
	
	template<class A>
	inline
	String<A> :: String() :
	Ancestor_() {
	}
	template<class A>
	inline
	String<A> :: String (const Index_ initialCapacity) :
	Ancestor_ (initialCapacity) {
	}
	template<class A>
	template<class A1>
	inline 
	String<A> :: String (const String<A1>& string) :
	Ancestor_ (string) {
	}
	template<class A>
	inline
	String<A> :: String (const char* string) :
	Ancestor_ (string, getStringLength (string)) {
	}
	template<class A>
	inline
	String<A> :: String (const char* string, const char* terminalChar) :
	Ancestor_ (string, getStringLength (string, terminalChar)) {
	}
	template<class A>
	inline
	String<A> :: String (const char* string, const Index_ size) :
	Ancestor_ (string, size) {
	}
	template<class A>
	inline
	String<A> :: ~ String() {
	}

	template<class A>
	typename String<A> :: Index_
	String<A> :: getStringLength (const char* const string)
	{
		if (string == NULL) {
			return 0;
		}
		const char* s = string;
		Index_ result = 0;
		while (*s ++ != chars :: NULL_CHAR) {
			result ++ ;
		}
		return result;
	}
	template<class A>
	inline typename String<A> :: Index_
	String<A> :: getStringLength
	(
		const char* const initialChar,
		const char* const terminalChar
	) {
		return static_cast<const Index_>(terminalChar - initialChar);
	}
	
	template<class A>
	template<class T> T
	String<A> :: getIntegerValue () const
	{
		T result = 0;
		T factor = 1;
		Index_ size = Ancestor_ :: getSize() - 1;
		for (Index_ i = 0; i <= size; i ++) {
			const char ch = Ancestor_ :: getValue (size - i);
			if (('0' <= ch) && (ch <= '9')) {
				result += (ch - '0') * factor;
			} else if (ch == chars :: NULL_CHAR) {
				break;
			} else {
				return Undefined<T> :: getValue();
			}
			factor *= 10;
		}
		return result;
	}
	template<class A>
	double
	String<A> :: getDoubleValue () const
	{
		double result = 0;
		std :: istringstream i (c_str());
		if (!(i >> result)) {
			return 0;
		} else {
			return result;
		}
	}
	template<class A>
	inline bool
	String<A> :: isEqual (const char* string) const {
		return Ancestor_ :: isEqual (string, getStringLength (string));
	}

	/******************************************
	 *		c string interface implementation
	 ******************************************/

	template<class A>
	inline char*
	String<A> :: c_str() {
		return &(Ancestor_ :: data_->getReference());
	}
	template<class A>
	inline const char* 
	String<A> :: c_str() const {
		return &(Ancestor_ :: data_->getReference());
	}
	template<class A>
	inline const char*
	String<A> :: getFirstChar() const {
		return c_str();
	}
	template<class A>
	inline const char*
	String<A> :: getLastChar() const {
		return c_str() + Ancestor_ :: getSize() - 1;
	}
	template<class A>
	inline const char*
	String<A> :: getTerminalChar() const {
		return c_str() + Ancestor_ :: getSize();
	}

	/******************************************
	 *		assign operators implementation
	 ******************************************/

	template<class A>
	inline void
	String<A> :: operator = (const char* const string) {
		Ancestor_ :: clear();
		operator << (string);
	}
	template<class A>
	inline void
	String<A> :: operator = (const String& string) {
		Ancestor_ :: operator = (string);
	}
	template<class A>
	template<class A1>
	inline void
	String<A> :: operator = (const String<A1>& string) {
		Ancestor_ :: clear();
		operator << (string);
	}
	template<class A>
	template<class A1>
	inline void
	String<A> :: copy (const String<A1>& string)
	{
		Ancestor_ :: clear();
		appendWithString (string);
	}

	/***********************************************
	 *		comparator operators implementation
	 ***********************************************/

	template<class A>
	template<class A1>
	inline bool
	String<A> :: operator == (const String<A1>& string) const {
		return Ancestor_ :: operator == (string);
	}
	template<class A>
	template<class A1>
	inline bool
	String<A> :: operator != (const String<A1>& string) const {
		return Ancestor_ :: operator != (string);
	}
	template<class A>
	inline bool
	String<A> :: operator == (const char* const string) const {
		return Ancestor_ :: isEqual (string, getStringLength (string));
	}
	template<class A>
	inline bool
	String<A> :: operator != (const char* const string) const {
		return !operator == (string);
	}
	template<class A>
	inline void
	String<A> :: copyFrom (const char* const beg, const char* const end) 
	{
		Ancestor_ :: clear();
		const Index_ length =
			(end == NULL) ?
			getStringLength (beg) :
			getStringLength (beg, end);
		Ancestor_ :: append (beg, length);
	}

	/************************************************
	 *		operator << overload implementation
	 ************************************************/

	template<class A>
	template<class A1>
	String<A>&
	String<A> :: operator << (const String<A1>& string)
	{
		appendWithString (string);
		return *this;
	}
	template<class A>
	String<A>&
	String<A> :: operator << (Manipulator_ manip)
	{
		String& string = *this;
		if (indentOn_) {
			indentM_ = manip;
			indentOn_ = false;
		} else {
			for (Size_t i = 0; i < count_; ++ i) {
				manip (string);
			}
			count_ = 1;
		}
		return string;
	}
	template<class A>
	String<A>&
	String<A> :: operator << (const char* string)
	{
		const Index_ length = getStringLength (string);
		if (indentCh_ != chars :: NULL_CHAR) {
			for (Size_t i = 0; i < count_; ++ i) {
				appendWithCharIndent (string, length);
			}
			indentCh_ = chars :: NULL_CHAR;
			count_ = 1;
			return *this;
		}
		if (indentM_ != NULL) {
			for (Size_t i = 0; i < count_; ++ i) {
				appendWithManipulatorIndent (string, length);
			}
			indentM_ = NULL;
			count_ = 1;
			return *this;
		}
		for (Size_t i = 0; i < count_; ++ i) {
			Ancestor_ :: append (string, length);
		}
		count_ = 1;
		return *this;
	}
	template<class A>
	String<A>&
	String<A> :: operator << (const std :: string& str) {
		return operator << (str.c_str());
	}
	template<class A>
	String<A>&
	String<A> :: operator << (const char ch)
	{
		if (!indentOn_ && !iterateOn_ && !modeOn_) {
			for (Size_t i = 0; i < count_; ++ i) {
				Ancestor_ :: add (ch);
			}
			count_ = 1;
		} else if (indentOn_) {
			indentCh_ = ch;
			indentOn_ = false;
		} else if (modeOn_) {
			mode_ = ch;
			modeOn_ = false;
		} else if (iterateOn_) {
			count_ = ch;
			iterateOn_ = false;
		}
		return *this;
	}
	template<class A>
	String<A>&
	String<A> :: operator << (const void* pointer)
	{
		std :: ostringstream oss;
		oss << pointer;
		return operator << (oss.str());
	}

	template<class A>
	String<A>&
	String<A> :: operator << (const U_int8_t value)
	{
		if (!iterateOn_ && !modeOn_) {
			std :: ostringstream oss;
			oss << value;
			operator << (oss.str());
		} else if (modeOn_) {
			mode_ = value;
			modeOn_ = false;
		} else if (iterateOn_) {
			count_ = value;
			iterateOn_ = false;
		}
		return *this;
	}
	template<class A>
	String<A>&
	String<A> :: operator << (const U_int16_t value)
	{
		if (!iterateOn_ && !modeOn_) {
			std :: ostringstream oss;
			oss << value;
			operator << (oss.str());
		} else if (modeOn_) {
			mode_ = value;
			modeOn_ = false;
		} else if (iterateOn_) {
			count_ = value;
			iterateOn_ = false;
		}
		return *this;
	}
	template<class A>
	String<A>&
	String<A> :: operator << (const U_int32_t value)
	{
		if (!iterateOn_ && !modeOn_) {
			std :: ostringstream oss;
			oss << value;
			operator << (oss.str());
		} else if (modeOn_) {
			mode_ = value;
			modeOn_ = false;
		} else if (iterateOn_) {
			count_ = value;
			iterateOn_ = false;
		}
		return *this;
	}
	template<class A>
	String<A>&
	String<A> :: operator << (const U_int64_t value)
	{
		if (!iterateOn_ && !modeOn_) {
			std :: ostringstream oss;
			oss << value;
			operator << (oss.str());
		} else if (modeOn_) {
			mode_ = value;
			modeOn_ = false;
		} else if (iterateOn_) {
			count_ = value;
			iterateOn_ = false;
		}
		return *this;
	}
	template<class A>
	String<A>&
	String<A> :: operator << (const Int8_t value)
	{
		if (!iterateOn_ && !modeOn_) {
			std :: ostringstream oss;
			oss << value;
			operator << (oss.str());
		} else if (modeOn_) {
			mode_ = value;
			modeOn_ = false;
		} else if (iterateOn_) {
			count_ = value;
			iterateOn_ = false;
		}
		return *this;
	}
	template<class A>
	String<A>&
	String<A> :: operator << (const Int16_t value)
	{
		if (!iterateOn_ && !modeOn_) {
			std :: ostringstream oss;
			oss << value;
			operator << (oss.str());
		} else if (modeOn_) {
			mode_ = value;
			modeOn_ = false;
		} else if (iterateOn_) {
			count_ = value;
			iterateOn_ = false;
		}
		return *this;
	}
	template<class A>
	String<A>&
	String<A> :: operator << (const Int32_t value)
	{
		if (!iterateOn_ && !modeOn_) {
			std :: ostringstream oss;
			oss << value;
			operator << (oss.str());
		} else if (modeOn_) {
			mode_ = value;
			modeOn_ = false;
		} else if (iterateOn_) {
			count_ = value;
			iterateOn_ = false;
		}
		return *this;
	}
	template<class A>
	String<A>&
	String<A> :: operator << (const Int64_t value)
	{
		if (!iterateOn_ && !modeOn_) {
			std :: ostringstream oss;
			oss << value;
			operator << (oss.str());
		} else if (modeOn_) {
			mode_ = value;
			modeOn_ = false;
		} else if (iterateOn_) {
			count_ = value;
			iterateOn_ = false;
		}
		return *this;
	}

	template<class A>
	String<A>&
	String<A> :: operator << (const Float value)
	{
		std :: ostringstream oss;
		oss << value;
		return operator << (oss.str());
	}

	template<class A>
	String<A>&
	String<A> :: operator << (const Double value)
	{
		std :: ostringstream oss;
		oss << value;
		return operator << (oss.str());
	}

	template<class A>
	inline Size_t
	String<A> :: getCount() {
		return count_;
	}
	template<class A>
	inline Size_t
	String<A> :: getMode() {
		return mode_;
	}

	template<class A>
	void
	String<A> :: dump() const {
		std :: cout << std :: endl << c_str() << std :: endl;
	}

	// nstd :: Object implementation
	template<class A>
	inline void
	String<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	inline Size_t
	String<A> :: getVolume() const {
		return Ancestor_ :: getVolume();
	}
	template<class A>
	inline Size_t
	String<A> :: getSizeOf() const {
		return sizeof (String);
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	bool
	String<A> :: doIndent() const
	{
		return
			(indentCh_ != chars :: NULL_CHAR) ||
			(indentM_ != NULL);
	}
	template<class A>
	template<class A1>
	typename String<A> :: Index_
	String<A> :: countNewLine (const String<A1>& string) const
	{
		Index_ count = 0;
		for (Index_ i = 0; i < string.getSize(); ++ i) {
			const char ch = string [i];
			if (ch == chars :: NEW_LINE) {
				++ count;
			}
		}
		return count;
	}
	template<class A>
	typename String<A> :: Index_
	String<A> :: countNewLine (const char* string) const
	{
		Index_ count = 0;
		const char* s = string;
		while (*s ++ != chars :: NULL_CHAR) {
			const char ch = *s;
			if (ch == chars :: NEW_LINE) {
				++ count;
			}
		}
		return count;
	}
	template<class A>
	template<class A1>
	void
	String<A> :: appendWithCharIndent (const String<A1>& string)
	{
		const Index_ newLineCount = countNewLine (string);
		const Index_ newSize = Ancestor_ :: size_ + string.getSize() + newLineCount;
		if (Ancestor_ :: ensureCapacityNotLess (newSize + 1)) {
			Ancestor_ :: undefineTail();
		}
		for (Size_t j = 0; j < string.getSize(); j ++) {
			const char ch = (string.getData() + j)->getValue();
			Ancestor_ :: add (ch);
			if (ch == chars :: NEW_LINE) {
				Ancestor_ :: add (indentCh_);
			}
		}
	}
	template<class A>
	template<class A1>
	void
	String<A> :: appendWithManipulatorIndent (const String<A1>& string)
	{
		const Index_ newLineCount = countNewLine (string);
		const Index_ newSize = Ancestor_ :: size_ + string.getSize() + newLineCount;
		if (Ancestor_ :: ensureCapacityNotLess (newSize + 1)) {
			Ancestor_ :: undefineTail();
		}
		for (Size_t j = 0; j < string.getSize(); j ++) {
			const char ch = (string.getData() + j)->getValue();
			Ancestor_ :: add (ch);
			if (ch == chars :: NEW_LINE) {
				indentM_ (*this);
			}
		}
	}
	template<class A>
	void
	String<A> :: appendWithCharIndent (const char* string, const Index_ length)
	{
		const Index_ newLineCount = countNewLine (string);
		const Index_ newSize = Ancestor_ :: size_ + length + newLineCount;
		if (Ancestor_ :: ensureCapacityNotLess (newSize + 1)) {
			Ancestor_ :: undefineTail();
		}
		for (Size_t j = 0; j < length; j ++) {
			const char ch = string [j];
			Ancestor_ :: add (ch);
			if (ch == chars :: NEW_LINE) {
				Ancestor_ :: add (indentCh_);
			}
		}
	}
	template<class A>
	void
	String<A> :: appendWithManipulatorIndent (const char* string, const Index_ length)
	{
		const Index_ newLineCount = countNewLine (string);
		const Index_ newSize = Ancestor_ :: size_ + length + newLineCount;
		if (Ancestor_ :: ensureCapacityNotLess (newSize + 1)) {
			Ancestor_ :: undefineTail();
		}
		for (Size_t j = 0; j < length; j ++) {
			const char ch = string [j];
			Ancestor_ :: add (ch);
			if (ch == chars :: NEW_LINE) {
				indentM_ (*this);
			}
		}
	}
	template<class A>
	template<class A1>
	void
	String<A> :: appendWithString (const String<A1>& string)
	{
		if (indentCh_ != chars :: NULL_CHAR) {
			for (Size_t i = 0; i < count_; ++ i) {
				appendWithCharIndent (string);
			}
			indentCh_ = chars :: NULL_CHAR;
			count_ = 1;
			return;
		}
		if (indentM_ != NULL) {
			for (Size_t i = 0; i < count_; ++ i) {
				appendWithManipulatorIndent (string);
			}
			indentM_ = NULL;
			count_ = 1;
			return;
		}
		for (Size_t i = 0; i < count_; ++ i) {
			Ancestor_ :: append (string);
		}
		count_ = 1;
	}

	/************************************
	 *		Static private attributes
	 ************************************/

	template<class A>
	bool String<A> :: indentOn_ = false;

	template<class A>
	bool String<A> :: iterateOn_ = false;

	template<class A>
	bool String<A> :: modeOn_ = false;

	template<class A>
	typename String<A> :: Manipulator_
	String<A> :: indentM_ = NULL;

	template<class A>
	char String<A> :: indentCh_ = chars :: NULL_CHAR;

	template<class A>
	Size_t String<A> :: count_ = 1;

	template<class A>
	Size_t String<A> :: mode_ = 0;
}


