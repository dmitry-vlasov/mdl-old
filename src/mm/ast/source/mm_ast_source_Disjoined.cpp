/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_source_Disjoined.cpp                              */
/* Description:     metamath disjoined variables                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_SOURCE_DISJOINED_CPP_
#define MM_AST_SOURCE_DISJOINED_CPP_

#include "auxiliary/mm_auxiliary.hpp"
#include "lexer/mm_lexer.hpp"
#include "ast/mm_ast.hpp"

namespace mm {
namespace ast {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	Disjoined :: Disjoined
	(
		const Location& location,
		const vector :: Literal& variables,
		mm :: source :: Block* const block
	) :
	location_ (location),
	variables_ (variables),
	previous_ (block->getDisjoined())
	{
		block->pushDisjoined (this);
		checkSemanticCorrectnes (block);
	}
	Disjoined :: Disjoined
	(
		const mm :: source ::Disjoined* disjoined,
		const vector :: Literal& variables
	) :
	location_ (dynamic_cast<const Disjoined*>(disjoined)->location_),
	variables_ (2),
	previous_
	(
		(dynamic_cast<const Disjoined*>(disjoined)->previous_ == NULL) ?
		NULL :
		new ast :: source :: Disjoined (dynamic_cast<const Disjoined*>(disjoined)->previous_, variables)
	)
	{
		const vector :: Literal&
			literals = dynamic_cast<const Disjoined*>(disjoined)->variables_;
		for (index :: Arity i = 0; i < literals.getSize(); ++ i) {
			const value :: Literal variable = literals.getValue (i);
			if (variables.contains (variable)) {
				const_cast<vector :: Literal&>(variables_).add (variable);
			}
		}
	}
	Disjoined :: ~ Disjoined() {
	}

	// source :: Disjointed implementation
	bool
	Disjoined :: areDisjoined
	(
		const value :: Literal variable_1,
		const value :: Literal variable_2
	) const
	{
		const bool areDisjoined =
			variables_.contains (variable_1) &&
			variables_.contains (variable_2);
		if (areDisjoined) {
			return true;
		}
		if (previous_ != NULL) {
			return previous_->areDisjoined (variable_1, variable_2);
		}
		return false;
	}
	const mm :: source :: Disjoined*
	Disjoined :: getPrevious() const {
		return previous_;
	}

	// object :: Translatable implementation
	const object :: Targetive*
	Disjoined :: translate() const {
		return new ast :: target :: Disjoined (&variables_);
	}
	bool
	Disjoined :: isBlock() const {
		return false;
	}
	bool
	Disjoined :: isDisjoined() const {
		return true;
	}
	bool
	Disjoined :: isFloating() const {
		return false;
	}
	bool
	Disjoined :: isEssential() const {
		return false;
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Writable implementation
	void
	Disjoined :: write (String& string) const
	{
		if (variables_.getSize() < 2) {
			return;
		}
		string << tab << mm :: Token :: disjoined_ << space;
		for (index :: Literal i = 0; i < variables_.getSize(); i++) {
			const value :: Literal variable = variables_ [i];
			string << Table :: literals()->get (variable) << space;
		}
		string << mm :: Token :: end_ << endLine;
	}

	// object :: Object implementation
	void
	Disjoined :: commitSuicide() {
		delete this;
	}
	Size_t
	Disjoined :: getVolume () const
	{
		Size_t volume = 0;
		volume += location_.getVolume();
		volume += variables_.getVolume();
		return volume;
	}
	Size_t
	Disjoined :: getSizeOf() const {
		return sizeof (Disjoined);
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Disjoined :: checkSemanticCorrectnes (const mm :: source :: Block* const block) const
	{
		const mm :: source :: Variables* const
			variables = block->getVariables();
		for (index :: Literal i = 0; i < variables_.getSize(); ++ i) {
			const value :: Literal literal = variables_ [i];
			if (!variables->isVariable (literal)) {
				Error* error = new Error (location_, Error :: SEMANTIC, "disjoined symbol must be variable.");
				error->message() << "symbol: " << Table :: literals()->get (literal);
				throw error;
			}
		}
	}
}
}
}

#endif /*MM_AST_SOURCE_DISJOINED_CPP_*/
