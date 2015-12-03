/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_lexer_Buffer.cpp                                    */
/* Description:     lexer buffer for input                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_LEXER_BUFFER_CPP_
#define NSTD_LEXER_BUFFER_CPP_

namespace nstd {
namespace lexer {

	/****************************
	 *		Public members
	 ****************************/

	template<int S>
	Buffer<S> :: Buffer () :
	fileName_ (""),
	inputFileStream_ (),

	fileSize_ (0),
	unreadSize_ (0),
	lastReadSize_ (0),

	array_ (),
	buffer1_ (array_),
	buffer2_ (array_ + BUFFER_SIZE) {
		clear();
	}
	template<int S>
	Buffer<S> :: ~ Buffer () {
	}

	template<int S>
	inline void
	Buffer<S> :: operator ++ ()
	{
		shift();
		fill();
	}

	template<int S>
	inline bool
	Buffer<S> :: checkEnd  (const char* ch, const Size_t dist) const {
		return  (dist + (ch - buffer2_) >= BUFFER_SIZE);
	}
	template<int S>
	inline void
	Buffer<S> :: shiftBack (const char*& ch) const {
		ch -= BUFFER_SIZE;
	}
	template<int S>
	inline void
	Buffer<S> :: setInitial (const char*& ch) const {
		ch = buffer2_;
	}
	template<int S>
	inline Size_t
	Buffer<S> :: getIndex (const char* ch) const {
		return ch - buffer2_;
	}
	template<int S>
	inline Size_t
	Buffer<S> :: getFileSize() const {
		return fileSize_;
	}

	template<int S>
	bool
	Buffer<S> :: open (const char* const fileName)
	{
		fileName_ = fileName;
		fileSize_ = system :: getFileSize (fileName);
		if (fileSize_ == Undefined<Size_t> :: getValue()) {
			return false;
		}
		unreadSize_ = fileSize_;
		lastReadSize_ = 0;
		inputFileStream_.open (fileName_, std :: ios :: binary);
		fill();
		return true;
	}
	template<int S>
	void
	Buffer<S> :: close()
	{
		clear();
		unreadSize_ = fileSize_;
		lastReadSize_ = 0;
		inputFileStream_.close();
	}


using manipulator :: endLine;

	template<int S>
	template<class T>
	void
	Buffer<S> :: show (T& string) const
	{
		string << "code:" << endLine;
		showLocal (string);
	}
	template<int S>
	template<class T>
	void
	Buffer<S> :: showHead (T& string) const
	{
		int shift = - (LOCAL_CODE_SIZE / 2);
		while (buffer2_ [shift] == chars :: NULL_CHAR) {
			++ shift;
		}

		char localCode [LOCAL_CODE_SIZE];
		bool empty = true;
		for (Size_t i = 0; i < LOCAL_CODE_SIZE; i++) {
			const char ch = buffer2_ [i + shift];
			localCode [i] = ch;
			if (ch != chars :: NULL_CHAR) {
				empty = false;
			}
		}
		if (!empty) {
			string << "local buffer:" << endLine;
			string << "--------------------------------------------------------------" << endLine;
			string << localCode << endLine;
			string << "--------------------------------------------------------------" << endLine;
		}
	}
	template<int S>
	template<class T>
	void
	Buffer<S> :: showWhole (T& string) const
	{
		string << "whole buffer:" << endLine;
		string << "--------------------------------------------------------------" << endLine;
		for (Size_t i = 0; i < ARRAY_SIZE; i++) {
			const char ch = array_ [i];
			switch (ch) {
			case chars :: NULL_CHAR :
				string << "\\0";
				break;
			default :
				string << ch;
			}
		}
		string << endLine;
		string << "--------------------------------------------------------------" << endLine;
	}
	template<int S>
	template<class T>
	void
	Buffer<S> :: showTail (T& string) const
	{
		string << "buffer tail:" << endLine;
		string << "string end: " << (int)array_ + BUFFER_SIZE + lastReadSize_ << endLine;
		string << "----------------------------" << endLine;
		for (int i = - LOCAL_CODE_SIZE / 2; i < LOCAL_CODE_SIZE /2; ++ i) {
			const Size_t index = BUFFER_SIZE + lastReadSize_ + i;
			if (!(index < ARRAY_SIZE)) {
				break;
			}
			const char ch = array_ [index];
			if (ch != chars :: NULL_CHAR) {
				string << ch;
			} else {
				string << "\\0";
			}
		}
		string << "----------------------------" << endLine;
	}
	template<int S>
	template<class T>
	void
	Buffer<S> :: showLocal (T& string, const Size_t locality) const
	{
		string << "local buffer:" << endLine;
		string << "----------------------------" << endLine;
		for (int i = - LOCAL_CODE_SIZE / 2; i < LOCAL_CODE_SIZE /2; ++ i) {
			const Size_t index = BUFFER_SIZE + locality + i;
			if (!(index < ARRAY_SIZE)) {
				break;
			}
			const char ch = array_ [index];
			if (ch != chars :: NULL_CHAR) {
				string << ch;
			} else {
				string << "\\0";
			}
		}
		string << "----------------------------" << endLine;
	}

using manipulator :: endLine;

	// nstd :: Object interface
	template<int S>
	void
	Buffer<S> :: commitSuicide() {
		delete this;
	}
	template<int S>
	Size_t
	Buffer<S> :: getSizeOf() const {
		return sizeof (Buffer);
	}
	template<int S>
	Size_t
	Buffer<S> :: getVolume() const {
		return 0;
	}
	template<int S>
	void
	Buffer<S> :: show (String<>& string) const {
		showWhole (string);
	}

	/****************************
	 *		Private members
	 ****************************/

	template<int S>
	void
	Buffer<S> :: shift ()
	{
		for (Size_t i = 0; i < BUFFER_SIZE; i ++) {
			const_cast<char*>(buffer1_)[i] = array_ [i + BUFFER_SIZE];
		}
		for (Size_t i = 0; i < BUFFER_SIZE + BUFFER_DELTA; i ++) {
			const_cast<char*>(buffer2_)[i] = chars :: NULL_CHAR;
		}
	}
	template<int S>
	void
	Buffer<S> :: clear ()
	{
		for (Size_t i = 0; i < ARRAY_SIZE; i++) {
			const_cast<char*>(array_) [i] = chars :: NULL_CHAR;
		}
	}
	template<int S>
	void
	Buffer<S> :: fill ()
	{
		lastReadSize_ =
			(unreadSize_ < BUFFER_SIZE) ?
			unreadSize_ :
			BUFFER_SIZE;
		char*
			buffer = const_cast<char*> (buffer2_);

		inputFileStream_.read (buffer, lastReadSize_);
		unreadSize_ -= lastReadSize_;
	}
}
}

#endif /*NSTD_LEXER_BUFFER_CPP_*/
