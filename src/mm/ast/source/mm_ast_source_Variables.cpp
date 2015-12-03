/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_source_Variables.cpp                              */
/* Description:     metamath variables                                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_SOURCE_VARIABLES_CPP_
#define MM_AST_SOURCE_VARIABLES_CPP_

#include "auxiliary/mm_auxiliary.hpp"
#include "lexer/mm_lexer.hpp"
#include "ast/mm_ast.hpp"

namespace mm {
namespace ast {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	Variables :: Variables
	(
		const Location& location,
		const vector :: Literal& variables,
		mm :: source :: Block* const block
	) :
	location_ (location),
	variables_ (variables),
	previous_ (block->getVariables())
	{
		block->pushVariables (this);
		checkSemanticCorrectness (block);
	}
	Variables :: ~ Variables() {
	}

	// source :: Variables implementation
	bool
	Variables :: isVariable (const value :: Literal literal) const
	{
		if (variables_.contains (literal)) {
			return true;
		}
		if (previous_ != NULL) {
			return previous_->isVariable (literal);
		}
		return false;
	}
	const mm :: source :: Variables*
	Variables :: getPrevious() const {
		return previous_;
	}

	// object :: Translatable interface
	const object :: Targetive*
	Variables :: translate() const {
		return NULL;
	}
	bool
	Variables :: isBlock() const {
		return false;
	}
	bool
	Variables :: isDisjoined() const {
		return false;
	}
	bool
	Variables :: isFloating() const {
		return false;
	}
	bool
	Variables :: isEssential() const {
		return false;
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Variables :: write (String& string) const
	{
		string << tab << mm :: Token :: variable_ << space;
		for (index :: Literal i = 0; i < variables_.getSize(); i++) {
			const value :: Literal variable = variables_.getValue (i);
			string << Table :: literals()->get (variable) << space;
		}
		string << mm :: Token :: end_ << endLine;
	}

	// object :: Object interface
	void
	Variables :: commitSuicide() {
		delete this;
	}
	Size_t
	Variables :: getVolume() const {
		return variables_.getVolume();
	}
	Size_t
	Variables :: getSizeOf() const {
		return sizeof (Variables);
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Variables :: checkSemanticCorrectness (const mm :: source :: Block* const block) const
	{
		const mm :: source :: Constants* const
			constants = block->getConstants();

		for (index :: Literal i = 0; i < variables_.getSize(); ++ i ) {
			const value :: Literal
				literal = variables_.getValue (i);
			if (previous_ != NULL && previous_->isVariable (literal)) {
				Error* error = new Error (location_, Error :: SEMANTIC, "duplicate variable declaration.");
				error->message() << "variable: " << Table :: literals()->get (literal);
				throw error;
			}
			if (constants != NULL && constants->isConstant (literal)) {
				Error* error = new Error (location_, Error :: SEMANTIC, "variable symbol previously was declared as a constant.");
				error->message() << "symbol: " << Table :: literals()->get (literal);
				throw error;
			}
		}
	}
}
}
}

#endif /*MM_AST_SOURCE_VARIABLES_CPP_*/
