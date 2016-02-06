/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_lexer_Source.hpp                                    */
/* Description:     input source                                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "lexer/nstd_lexer_Char.hpp"
#include "lexer/nstd_lexer_Location.hpp"
#include "lexer/nstd_lexer_Buffer.hpp"

namespace nstd {
namespace lexer {

template<int S = Buffer<> :: DEFAULT_SIZE>
class Source : public Object {
public :
	enum {
		BUFFER_SIZE = S,
		MINIMAL_RESERVE = 32
	};
	typedef
		Buffer<BUFFER_SIZE>
		Buffer_;
	typedef
		Location<Source>
		Location_;

	template<class A>
	Source (const String<A>&, const bool = false);
	virtual ~ Source();

	bool open (const char*);
	bool open();
	bool isTop() const;
	void close();
	bool isEmpty() const;
	const char* file() const;

	void operator ++ ();
	void reserve (const Size_t = MINIMAL_RESERVE);
	void setTop (const bool = true);

	void startToken();
	void stopToken();

	Char getChar() const;
	const char* getTokenStart() const;
	const char* getTokenStop() const;
	const Location_& getLocation() const;
	const Buffer_& getBuffer() const;
	Location_& location();

	template<class T>
	void show (T&) const;

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String<>&) const;

private :
	template<class>
	friend class Location;

	const char* fileName_;
	const bool isTop_;
	Location_ location_;
	mutable Buffer_ buffer_;

	const char* charStart_;
	const char* charStop_;
	Char charCurrent_;

	bool insideIndent_;
};

}
}


