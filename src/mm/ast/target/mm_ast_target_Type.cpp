/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_Type.cpp                                   */
/* Description:     mdl type declaration                                     */
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

	Type :: Type
	(
		const Symbol& symbol,
		mm :: target :: Block* const block
	) :
	declared_ (false),
	symbol_ (symbol),
	super_ (NULL) {
		block->addType (this);
	}
	Type :: ~ Type() {
	}

	// target :: Type implementation
	const Symbol&
	Type :: getSymbol() const {
		return symbol_;
	}
	void
	Type :: setSuper (const mm :: target :: Type* const super) const {
		super_ = super;
	}

	// object :: Referable implementation
	void
	Type :: writeReference (String& string) const {
		string << symbol_;
	}
	void
	Type :: writeIdentificator (String& string) const {
		string << symbol_;
	}

	// object :: Targetive implementation
	void
	Type :: complete (mm :: target :: Block* const) const {
	}

	// object :: Writable implementation
	void
	Type :: write (String& string) const
	{
		if (declared_) {
			return;
		}
		if (super_ != NULL) {
			super_->write (string);
		}
		string << tab << mdl :: Token :: type_ << space;
		writeReference (string);
		if (super_ != NULL) {
			string << mdl :: Token :: colon_ << space;
			super_->writeReference (string);
		}
		string << mdl :: Token :: semicolon_ << endLine;
		string << endLine;
		declared_ = true;
	}

	// object :: Object implementation
	void
	Type :: commitSuicide() {
		delete this;
	}
	Size_t
	Type :: getVolume() const {
		return 0;
	}
	Size_t
	Type :: getSizeOf() const {
		return sizeof (Type);
	}
}
}
}


