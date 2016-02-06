/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_header_Variable.cpp                        */
/* Description:     mdl variable declaration                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

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
	Variable :: Variable
	(
		const Symbol& variable,
		const Symbol& type
	) :
	variableSymbol_ (variable),
	typeSymbol_ (type),
	type_ (NULL) {
	}
	Variable :: ~ Variable() {
	}

	// target :: Typing implementation
	const mm :: target :: Type*
	Variable :: getType (const Symbol& variable) const {
		return (variableSymbol_ == variable) ? type_ : NULL;
	}

	// object :: Targetive implementation
	void
	Variable :: complete (mm :: target :: Block* const block) const
	{
		type_ = block->getType (typeSymbol_);
		if (type_ == NULL) {
			type_ = new ast :: target :: Type (typeSymbol_, block);
		}
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Writable implementation
	void
	Variable :: write (String& string) const {
		string << mdl :: Token :: variable_ << space << variableSymbol_;
		string << mdl :: Token :: colon_ << space << typeSymbol_;
	}

	// object :: Object implementation
	void
	Variable :: commitSuicide() {
		delete this;
	}
	Size_t
	Variable :: getVolume() const {
		return 0;
	}
	Size_t
	Variable :: getSizeOf() const {
		return sizeof (Variable);
	}
}
}
}
}


