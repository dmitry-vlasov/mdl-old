/*****************************************************************************/
/* Project name:    nstd - non-standard library                              */
/* File name:       nstd_lexer_Char.hpp                                      */
/* Description:     lexer char wrapper                                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef NSTD_LEXER_CHAR_HPP_
#define NSTD_LEXER_CHAR_HPP_

namespace nstd {
namespace lexer {

class Char {
public :
	Char ();
	Char (const char* const);
	Char (const Char&);

	char getValue (const Ptrdiff_t = 0) const;
	const char* getString() const;

	bool isAlphabet() const;
	bool isAlphaNumeric () const ;
	bool isWhitespace() const;
	bool isNumber() const;
	bool isEOF() const;
	bool isNewLine() const;

	void operator ++ ();
	void operator = (const Char&);
	bool operator == (const Char&) const;
	bool operator != (const Char&) const;
	bool operator == (const char) const;
	bool operator != (const char) const;

	// nstd :: Object interface
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	void show (String<>&) const;

private :
	template<int>
	friend class Source;
	const char* char_;
};

}
}

#endif /*NSTD_LEXER_CHAR_HPP_*/
