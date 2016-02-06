/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_lexer_Scaner.ipp                                     */
/* Description:     general scaner                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace lexer {

	/****************************
	 *		Public members
	 ****************************/

	inline Scaner :: Comments_&
	Scaner :: comments() {
		return whitespaceScaner_.comments();
	}
	inline void
	Scaner :: scanComments() {
		whitespaceScaner_.scan();
	}

	/*    One token scanners    */

	/// One char scanners
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: COLON
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case ':' :
			++ source_;
			return finalize (Token :: COLON);
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: SEMICOLON
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case ';' :
			++ source_;
			return finalize (Token :: SEMICOLON);
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: COMMA
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case ',' :
			++ source_;
			return finalize (Token :: COMMA);
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: OPEN_BRACE
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case '{' :
			++ source_;
			return finalize (Token :: OPEN_BRACE);
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: CLOSE_BRACE
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case '}' :
			++ source_;
			return finalize (Token :: CLOSE_BRACE);
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: OPEN_BRACKET
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case '(' :
			++ source_;
			return finalize (Token :: OPEN_BRACKET);
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: CLOSE_BRACKET
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case ')' :
			++ source_;
			return finalize (Token :: CLOSE_BRACKET);
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: OPEN_SQ_BRACKET
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case '[' :
			++ source_;
			return finalize (Token :: OPEN_SQ_BRACKET);
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: CLOSE_SQ_BRACKET
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case ']' :
			++ source_;
			return finalize (Token :: CLOSE_SQ_BRACKET);
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: TURNSTILE
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case '|' :
			++ source_;
			if (source_.getChar() == '-') {
				++ source_;
				return finalize (Token :: TURNSTILE);
			}
			return finalize (Token :: UNKNOWN);
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: SHARP
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case '#' :
			++ source_;
			return finalize (Token :: SHARP);
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: EQUALITY
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case '=' :
			++ source_;
			return finalize (Token :: EQUALITY);
		default :
			return finalize (Token :: UNKNOWN);
		}
	}

	/// String token scanners
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: LITERAL
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		return finalize (literalScaner_.scan());
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: NUMBER
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		return finalize (numberScaner_.scan());
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: REAL_NUMBER
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		return finalize (realScaner_.scan());
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: NAME
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		return finalize (nameScaner_.scan());
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: PROP
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case 'p' :
			return finalize (consume (Token :: prop_));
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: TERM
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case 't' :
			return finalize (consume (Token :: term_));
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: STEP
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case 's' :
			return finalize (consume (Token :: step_));
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: TYPE
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case 't' :
			return finalize (consume (Token :: type_));
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: THEORY
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case 't' :
			return finalize (consume (Token :: theory_));
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: THEOREM
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case 't' :
			return finalize (consume (Token :: theorem_));
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: OF
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case 'o' :
			++ source_;
			if (source_.getChar() == 'f') {
				++ source_;
				return finalize (Token :: OF);
			}
			return finalize (Token :: UNKNOWN);
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: PROOF
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case 'p' :
			return finalize (consume (Token :: proof_));
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: VARIABLE
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case 'v' :
			return finalize (consume (Token :: variable_));
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: ABBREVIATION
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case 'a' :
			return finalize (consume (Token :: abbreviation_));
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: MEANING
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case 'm' :
			return finalize (consume (Token :: meaning_));
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: DEFIENDUM
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case 'd' :
			return finalize (consume (Token :: defiendum_));
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: DEFINIENS
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case 'd' :
			return finalize (consume (Token :: definiens_));
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: EOF_
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		} else {
			return finalize (Token :: UNKNOWN);
		}
	}

	/*    Two token scanners    */

	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: QUESTION,
		Token :: NAME
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case '?' :
			++ source_;
			return finalize (Token :: QUESTION);
		default :
			return finalize (nameScaner_.scan());
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: HYP,
		Token :: PROP
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case 'h' :
			return finalize (consume (Token :: hyp_));
		case 'p' :
			return finalize (consume (Token :: prop_));
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: HYP,
		Token :: HORISONTAL_BAR
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case 'h' :
			return finalize (consume (Token :: hyp_));
		case '-' :
			return finalize (horisontalBarScaner_.scan ());
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: PROP,
		Token :: CLOSE_BRACE
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case 'p' :
			return finalize (consume (Token :: prop_));
		case '}' :
			++ source_;
			return finalize (Token :: CLOSE_BRACE);
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: PROP,
		Token :: CLAIM
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case 'p' :
			return finalize (consume (Token :: prop_));
		case 'c' :
			return finalize (consume (Token :: claim_));
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: OPEN_BRACE,
		Token :: DISJOINTED
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case '{' :
			++ source_;
			return finalize (Token :: OPEN_BRACE);
		case 'd' :
			return finalize (consume (Token :: disjointed_));
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: NUMBER,
		Token :: TURNSTILE
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case '|' :
			++ source_;
			if (source_.getChar() == '-') {
				++ source_;
				return finalize (Token :: TURNSTILE);
			}
		default :
			return finalize (numberScaner_.scan());
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: NUMBER,
		Token :: SHARP
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case '#' :
			++ source_;
			return finalize (Token :: SHARP);
		default :
			return finalize (numberScaner_.scan());
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: EQUALITY,
		Token :: NUMBER
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case '=' :
			++ source_;
			return finalize (Token :: EQUALITY);
		default :
			return finalize (numberScaner_.scan());
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: NUMBER,
		Token :: COLON
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case ':' :
			++ source_;
			return finalize (Token :: COLON);
		default :
			return finalize (numberScaner_.scan());
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: NUMBER,
		Token :: QUESTION
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case '?' :
			++ source_;
			return finalize (Token :: QUESTION);
		default :
			return finalize (numberScaner_.scan());
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: UP_ARROW,
		Token :: NUMBER
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case '^' :
			++ source_;
			return finalize (Token :: UP_ARROW);
		default :
			return finalize (numberScaner_.scan());
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: LITERAL,
		Token :: SEMICOLON
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case ';' :
			++ source_;
			return finalize (Token :: SEMICOLON);
		default :
			return finalize (literalScaner_.scan());
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: SEMICOLON,
		Token :: COLON
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case ';' :
			++ source_;
			return finalize (Token :: SEMICOLON);
		case ':' :
			++ source_;
			return finalize (Token :: COLON);
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: SEMICOLON,
		Token :: COMMA
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case ';' :
			++ source_;
			return finalize (Token :: SEMICOLON);
		case ',' :
			++ source_;
			return finalize (Token :: COMMA);
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: OPEN_BRACKET,
		Token :: COLON
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case '(' :
			++ source_;
			return finalize (Token :: OPEN_BRACKET);
		case ':' :
			++ source_;
			return finalize (Token :: COLON);
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: NAME,
		Token :: CLOSE_BRACKET
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case ')' :
			++ source_;
			return finalize (Token :: CLOSE_BRACKET);
		default :
			return finalize (nameScaner_.scan());
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: NAME,
		Token :: OF
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case 'o' :
			++ source_;
			if (source_.getChar() == 'f') {
				++ source_;
				return finalize (Token :: OF);
			} else {
				return finalize (nameScaner_.scan());
			}
		default :
			return finalize (nameScaner_.scan());
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: NAME,
		Token :: STEP
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case 's' :
			++ source_;
			return finalize (consume (Token :: step_, 1));
		default :
			return finalize (nameScaner_.scan());
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: OPEN_BRACKET,
		Token :: NUMBER
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case '(' :
			++ source_;
			return finalize (Token :: OPEN_BRACKET);
		default :
			return finalize (numberScaner_.scan());
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: DOT,
		Token :: CLOSE_BRACKET
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case ')' :
			++ source_;
			return finalize (Token :: CLOSE_BRACKET);
		case '.' :
			++ source_;
			return finalize (Token :: DOT);
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: DOT,
		Token :: SEMICOLON
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case '.' :
			++ source_;
			return finalize (Token :: DOT);
		case ';' :
			++ source_;
			return finalize (Token :: SEMICOLON);
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: COMMA,
		Token :: CLOSE_BRACKET
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case ',' :
			++ source_;
			return finalize (Token :: COMMA);
		case ')' :
			++ source_;
			return finalize (Token :: CLOSE_BRACKET);
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: OPEN_SQ_BRACKET,
		Token :: OPEN_BRACKET
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case '[' :
			++ source_;
			return finalize (Token :: OPEN_SQ_BRACKET);
		case '(' :
			++ source_;
			return finalize (Token :: OPEN_BRACKET);
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: VARIABLE,
		Token :: CLOSE_BRACKET
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case 'v' :
			return finalize (consume (Token :: variable_));
		case ')' :
			++ source_;
			return finalize (Token :: CLOSE_BRACKET);
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: COLON,
		Token :: CLOSE_BRACE
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case ':' :
			++ source_;
			return finalize (Token :: COLON);
		case '}' :
			++ source_;
			return finalize (Token :: CLOSE_BRACE);
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: THEOREM,
		Token :: CLOSE_SQ_BRACKET
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case 't' :
			++ source_;
			return finalize (consume (Token :: theorem_, 1));
		case ']' :
			++ source_;
			return finalize (Token :: CLOSE_SQ_BRACKET);
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: COMMA,
		Token :: CLOSE_SQ_BRACKET
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case ',' :
			++ source_;
			return finalize (Token :: COMMA);
		case ']' :
			++ source_;
			return finalize (Token :: CLOSE_SQ_BRACKET);
		default :
			return finalize (Token :: UNKNOWN);
		}
	}

	/*    Three token scanners    */

	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: NAME,
		Token :: CLOSE_BRACKET,
		Token :: COMMA
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case ')' :
			++ source_;
			return finalize (Token :: CLOSE_BRACKET);
		case ',' :
			++ source_;
			return finalize (Token :: COMMA);
		default :
			return finalize (nameScaner_.scan());
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: HYP,
		Token :: PROP,
		Token :: STEP
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case 'h' :
			return finalize (consume (Token :: hyp_));
		case 's' :
			return finalize (consume (Token :: step_));
		case 'p' :
			return finalize (consume (Token :: prop_));
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: PLUS,
		Token :: MINUS,
		Token :: CLOSE_SQ_BRACKET
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case '+' :
			++ source_;
			return finalize (Token :: PLUS);
		case '-' :
			++ source_;
			return finalize (Token :: MINUS);
		case ']' :
			++ source_;
			return finalize (Token :: CLOSE_SQ_BRACKET);
		default :
			return finalize (Token :: UNKNOWN);
		}
	}

	/*    Four token scanners    */

	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: IMPORT,
		Token :: THEORY,
		Token :: CONTENTS,
		Token :: EOF_
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case 'i' :
			return finalize (consume (Token :: import_));
		case 't' :
			return finalize (consume (Token :: theory_));
		case 'c' :
			return finalize (consume (Token :: contents_));
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: SYMBOL,
		Token :: ASCII,
		Token :: LATEX,
		Token :: CLOSE_BRACE
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case '}' :
			++ source_;
			return finalize (Token :: CLOSE_BRACE);
		case 's' :
			return finalize (consume (Token :: symbol_));
		case 'a' :
			return finalize (consume (Token :: ascii_));
		case 'l' :
			return finalize (consume (Token :: latex_));
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: HYP,
		Token :: PROP,
		Token :: STEP,
		Token :: CLOSE_BRACKET
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case ')' :
			++ source_;
			return finalize (Token :: CLOSE_BRACKET);
		case 'h' :
			return finalize (consume (Token :: hyp_));
		case 's' :
			return finalize (consume (Token :: step_));
		case 'p' :
			return finalize (consume (Token :: prop_));
		default :
			return finalize (Token :: UNKNOWN);
		}
	}

	/*    Five token scanners    */

	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: STEP,
		Token :: QED,
		Token :: VARIABLE,
		Token :: NOTATION,
		Token :: CLOSE_BRACE
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case '}' :
			++ source_;
			return finalize (Token :: CLOSE_BRACE);
		case 'q' :
			return finalize (consume (Token :: qed_));
		case 'n' :
			return finalize (consume (Token :: notation_));
		case 'v' :
			return finalize (consume (Token :: variable_));
		case 's' :
			return finalize (consume (Token :: step_));
		default :
			return finalize (Token :: UNKNOWN);
		}
	}

	/*    Six token scanners    */

	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: QUESTION,
		Token :: CLAIM,
		Token :: AXIOM,
		Token :: THEOREM,
		Token :: DEFINITION
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case '?' :
			++ source_;
			return finalize (Token :: QUESTION);
		case 'c' :
			return finalize (consume (Token :: claim_));
		case 'a' :
			return finalize (consume (Token :: axiom_));
		case 't' :
			return finalize (consume (Token :: theorem_));
		case 'd' :
			return finalize (consume (Token :: definition_));
		default :
			return finalize (Token :: UNKNOWN);
		}
	}

	/*    Seven token scanners    */

	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: DOT,
		Token :: COMMA,
		Token :: SEMICOLON,
		Token :: EQUALITY,
		Token :: COLON,
		Token :: OPEN_BRACKET,
		Token :: OPEN_BRACE,
		Token :: CLOSE_BRACKET
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case '.' :
			++ source_;
			return finalize (Token :: DOT);
		case ',' :
			return finalize (Token :: COMMA);
		case ';' :
			return finalize (Token :: SEMICOLON);
		case '=' :
			return finalize (Token :: EQUALITY);
		case ':' :
			return finalize (Token :: COLON);
		case '(' :
			return finalize (Token :: OPEN_BRACKET);
		case '{' :
			return finalize (Token :: OPEN_BRACE);
		case ')' :
			return finalize (Token :: CLOSE_BRACKET);
		default :
			return finalize (Token :: UNKNOWN);
		}
	}

	/*    Plenty of variants    */

	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: SUM,
		Token :: MULT,
		Token :: LEXP,
		Token :: CONST,
		Token :: SUB_CPLX,
		Token :: EXP_CPLX,
		Token :: EXP_AVG,
		Token :: EXP_SIM,
		Token :: EXP_EQ,
		Token :: EXP_DISP,
		Token :: FORKING,
		Token :: WEIGHTED_SUM,
		Token :: BARRIER,
		Token :: CLOSE_BRACKET
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case 's' :
			++ source_;
			if (source_.getChar() == 'u') {
				++ source_;
				if (source_.getChar() == 'm') {
					++ source_;
					return finalize (Token :: SUM);
				} else {
					return finalize (consume (Token :: subCplx_, 2));
				}
			}
			return finalize (Token :: UNKNOWN);
		case 'm' :
			return finalize (consume (Token :: mult_));
		case 'l' :
			return finalize (consume (Token :: lexp_));
		case 'f' :
			return finalize (consume (Token :: forking_));
		case 'c' :
			return finalize (consume (Token :: const_));
		case 'e' :
			++ source_;
			if (source_.getChar() == 'x') {
				++ source_;
				if (source_.getChar() == 'p') {
					++ source_;
					if (source_.getChar() == '_') {
						++ source_;
						switch (source_.getChar().getValue()) {
						case 'c' :
							return finalize (consume (Token :: expCplx_, 4));
						case 'a' :
							return finalize (consume (Token :: expAvg_, 4));
						case 's' :
							return finalize (consume (Token :: expSim_, 4));
						case 'e' :
							return finalize (consume (Token :: expEq_, 4));
						case 'd' :
							return finalize (consume (Token :: expDisp_, 4));
						default :
							return finalize (Token :: UNKNOWN);
						}
					}
				}
			}
			return finalize (Token :: UNKNOWN);
		case 'w' :
			return finalize (consume (Token :: weightedSum_));
		case 'b' :
			return finalize (consume (Token :: barrier_));
		case ')' :
			++ source_;
			return finalize (Token :: CLOSE_BRACKET);
		default :
			return finalize (Token :: UNKNOWN);
		}
	}

	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: CONSTANT,
		Token :: TYPE,
		Token :: RULE,
		Token :: AXIOM,
		Token :: DEFINITION,
		Token :: THEOREM,
		Token :: PROOF,
		Token :: PROBLEM,
		Token :: THEORY,
		Token :: EVALUATION,
		Token :: CONTENTS,
		Token :: CLOSE_BRACE
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case '}' :
			++ source_;
			return finalize (Token :: CLOSE_BRACE);
		case 'c' :
			++ source_;
			if (source_.getChar().getValue() == 'o') {
				++ source_;
				if (source_.getChar().getValue() == 'n') {
					++ source_;
					if (source_.getChar().getValue() == 's') {
						return finalize (consume (Token :: constant_, 3));
					}
					if (source_.getChar().getValue() == 't') {
						return finalize (consume (Token :: contents_, 3));
					}
				}
			}
			return finalize (Token :: UNKNOWN);
		case 'r' :
			return finalize (consume (Token :: rule_));
		case 't' :
			++ source_;
			switch (source_.getChar().getValue()) {
			case 'y' :
				return finalize (consume (Token :: type_, 1));
			case 'h' :
				++ source_;
				if (source_.getChar().getValue() == 'e') {
					++ source_;
					if (source_.getChar().getValue() == 'o') {
						++ source_;
						if (source_.getChar().getValue() == 'r') {
							++ source_;
							if (source_.getChar().getValue() == 'y') {
								++ source_;
								return finalize (Token :: THEORY);
							} else if (source_.getChar().getValue() == 'e') {
								return finalize (consume (Token :: theorem_, 5));
							}
						}
					}
				}
				return finalize (nameScaner_.scan());
			default :
				return finalize (nameScaner_.scan());
			}
			return finalize (Token :: UNKNOWN);
		case 'a' :
			return finalize (consume (Token :: axiom_));
		case 'd' :
			return finalize (consume (Token :: definition_));
		case 'p' :
			++ source_;
			if (source_.getChar().getValue() == 'r') {
				++ source_;
				if (source_.getChar().getValue() == 'o') {
					++ source_;
					if (source_.getChar().getValue() == 'b') {
						return finalize (consume (Token :: problem_, 3));
					} else {
						return finalize (consume (Token :: proof_, 3));
					}
				}
			}
			return finalize (Token :: UNKNOWN);
		case 'e' :
			return finalize (consume (Token :: evaluation_));
		default :
			return finalize (Token :: UNKNOWN);
		}
	}

}
}


