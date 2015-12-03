/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_lexer_Buffer.hpp                                    */
/* Description:     lexer buffer for input                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_LEXER_BUFFER_HPP_
#define NSTD_LEXER_BUFFER_HPP_

namespace nstd {
namespace lexer {

template<int S = 32>
class Buffer : public Object {
public :
	enum {
		DEFAULT_SIZE = 32,  // kilobyte
		BUFFER_SIZE = size :: KILOBYTE * S
	};
	Buffer();
	~ Buffer();

	void operator ++ ();

	bool checkEnd (const char*, const Size_t = 1) const;
	void shiftBack (const char*&) const;
	void setInitial (const char*&) const;
	Size_t getIndex (const char*) const;
	Size_t getFileSize() const;

	bool open (const char* const);
	void close();

	template<class T>
	void show (T&) const;

	template<class T>
	void showHead (T&) const;
	template<class T>
	void showWhole (T&) const;
	template<class T>
	void showTail (T&) const;
	template<class T>
	void showLocal (T&, const Size_t) const;

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getSizeOf() const;
	virtual Size_t getVolume() const;
	virtual void show (String<>&) const;

private :
	enum {
		BUFFER_DELTA = 16,
		ARRAY_SIZE = BUFFER_SIZE * 2 + BUFFER_DELTA,
		LOCAL_CODE_SIZE = 4096
	};

	const char* fileName_;
	InputFileStream inputFileStream_;
	Size_t fileSize_;
	Size_t unreadSize_;
	Size_t lastReadSize_;

	void clear();
	void fill();
	void shift();

	const char array_[ARRAY_SIZE];
	const char* const buffer1_;
	const char* const buffer2_;
};

}
}

#endif /*NSTD_LEXER_BUFFER_HPP_*/
