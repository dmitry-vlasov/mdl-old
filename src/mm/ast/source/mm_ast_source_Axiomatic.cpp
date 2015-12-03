/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_source_Axiomatic.cpp                              */
/* Description:     metamath axiomatic assertion                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_SOURCE_AXIOMATIC_CPP_
#define MM_AST_SOURCE_AXIOMATIC_CPP_

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

	Axiomatic :: Axiomatic
	(
		const Location& location,
		const value :: Label label,
		const vector :: Literal& literalVector,
		mm :: source :: Block* const block,
		const mm :: source :: Comments* comments
	) :
	Assertion (location, label, literalVector, block, comments) {
		Math :: assertions()->add (this);
	}
	Axiomatic :: ~ Axiomatic()
	{
		const mm :: source :: Disjoined*
			disjoined = disjoined_;
		while (disjoined != NULL) {
			const mm :: source :: Disjoined*
				previous = disjoined->getPrevious();
			deleteAggregateObject (disjoined);
			disjoined = previous;
		}
	}

	// source :: Assertion implementation
	inline void
	Axiomatic :: applyCheck (Stack* const stack) const {
		Assertion :: applyCheck (stack);
	}
	inline const mm :: target :: Step*
	Axiomatic :: applyTranslate (Stack* const stack) const {
		return Assertion :: applyTranslate (stack);
	}
	inline bool
	Axiomatic :: areDisjoined
	(
		const value :: Literal variable_1,
		const value :: Literal variable_2
	) const
	{
		return Assertion :: areDisjoined (variable_1, variable_2);
	}
	inline void
	Axiomatic :: checkDisjoined (const mm :: source :: Assertion* const theorem) const {
		Assertion :: checkDisjoined (theorem);
	}
	inline bool
	Axiomatic :: newVariable (const value :: Literal variable) const {
		return Assertion :: newVariable (variable);
	}
	bool
	Axiomatic :: isAxiomatic() const {
		return true;
	}
	bool
	Axiomatic :: isProvable() const {
		return false;
	}
	bool
	Axiomatic :: isVerified() const {
		return true;
	}

	// object :: Expressive implementation
	inline bool
	Axiomatic :: isEqual (const mm :: Expression* const expression) const {
		return Assertion :: isEqual (expression);
	}
	inline void
	Axiomatic :: assignTo (const mm :: Expression* const expression) {
		Assertion :: assignTo (expression);
	}

	// object :: Labeled implementation
	inline value :: Label
	Axiomatic :: getLabel() const {
		return Assertion :: getLabel();
	}

	// object :: Verifiable implementation
	void
	Axiomatic :: check() const {
	}

	// object :: Translatable implementation
	const object :: Targetive*
	Axiomatic :: translate() const
	{
		const mm :: target :: Comments* const
			comments = dynamic_cast<const mm :: target :: Comments*>(comments_->translate());
		const mm :: target :: Variables* const
			variables = translateVariables();
		const mm :: target :: Disjoineds* const
			disjoineds = translateDisjoineds (true);

		if (isStatement()) {
			mm :: target :: Statement* statement = NULL;
			if (isDefinition()) {
				statement = new ast :: target :: Definition (label_, variables, disjoineds, comments
				);
			} else {
				statement = new ast :: target :: Axiom (label_, variables, disjoineds, comments);
			}
			translateDefinition (statement);
			translateHypothesis (statement);
			translateProposition (statement);
			return statement;
		}
		if (isSuperType ()) {
			mm :: target :: Syntactic* const
				super = new ast :: target :: Super (label_, variables, disjoineds, comments);
			translateTerm (super);
			return super;
		} else {
			mm :: target :: Syntactic* const
				rule = new ast :: target :: Rule (label_, variables, disjoineds, comments);
			translateTerm (rule);
			return rule;
		}
	}
	inline bool
	Axiomatic :: isBlock() const {
		return Assertion :: isBlock();
	}
	inline bool
	Axiomatic :: isDisjoined() const {
		return Assertion :: isDisjoined();
	}
	inline bool
	Axiomatic :: isFloating() const {
		return Assertion :: isFloating();
	}
	inline bool
	Axiomatic :: isEssential() const {
		return Assertion :: isEssential();
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Axiomatic :: write (String& string) const
	{
		string << tab << Table :: assertionLabels()->get (label_) << space;
		string << mm :: Token :: axiomatic_ << space;
		string << *proposition_;
		string << mm :: Token :: end_ << endLine;
	}

	// object :: Object implementation
	void
	Axiomatic :: commitSuicide() {
		delete this;
	}
	Size_t
	Axiomatic :: getVolume() const
	{
		Size_t volume = 0;
		volume += Assertion :: getVolume();
		const mm :: source :: Disjoined*
			disjoined = disjoined_;
		while (disjoined != NULL) {
			volume += getAggregateVolume (disjoined);
			disjoined = disjoined->getPrevious();
		}
		return volume;
	}
	Size_t
	Axiomatic :: getSizeOf() const {
		return sizeof (Axiomatic);
	}
}
}
}

#endif /*MM_AST_SOURCE_AXIOMATIC_CPP_*/
