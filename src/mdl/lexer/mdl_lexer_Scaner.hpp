/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_lexer_Scaner.hpp                                     */
/* Description:     general scaner                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/lexer/mdl_lexer.dpp"
#include "mdl/lexer/mdl_lexer_HorisontalBarScaner.hpp"
#include "mdl/lexer/mdl_lexer_LiteralScaner.hpp"
#include "mdl/lexer/mdl_lexer_NameScaner.hpp"
#include "mdl/lexer/mdl_lexer_NumberScaner.hpp"
#include "mdl/lexer/mdl_lexer_RealScaner.hpp"
#include "mdl/lexer/mdl_lexer_WhitespaceScaner.hpp"

namespace mdl {
namespace lexer {

class Scaner : public object :: Object {
public :
	typedef
		WhitespaceScaner :: Comments_
		Comments_;

	Scaner (Source&);
	virtual ~ Scaner();

	Comments_& comments();
	void scanComments();

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
	bool eofAtStart();
	Token :: Type consume (const Token&, const short pos = 0);
	Token :: Type finalize (const Token :: Type);

	Source& source_;

	HorisontalBarScaner horisontalBarScaner_;
	LiteralScaner literalScaner_;
	NameScaner nameScaner_;
	NumberScaner numberScaner_;
	RealScaner realScaner_;
	WhitespaceScaner whitespaceScaner_;

	bool inExpression_;
};

}
}

#include "mdl/lexer/mdl_lexer_Scaner.ipp"


