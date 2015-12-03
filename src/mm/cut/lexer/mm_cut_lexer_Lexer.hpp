/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_cut_lexer_Lexer.hpp                                   */
/* Description:     mm source file cutting lexer                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_CUT_LEXER_LEXER_HPP_
#define MM_CUT_LEXER_LEXER_HPP_

#include "mm/cut/auxiliary/mm_cut_auxiliary.hpp"
#include "mm/cut/lexer/mm_cut_lexer_Token.hpp"
#include "mm/cut/lexer/mm_cut_lexer_WhitespaceScaner.hpp"

namespace mm {
namespace cut {
namespace lexer {

class Lexer :
	public nstd :: Object,
	public Scalar<Lexer> {
public :
	Lexer ();
	Lexer (const String&);
	virtual ~ Lexer();

	void open();
	void close();

	template
	<
		Token :: Type type
	>
	Token :: Type scan();

	template
	<
		Token :: Type type_1,
		Token :: Type type_2
	>
	Token :: Type scan();

	Token :: Type getTokenType() const;
	const String& getToken() const;
	const String& guessToken (const bool = false, const int = 0);
	const Location& getLocation() const;
	const Source& getSource() const;

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (nstd :: String<>&) const;

private :

	template<Token :: Type type>
	Token :: Type scanToken();
	template
	<
		Token :: Type type_1,
		Token :: Type type_2
	>
	Token :: Type scanToken();

	bool divisorBegins() const;
	bool eofAtStart();
	Token :: Type consume (const Token&, const short pos = 0);
	Token :: Type finalize (const Token :: Type);

	Source source_;
	WhitespaceScaner whitespaceScaner_;
	Token :: Type tokenType_;
	mutable String token_;
	enum {
		INITIAL_TOKEN_CAPACITY = nstd :: size :: MEGABYTE * 4
	};
};

}
}
}

#include "mm/cut/lexer/mm_cut_lexer_Lexer.ipp"

#endif /*MM_CUT_LEXER_LEXER_HPP_*/
