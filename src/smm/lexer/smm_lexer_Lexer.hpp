/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_lexer_Lexer.hpp                                      */
/* Description:     smm lexer class                                          */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "smm/lexer/smm_lexer_Scaner.hpp"

namespace smm {
namespace lexer {

class Lexer :
	public nstd :: Object,
	public Scalar<Lexer> {
public :
	Lexer ();
	Lexer (const String&);
	virtual ~ Lexer();

	void open();
	void open (const String&);
	void close();

	value :: Index scanIndex();
	value :: Index scanLabel();
	value :: Index scanAssertion();

	Token :: Type scan();

	template<Token :: Type type>
	Token :: Type scan ();

	template
	<
		Token :: Type type_1,
		Token :: Type type_2
	>
	Token :: Type scan ();

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
	Source source_;
	Scaner scaner_;
	Token :: Type tokenType_;
	mutable String token_;
	enum {
		INITIAL_TOKEN_CAPACITY = 1024
	};
};

}
}

#include "smm/lexer/smm_lexer_Lexer.ipp"


