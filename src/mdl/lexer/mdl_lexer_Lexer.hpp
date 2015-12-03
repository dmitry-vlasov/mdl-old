/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_lexer_Lexer.hpp                                      */
/* Description:     lexer class                                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_LEXER_LEXER_HPP_
#define MDL_LEXER_LEXER_HPP_

#include "mdl/lexer/mdl_lexer_Scaner.hpp"

namespace mdl {
namespace lexer {

class Lexer :
	public object :: Object,
	public Scalar<Lexer> {
public :
	typedef
		Scaner :: Comments_
		Comments_;

	Lexer (const String&, const bool = false);
	virtual ~ Lexer();

	bool isTop() const;
	void open();
	void open (const String&);
	void close();

	template<class T>
	T scanNumber();
	value :: Real scanReal();
	value :: Name scanName();
	value :: Literal scanLiteral();
	value :: Literal scanLiteralName();

	Comments_& comments();
	void scanComments();

	Token :: Type expectToken (const Token :: Type);
	Token :: Type expectTokens (const Token :: Type, const Token :: Type);

	Token :: Type getTokenType() const;
	const String& getToken() const;
	const Location& getLocation();

	template
	<
		Token :: Type type
	>
	Token :: Type scan ();

	template
	<
		Token :: Type type_1,
		Token :: Type type_2
	>
	Token :: Type scan ();

	template
	<
		Token :: Type type_1,
		Token :: Type type_2,
		Token :: Type type_3
	>
	Token :: Type scan ();

	template
	<
		Token :: Type type_1,
		Token :: Type type_2,
		Token :: Type type_3,
		Token :: Type type_4
	>
	Token :: Type scan ();

	template
	<
		Token :: Type type_1,
		Token :: Type type_2,
		Token :: Type type_3,
		Token :: Type type_4,
		Token :: Type type_5
	>
	Token :: Type scan ();

	template
	<
		Token :: Type type_1,
		Token :: Type type_2,
		Token :: Type type_3,
		Token :: Type type_4,
		Token :: Type type_5,
		Token :: Type type_6
	>
	Token :: Type scan ();

	template
	<
		Token :: Type type_1,
		Token :: Type type_2,
		Token :: Type type_3,
		Token :: Type type_4,
		Token :: Type type_5,
		Token :: Type type_6,
		Token :: Type type_7
	>
	Token :: Type scan ();

	template
	<
		Token :: Type type_1,
		Token :: Type type_2,
		Token :: Type type_3,
		Token :: Type type_4,
		Token :: Type type_5,
		Token :: Type type_6,
		Token :: Type type_7,
		Token :: Type type_8
	>
	Token :: Type scan ();

	template
	<
		Token :: Type type_1,
		Token :: Type type_2,
		Token :: Type type_3,
		Token :: Type type_4,
		Token :: Type type_5,
		Token :: Type type_6,
		Token :: Type type_7,
		Token :: Type type_8,
		Token :: Type type_9
	>
	Token :: Type scan ();

	template
	<
		Token :: Type type_1,
		Token :: Type type_2,
		Token :: Type type_3,
		Token :: Type type_4,
		Token :: Type type_5,
		Token :: Type type_6,
		Token :: Type type_7,
		Token :: Type type_8,
		Token :: Type type_9,
		Token :: Type type_10
	>
	Token :: Type scan ();

	template
	<
		Token :: Type type_1,
		Token :: Type type_2,
		Token :: Type type_3,
		Token :: Type type_4,
		Token :: Type type_5,
		Token :: Type type_6,
		Token :: Type type_7,
		Token :: Type type_8,
		Token :: Type type_9,
		Token :: Type type_10,
		Token :: Type type_11
	>
	Token :: Type scan ();

	template
	<
		Token :: Type type_1,
		Token :: Type type_2,
		Token :: Type type_3,
		Token :: Type type_4,
		Token :: Type type_5,
		Token :: Type type_6,
		Token :: Type type_7,
		Token :: Type type_8,
		Token :: Type type_9,
		Token :: Type type_10,
		Token :: Type type_11,
		Token :: Type type_12
	>
	Token :: Type scan ();

	template
	<
		Token :: Type type_1,
		Token :: Type type_2,
		Token :: Type type_3,
		Token :: Type type_4,
		Token :: Type type_5,
		Token :: Type type_6,
		Token :: Type type_7,
		Token :: Type type_8,
		Token :: Type type_9,
		Token :: Type type_10,
		Token :: Type type_11,
		Token :: Type type_12,
		Token :: Type type_13
	>
	Token :: Type scan ();

	template
	<
		Token :: Type type_1,
		Token :: Type type_2,
		Token :: Type type_3,
		Token :: Type type_4,
		Token :: Type type_5,
		Token :: Type type_6,
		Token :: Type type_7,
		Token :: Type type_8,
		Token :: Type type_9,
		Token :: Type type_10,
		Token :: Type type_11,
		Token :: Type type_12,
		Token :: Type type_13,
		Token :: Type type_14
	>
	Token :: Type scan ();

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	const String& guessToken();

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

#include "mdl/lexer/mdl_lexer_Lexer.ipp"

#endif /*MDL_LEXER_LEXER_HPP_*/
