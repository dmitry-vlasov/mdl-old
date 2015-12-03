/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_lexer_Lexer.hpp                                       */
/* Description:     metamath lexer class                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_LEXER_LEXER_HPP_
#define MM_LEXER_LEXER_HPP_

#include "lexer/mm_lexer_Scaner.hpp"

namespace mm {
namespace lexer {

class Lexer :
	public nstd :: Object,
	public Scalar<Lexer> {
public :
	typedef
		Scaner :: Comments_
		Comments_;

	Lexer ();
	Lexer (const String&);
	virtual ~ Lexer();

	void open();
	void open (const String&);
	void close();

	Token :: Type scan();

	template<Token :: Type type>
	Token :: Type scan ();

	template
	<
		Token :: Type type_1,
		Token :: Type type_2
	>
	Token :: Type scan ();

	Comments_& comments();
	void scanComments();

	Token :: Type getTokenType() const;
	const String& getToken() const;
	const Location& getLocation() const;

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (nstd :: String<>&) const;

private :
	const String& guessToken();

	Source source_;
	Scaner scaner_;
	Token :: Type tokenType_;
	mutable String token_;
	enum {
		INITIAL_TOKEN_CAPACITY = nstd :: size :: KILOBYTE
	};
};

}
}

#include "lexer/mm_lexer_Lexer.ipp"

#endif /*MM_LEXER_LEXER_HPP_*/
