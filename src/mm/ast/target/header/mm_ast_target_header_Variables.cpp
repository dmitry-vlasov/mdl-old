/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_header_Variables.cpp                       */
/* Description:     mdl variables declarations                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_TARGET_HEADER_VARIABLES_CPP_
#define MM_AST_TARGET_HEADER_VARIABLES_CPP_

#include "mdl/lexer/mdl_lexer_Token.hpp"
#include "auxiliary/mm_auxiliary.hpp"
#include "ast/mm_ast.hpp"

namespace mm {
namespace ast {
namespace target {
namespace header {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Variables :: Variables() :
	variables_ () {
	}
	Variables :: ~ Variables() {
	}

	// target :: Variables implementation
	void
	Variables :: addVariable (const mm :: target :: Typing* const variable) {
		variables_.addLast (variable);
	}

	// target :: Typing implementation
	const mm :: target :: Type*
	Variables :: getType (const Symbol& variable) const
	{
		const Variables_ :: Node_*
			node = variables_.getFirst();
		const mm :: target :: Type*
			type = NULL;
		while (node != NULL) {
			type = node->getValue()->getType (variable);
			if (type != NULL) {
				return type;
			}
			node = node->getNext();
		}
		return NULL;
	}

	// object :: Targetive implementation
	void
	Variables :: complete (mm :: target :: Block* const block) const
	{
		const Variables_ :: Node_*
			node = variables_.getFirst();
		while (node != NULL) {
			node->getValue()->complete (block);
			node = node->getNext();
		}
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Writable implementation
	void
	Variables :: write (String& string) const
	{
		string << mdl :: Token :: openBracket_;
		const Variables_ :: Node_*
			node = variables_.getFirst();
		if (node == NULL) {
			string << mdl :: Token :: closeBracket_ << space;
			return;
		}
		while (node != NULL) {
			node->getValue()->write (string);
			if (node->getNext() == NULL) {
				string << mdl :: Token :: closeBracket_ << space;
			} else {
				string << mdl :: Token :: comma_ << space;
			}
			node = node->getNext();
		}
	}

	// object :: Object implementation
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
}
}
}
}


#endif /* MM_AST_TARGET_HEADER_VARIABLES_CPP_ */
