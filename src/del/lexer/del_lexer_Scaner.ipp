/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_lexer_Scaner.ipp                                     */
/* Description:     general scaner                                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace del {
namespace lexer {

	/****************************
	 *		Public members
	 ****************************/

	//  One token scanners
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
		Token :: MODELS
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		return finalize (consume (Token :: models_));
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: DOES_NOT_MODEL
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		return finalize (consume (Token :: does_not_model_));
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
		switch (source_.getChar().getValue()) {
		case ',' :
			++ source_;
			return finalize (Token :: CLOSE_BRACKET);
		case ')' :
			++ source_;
			return finalize (Token :: CLOSE_BRACKET);
		case '}' :
			++ source_;
			return finalize (Token :: CLOSE_BRACE);
		default :
			return finalize (nameScaner_.scan());
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: PATH
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		return finalize (pathScaner_.scan());
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: DOT
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
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
		Token :: INTERSECT
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		return finalize (consume (Token :: intersect_));
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
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
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: ASSERTION
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case '!' :
			++ source_;
			return finalize (Token :: ASSERTION);
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
		Token :: UNION
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		return finalize (consume (Token :: union_));
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: DECOMPOSITION_OF
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		return finalize (consume (Token :: decompositionOf_));
	}

	//  Two token scanners
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: COMMA,
		Token :: CLOSE_BRACE
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case ',' :
			++ source_;
			return finalize (Token :: COMMA);
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
		Token :: SUBSET,
		Token :: EQUAL
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		if (lookahead (Token :: subset_)) {
			return finalize (consume (Token :: subset_));
		}
		if (lookahead (Token :: equal_)) {
			return finalize (consume (Token :: equal_));
		}
		return finalize (Token :: UNKNOWN);
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: MODELS,
		Token :: DOES_NOT_MODEL
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		if (lookahead (Token :: models_)) {
			return finalize (consume (Token :: models_));
		}
		if (lookahead (Token :: does_not_model_)) {
			return finalize (consume (Token :: does_not_model_));
		}
		return finalize (Token :: UNKNOWN);
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: CONCEPT,
		Token :: RELATION
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case 'c' :
			++ source_;
			return finalize (consume (Token :: concept_, 1));
		case 'r' :
			++ source_;
			return finalize (consume (Token :: relation_, 1));
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: INTERSECT,
		Token :: CLOSE_BRACKET
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		if (source_.getChar().getValue() == ')') {
			++ source_;
			return finalize (Token :: CLOSE_BRACKET);
		}
		if (lookahead (Token :: intersect_)) {
			return finalize (consume (Token :: intersect_));
		}
		return finalize (Token :: UNKNOWN);
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: UNION,
		Token :: CLOSE_BRACKET
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		if (source_.getChar().getValue() == ')') {
			++ source_;
			return finalize (Token :: CLOSE_BRACKET);
		}
		if (lookahead (Token :: union_)) {
			return finalize (consume (Token :: union_));
		}
		return finalize (Token :: UNKNOWN);
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: OPEN_BRACE,
		Token :: OPEN_BRACKET
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case '{' :
			++ source_;
			return finalize (Token :: OPEN_BRACE);
		case '(' :
			++ source_;
			return finalize (Token :: OPEN_BRACKET);
		default :
			++ source_;
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: COPY,
		Token :: NAME
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		if (lookahead (Token :: copy_)) {
			return finalize (consume (Token :: copy_));
		}
		return finalize (nameScaner_.scan());
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: CLOSE_BRACKET,
		Token :: UNION
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		if (source_.getChar().getValue() == ')') {
			++ source_;
			return finalize (Token :: CLOSE_BRACKET);
		}
		if (lookahead (Token :: union_)) {
			return finalize (consume (Token :: union_));
		}
		return finalize (nameScaner_.scan());
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: SIGNATURE,
		Token :: THEORY
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case 's' :
			++ source_;
			return finalize (consume (Token :: signature_, 1));
		case 't' :
			++ source_;
			return finalize (consume (Token :: theory_, 1));
		default :
			return finalize (Token :: UNKNOWN);
		}
	}

	// Three token scanners
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: CLOSE_BRACKET,
		Token :: COPY,
		Token :: NAME
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		if (source_.getChar().getValue() == ')') {
			++ source_;
			return finalize (Token :: CLOSE_BRACKET);
		}
		if (lookahead (Token :: copy_)) {
			return finalize (consume (Token :: copy_));
		}
		return finalize (nameScaner_.scan());
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: CONCEPT,
		Token :: RELATION,
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
			return finalize (consume (Token :: concept_, 1));
		case 'r' :
			++ source_;
			return finalize (consume (Token :: relation_, 1));
		default :
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: OPEN_BRACE,
		Token :: OPEN_BRACKET,
		Token :: FILE
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case '{' :
			++ source_;
			return finalize (Token :: OPEN_BRACE);
		case '(' :
			++ source_;
			return finalize (Token :: OPEN_BRACKET);
		case 'f' :
			++ source_;
			return finalize (consume (Token :: file_, 1));
		default :
			++ source_;
			return finalize (Token :: UNKNOWN);
		}
	}
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: COMMA,
		Token :: CLOSE_BRACE,
		Token :: NAME
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case ',' :
			++ source_;
			return finalize (Token :: COMMA);
		case '}' :
			++ source_;
			return finalize (Token :: CLOSE_BRACE);
		default :
			return finalize (nameScaner_.scan());
		}
	}

	// five token scaners
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: CONCEPT,
		Token :: RELATION,
		Token :: CONCEPTS,
		Token :: RELATIONS,
		Token :: CLOSE_BRACE
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		if (source_.getChar().getValue() == '}') {
			++ source_;
			return finalize (Token :: CLOSE_BRACE);
		}
		if (lookahead (Token :: concepts_)) {
			return finalize (consume (Token :: concepts_));
		}
		if (lookahead (Token :: relations_)) {
			return finalize (consume (Token :: relations_));
		}
		if (lookahead (Token :: concept_)) {
			return finalize (consume (Token :: concept_));
		}
		if (lookahead (Token :: relation_)) {
			return finalize (consume (Token :: relation_));
		}
		return finalize (Token :: UNKNOWN);
	}

	// Six token scanners
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: EXISTS,
		Token :: OPEN_BRACKET,
		Token :: TOP,
		Token :: NAME,
		Token :: COPY,
		Token :: CLOSE_BRACE
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		if (source_.getChar().getValue() == '(') {
			++ source_;
			return finalize (Token :: OPEN_BRACKET);
		}
		if (source_.getChar().getValue() == '}') {
			++ source_;
			return finalize (Token :: CLOSE_BRACE);
		}
		if (lookahead (Token :: exists_)) {
			return finalize (consume (Token :: exists_));
		}
		if (lookahead (Token :: top_)) {
			return finalize (consume (Token :: top_));
		}
		if (lookahead (Token :: copy_)) {
			return finalize (consume (Token :: copy_));
		}
		return finalize (nameScaner_.scan());
	}
	/*template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: THEORY,
		Token :: DOES,
		Token :: SOLUTION,
		Token :: SIGNATURE,
		Token :: EOF_
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case 't' :
			return finalize (consume (Token :: theory_));
		case 'd' :
			return finalize (consume (Token :: does_));
		case 's' :
			++ source_;
			switch (source_.getChar().getValue()) {
			case 'o' :
				++ source_;
				return finalize (consume (Token :: solution_, 2));
			case 'i' :
				++ source_;
				return finalize (consume (Token :: signature_, 2));
			default :
				return finalize (Token :: UNKNOWN);
			}
		default :
			return finalize (Token :: UNKNOWN);
		}
	}*/

	// Ten token scanners
	template<>
	Token :: Type
	Scaner :: scan
	<
		Token :: ASSERT,
		Token :: THEORY,
		Token :: DOES,
		Token :: SOLUTION,
		Token :: SIGNATURE,
		Token :: DECOMPOSE,
		Token :: DECOMPOSITION_OF,
		Token :: MINIMIZE,
		Token :: MINIMIZATION_OF,
		Token :: EOF_
	> ()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case 'a' :
			return finalize (consume (Token :: assert_));
		case 't' :
			return finalize (consume (Token :: theory_));
		case 'd' : {
			if (lookahead (Token :: does_)) {
				return finalize (consume (Token :: does_));
			}
			if (lookahead (Token :: decompose_)) {
				return finalize (consume (Token :: decompose_));
			}
			if (lookahead (Token :: decompositionOf_)) {
				return finalize (consume (Token :: decompositionOf_));
			}
			return finalize (Token :: UNKNOWN);
		}
		case 's' :
			++ source_;
			switch (source_.getChar().getValue()) {
			case 'o' :
				++ source_;
				return finalize (consume (Token :: solution_, 2));
			case 'i' :
				++ source_;
				return finalize (consume (Token :: signature_, 2));
			default :
				return finalize (Token :: UNKNOWN);
			}
		case 'm' : {
			if (lookahead (Token :: minimize_)) {
				return finalize (consume (Token :: minimize_));
			}
			if (lookahead (Token :: minimizationOf_)) {
				return finalize (consume (Token :: minimizationOf_));
			}
			return finalize (Token :: UNKNOWN);
		}
		default :
			return finalize (Token :: UNKNOWN);
		}
	}

}
}


