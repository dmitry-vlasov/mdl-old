/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_step_Declaration.cpp                       */
/* Description:     mdl variable declaration in proof                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_TARGET_STEP_DECLARATION_CPP_
#define MM_AST_TARGET_STEP_DECLARATION_CPP_

#include "mdl/lexer/mdl_lexer_Token.hpp"
#include "auxiliary/mm_auxiliary.hpp"
#include "ast/mm_ast.hpp"

namespace mm {
namespace ast {
namespace target {
namespace step {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Declaration :: Declaration (const mm :: target :: Typing* const variable) :
	variable_ (variable) {
	}
	Declaration :: ~ Declaration() {
		deleteAggregateObject (variable_);
	}

	// target :: Step implementation
	void
	Declaration :: incIndex (index :: Step&) const {
	}

	// object :: Referable implementation
	void
	Declaration :: writeReference (String&) const {
	}
	void
	Declaration :: writeIdentificator (String&) const {
	}

	// object :: Targetive implementation
	void
	Declaration :: complete (mm :: target :: Block* const block) const {
		variable_->complete (block);
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;

	// object :: Writable implementation
	void
	Declaration :: write (String& string) const
	{
		string << tab << tab << *variable_;
		string << mdl :: Token :: semicolon_ << endLine;
	}

	// object :: Object implementation
	void
	Declaration :: commitSuicide() {
		delete this;
	}
	Size_t
	Declaration :: getVolume() const {
		return getAggregateVolume (variable_);
	}
	Size_t
	Declaration :: getSizeOf() const {
		return sizeof (Declaration);
	}
}
}
}
}

#endif /* MM_AST_TARGET_STEP_DECLARATION_CPP_ */
