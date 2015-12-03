/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_source_Comments.cpp                               */
/* Description:     metamath comments                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_SOURCE_COMMENTS_CPP_
#define MM_AST_SOURCE_COMMENTS_CPP_

#include "auxiliary/mm_auxiliary.hpp"
#include "lexer/mm_lexer.hpp"
#include "ast/mm_ast.hpp"

namespace mm {
namespace ast {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Comments :: Comments
	(
		const Lexer :: Comments_& comments,
		const bool date
	) :
	vector_ (comments.getSize()),
	date_ (date)
	{
		for (Index_ i = 0; i < comments.getSize(); ++ i) {
			const String* comment = new String (*comments.get (i));
			vector_.add (comment);
		}
	}
	Comments :: ~ Comments() {
	}

	// source :: Comments implementation
	Comments :: Index_
	Comments :: getSize() const {
		return vector_.getSize();
	}
	const String*
	Comments :: getString (const Index_ i) const {
		return vector_.getValue (i);
	}
	bool
	Comments :: isDate (const Index_ i) const
	{
		/* $( [3-Jan-2005] $)  - varA
		 * $( [22-May-2005] $) - varB
		 * $( [ ?] $)          - varC */
		const String& comment = *vector_.getValue (i);
		bool varA =
			(comment [1] == '[') &&
			(comment [3] == '-') &&
			(comment [7] == '-') &&
			(comment [12] == ']');
		bool varB =
			(comment [1] == '[') &&
			(comment [4] == '-') &&
			(comment [8] == '-') &&
			(comment [13] == ']');
		bool varC =
			(comment [1] == '[') &&
			(comment [3] == '?') &&
			(comment [4] == ']');
		return (varA || varB || varC);
	}

	// object :: Translatable implementation
	const object :: Targetive*
	Comments :: translate() const {
		return new ast :: target :: Comments (this);
	}
	bool
	Comments :: isBlock() const {
		return false;
	}
	bool
	Comments :: isDisjoined() const {
		return false;
	}
	bool
	Comments :: isFloating() const {
		return false;
	}
	bool
	Comments :: isEssential() const {
		return false;
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Comments :: write (String& string) const
	{
		for (Index_ i = 0; i < vector_.getSize(); ++ i) {
			if (date_ != isDate (i)) {
				continue;
			}
			string << mm :: Token :: commentBegin_ << space;
			string << *vector_.getValue (i) << space;
			string << mm :: Token :: commentEnd_;
			if (date_) {
				string << space;
			} else {
				string << endLine;
			}
		}
	}

	// object :: Object implementation
	void
	Comments :: commitSuicide() {
		delete this;
	}
	Size_t
	Comments :: getVolume() const {
		return vector_.getVolume();
	}
	Size_t
	Comments :: getSizeOf() const {
		return sizeof (Comments);
	}
}
}
}

#endif /* MM_AST_SOURCE_COMMENTS_CPP_ */
