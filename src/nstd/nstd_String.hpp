/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_String.hpp                                          */
/* Description:     nstd string class                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "nstd_manipulator.hpp"

namespace nstd {

template<class A>
class String : public container :: Vector<char, container :: storage :: ByValue, A> {
	typedef
		container :: Vector<char, container :: storage :: ByValue, A>
		Ancestor_;
public :
	typedef
		typename Ancestor_ :: Allocator_
		Allocator_;
	typedef
		typename Ancestor_ :: Index_
		Index_;
	typedef
		String& (*Manipulator_)(String&);

	String ();
	String (const Index_);
	template<class A1>
	String (const String<A1>&);
	String (const char*);
	String (const char* string, const char* terminalChar);
	String (const char*, const Index_);
	virtual ~ String();

	static Index_ getStringLength (const char*);
	static Index_ getStringLength (const char*, const char*);

	template<class T> T getIntegerValue() const;
	double getDoubleValue() const;
	bool isEqual (const char*) const;

	// c string interface
	char* c_str();
	const char* c_str() const;
	const char* getFirstChar() const;
	const char* getLastChar() const;
	const char* getTerminalChar() const;

	// assign operators
	void operator = (const char* const);
	void operator = (const String&);
	template<class A1>
	void operator = (const String<A1>&);
	template<class A1>
	void copy (const String<A1>&);

	// comparator operators
	template<class A1>
	bool operator == (const String<A1>&) const;
	template<class A1>
	bool operator != (const String<A1>&) const;
	bool operator == (const char* const) const;
	bool operator != (const char* const) const;

	void copyFrom (const char* const, const char* const = NULL);

	// operator << overload:
	template<class A1>
	String& operator << (const String<A1>&);
	String& operator << (Manipulator_);
	String& operator << (const char*);
	String& operator << (const std :: string&);
	String& operator << (const char);
	String& operator << (const void*);

	String& operator << (const U_int8_t value);
	String& operator << (const U_int16_t value);
	String& operator << (const U_int32_t value);
	String& operator << (const U_int64_t value);
	String& operator << (const Int8_t value);
	String& operator << (const Int16_t value);
	String& operator << (const Int32_t value);
	String& operator << (const Int64_t value);

	String& operator << (const Float value);
	String& operator << (const Double value);

	static Size_t getCount();
	static Size_t getMode();

	void dump() const;

	// nstd :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;

private :
	template<class A1>
	friend String<A1>&
	manipulator :: indent (String<A1>&);
	template<class A1>
	friend String<A1>&
	manipulator :: iterate (String<A1>&);
	template<class A1>
	friend String<A1>&
	manipulator :: mode (String<A1>&);

	bool doIndent() const;
	template<class A1>
	Index_ countNewLine (const String<A1>&) const;
	Index_ countNewLine (const char*) const;
	template<class A1>
	void appendWithCharIndent (const String<A1>&);
	template<class A1>
	void appendWithManipulatorIndent (const String<A1>&);
	void appendWithCharIndent (const char*, const Index_);
	void appendWithManipulatorIndent (const char*, const Index_);
	template<class A1>
	void appendWithString (const String<A1>&);

	static bool indentOn_;
	static bool iterateOn_;
	static bool modeOn_;
	static Manipulator_ indentM_;
	static char indentCh_;
	static Size_t count_;
	static Size_t mode_;
};

}


