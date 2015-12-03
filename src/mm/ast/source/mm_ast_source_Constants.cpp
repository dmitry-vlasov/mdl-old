/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_source_Constants.cpp                              */
/* Description:     metamath constants                                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_SOURCE_CONSTANTS_CPP_
#define MM_AST_SOURCE_CONSTANTS_CPP_

#include "auxiliary/mm_auxiliary.hpp"
#include "lexer/mm_lexer.hpp"
#include "math/mm_math.hpp"
#include "ast/mm_ast.hpp"

namespace mm {
namespace ast {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	Constants :: Constants
	(
		const Location& location,
		const mm :: source :: Comments* comments,
		const vector :: Literal& constants,
		mm :: source :: Block* const block
	) :
	location_ (location),
	comments_ (comments),
	constants_ (constants),
	previous_ (block->getConstants ())
	{
		block->pushConstants (this);
		checkSemanticCorrectness (block);
		Math :: constants()->add (this);
	}
	Constants :: ~ Constants() {
		deleteAggregateObject (comments_);
	}

	// source :: Constants implementation
	bool
	Constants :: isConstant (const value :: Literal literal) const
	{
		if (constants_.contains (literal)) {
			return true;
		}
		if (previous_ != NULL) {
			return previous_->isConstant (literal);
		}
		return false;
	}
	const mm :: source :: Constants*
	Constants :: getPrevious () const {
		return previous_;
	}
	void
	Constants :: addTo (vector :: Literal& literalVector) const
	{
		for (index :: Literal i = 0; i < constants_.getSize(); ++ i ) {
			const value :: Literal
				constant = constants_.getValue (i);
			if (literalVector.contains (constant)) {
				throw new Error (location_, Error :: SEMANTIC, "duplicate constant declaration.");
			}
			literalVector.add (constant);
		}
	}

	// object :: Translatable implementation
	const object :: Targetive*
	Constants :: translate() const
	{
		const mm :: target :: Comments* const
			comments = dynamic_cast<const mm :: target :: Comments*>(comments_->translate());
		return new ast :: target :: Constant (&constants_, comments);
	}
	bool
	Constants :: isBlock() const {
		return false;
	}
	bool
	Constants :: isDisjoined() const {
		return false;
	}
	bool
	Constants :: isFloating() const {
		return false;
	}
	bool
	Constants :: isEssential() const {
		return false;
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Constants :: write (String& string) const
	{
		string << tab << mm :: Token :: constant_ << space;
		for (index :: Literal i = 0; i < constants_.getSize(); i++) {
			const value :: Literal constant = constants_.getValue (i);
			string << Table :: literals()->get (constant) << space;
		}
		string << mm :: Token :: end_ << endLine;
	}

	// object :: Object implementation
	void
	Constants :: commitSuicide() {
		delete this;
	}
	Size_t
	Constants :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (comments_);
		volume += location_.getVolume();
		volume += constants_.getVolume();
		return volume;
	}
	Size_t
	Constants :: getSizeOf() const {
		return sizeof (Constants);
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Constants :: checkSemanticCorrectness (const mm :: source :: Block* const block) const
	{
		const mm :: source :: Variables* const
			variables = block->getVariables();

		for (index :: Literal i = 0; i < constants_.getSize(); ++ i ) {
			const value :: Literal
				literal = constants_.getValue (i);
			if (previous_ != NULL && previous_->isConstant (literal)) {
				Error* error = new Error (location_, Error :: SEMANTIC, "duplicate constant declaration.");
				error->message() << "constant: " << Table :: literals()->get (literal);
				throw error;
			}
			if (variables != NULL && variables->isVariable (literal)) {
				Error* error = new Error (location_, Error :: SEMANTIC, "constant symbol previously was declared as a variable.");
				error->message() << "symbol: " << Table :: literals()->get (literal);
				throw error;
			}
		}
	}
}
}
}

#endif /*MM_AST_SOURCE_CONSTANTS_CPP_*/
