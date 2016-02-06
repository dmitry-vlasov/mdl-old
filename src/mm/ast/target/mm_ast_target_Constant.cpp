/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_Constant.cpp                               */
/* Description:     mdl constant                                             */
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
#include "math/mm_math.hpp"
#include "ast/mm_ast.hpp"

namespace mm {
namespace ast {
namespace target {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Constant :: Constant
	(
		const vector :: Literal* const literals,
		const mm :: target :: Comments* const comments
	) :
	literals_ (literals),
	constants_ (),
	comments_ (comments),
	block_ (NULL) {
	}
	Constant :: ~ Constant()
	{
		deleteAggregateObject (comments_);
		deleteAggregateObject (translated_);
	}

	// object :: Targetive implementation
	void
	Constant :: complete (mm :: target :: Block* const block) const {
		block_ = block;
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Constant :: write (String& string) const
	{
		collectConstants ();
		if (constants_.isEmpty()) {
			return;
		}
		if (comments_ != NULL) {
			comments_->write (string);
		}
		for (index :: Arity i = 0; i < constants_.getSize(); ++ i) {
			const value :: Literal constant = constants_.getValue (i);
			writeConstant (constant, string);
		}
	}

	// object :: Object implementation
	void
	Constant :: commitSuicide() {
		delete this;
	}
	Size_t
	Constant :: getVolume() const
	{
		Size_t volume = 0;
		volume += constants_.getVolume();
		volume += getAggregateVolume (comments_);
		if (!staticVolumeCounted_) {
			volume += getAggregateVolume (translated_);
			staticVolumeCounted_ = true;
		}
		return volume;
	}
	Size_t
	Constant :: getSizeOf() const {
		return sizeof (Constant);
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Constant :: collectConstants () const
	{
		const index :: Arity arity = literals_->getSize();
		for (index :: Arity i = 0; i < arity; ++ i) {
			const value :: Literal constant = literals_->getValue (i);
			if (isMeaningful (constant)) {
				constants_.add (constant);
			}
		}
	}
	bool
	Constant :: isMeaningful (const value :: Literal constant) const
	{
		if (constant == Math :: constants()->turnstile()) {
			return false;
		}
		const Symbol symbol (constant);
		return (block_->getType (symbol) == NULL);
	}
	void
	Constant :: writeConstant (const value :: Literal constant, String& string) const
	{
		if (translated_ == NULL) {
			translated_ = new Strings_ (INITIAL_STRINGS_CAPACITY);
		}
		const String* ascii = Table :: literals()->getAscii (constant);
		const String* unicode = Table :: literals()->getUnicode (constant);
		const String* latex = Table :: literals()->getLatex (constant);
		if (Config :: useSymbolCorrection() && (unicode != NULL)) {
			for (Strings_ :: Index_ i = 0; i < translated_->getSize(); ++ i) {
				const String* translated = translated_->getValue (i);
				if (*translated == *unicode) {
					return;
				}
			}
			translated_->add (unicode);
		}
		string << tab << mdl :: Token :: constant_ << space << endLine;
		string << tab << mdl :: Token :: openBrace_ << endLine;
		if (!Config :: useSymbolCorrection() || (unicode == NULL)) {
			string << tab << tab << mdl :: Token :: symbol_ << space;
			string << *ascii << space << mdl :: Token :: semicolon_ << endLine;
		} else {
			string << tab << tab << mdl :: Token :: symbol_ << space;
			string << *unicode << space << mdl :: Token :: semicolon_ << endLine;

			string << tab << tab << mdl :: Token :: ascii_ << space;
			string << *ascii << space << mdl :: Token :: semicolon_ << endLine;

			string << tab << tab << mdl :: Token :: latex_ << space;
			string << *latex << space << mdl :: Token :: semicolon_ << endLine;
		}
		string << tab << mdl :: Token :: closeBrace_ << endLine;
		string << endLine;
	}

	/************************************
	 *		Static private attributes
	 ************************************/

	bool
		Constant :: staticVolumeCounted_ = false;
	Constant :: Strings_*
		Constant :: translated_ = NULL;
}
}
}


