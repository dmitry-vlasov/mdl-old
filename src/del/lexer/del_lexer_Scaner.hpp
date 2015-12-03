/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_lexer_Scaner.hpp                                     */
/* Description:     general scaner                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_LEXER_SCANER_HPP_
#define DEL_LEXER_SCANER_HPP_

#include "del/lexer/del_lexer.dpp"
#include "del/lexer/del_lexer_NameScaner.hpp"
#include "del/lexer/del_lexer_PathScaner.hpp"
#include "del/lexer/del_lexer_WhitespaceScaner.hpp"

namespace del {
namespace lexer {

class Scaner : public Object {
public :
	typedef
		WhitespaceScaner :: Comments_
		Comments_;

	Scaner (Source&);
	virtual ~ Scaner();

	Comments_& comments();
	void scanComments();
	void scanWhitespace();

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

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	bool eofAtStart();
	bool lookahead (const Token&, const short pos = 0);
	Token :: Type consume (const Token&, const short pos = 0);
	Token :: Type finalize (const Token :: Type);

	Source& source_;
	NameScaner nameScaner_;
	PathScaner pathScaner_;
	WhitespaceScaner whitespaceScaner_;
	bool inExpression_;
};

}
}

#include "del/lexer/del_lexer_Scaner.ipp"

#endif /*DEL_LEXER_SCANER_HPP_*/
