/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_target_Comments.cpp                               */
/* Description:     Russell comments                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "auxiliary/mm_auxiliary.hpp"
#include "mdl/lexer/mdl_lexer_Token.hpp"
#include "ast/mm_ast.hpp"

namespace mm {
namespace ast {
namespace target {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Comments :: Comments (const mm :: source :: Comments* comments, const bool date) :
	date_ (date),
	comments_ (comments) {
	}
	Comments :: ~ Comments() {
	}

	// object :: Targetive implementation
	void
	Comments :: complete (mm :: target :: Block* const) const {
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;
using manipulator :: indent;

	// object :: Writable implementation
	void
	Comments :: write (String& string) const
	{
		if (Config :: removeComments()) {
			return;
		}
		for (Index_ i = 0; i < comments_->getSize(); ++ i) {
			if (date_ != comments_->isDate (i)) {
				continue;
			}
			if (date_) {
				string << mdl :: Token :: commentBegin_ << space;
			} else {
				string << tab << mdl :: Token :: commentBegin_ << space;
				string << indent << tab;
			}
			string << *comments_->getString (i) << space;
			string << mdl :: Token :: commentEnd_;
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
		return 0;
	}
	Size_t
	Comments :: getSizeOf() const {
		return sizeof (Comments);
	}
}
}
}


