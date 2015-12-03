#ifndef MM_AST_SOURCE_HYPOTHESIS_FLOATING_CPP_
#define MM_AST_SOURCE_HYPOTHESIS_FLOATING_CPP_

#include "auxiliary/mm_auxiliary.hpp"
#include "lexer/mm_lexer.hpp"
#include "ast/mm_ast.hpp"

namespace mm {
namespace ast {
namespace source {
namespace hypothesis {

	/****************************
	 *		Public members
	 ****************************/

	Floating :: Floating
	(
		const Location& location,
		const value :: Label label,
		const value :: Literal type,
		const value :: Literal variable,
		mm :: source :: Block* const block
	) :
	location_ (location),
	label_ (label),
	type_ (type, false),
	variable_ (variable, true),
	previous_ (block->getHypothesis())
	{
		block->pushHypothesis (this);
		checkSemanticCorrectness (block);
	}
	Floating :: ~ Floating() {
	}

using manipulator :: endLine;

	// source :: Hypothesis implementation
	bool
	Floating :: isRelevant (const vector :: Literal& variables) const {
		return variables.contains (variable_.getLiteral());
	}
	void
	Floating :: checkFloating
	(
		const Expression* expression,
		Substitution* const substitution
	) const
	{
		const Symbol&
			type = expression->getSymbol (0);

		if (type_ != type) {
			Error* error = new Error (location_, Error :: CHECKER);
			error->message() << "wrong type in floating hypothesis." << endLine;
			error->message() << "floating type: " << Table :: literals()->get (type_.getLiteral()) << endLine;
			error->message() << "expression type: " << Table :: literals()->get (type.getLiteral()) << endLine;
			error->message() << "expression: " << *expression << endLine;
			throw error;
		}
		substitution->add (variable_.getLiteral(), expression);
	}
	void
	Floating :: checkEssential (const stack :: Line*, const Substitution* const) const {
	}
	void
	Floating :: collectEssentialVariables (vector :: Literal&) const {
	}
	void
	Floating :: pushSelf (mm :: Stack* const stack, const stack :: Line* const) const
	{
		stack :: Line* line = stack->push();
		line->copyExpression (type_, variable_);
	}
	const mm :: target :: Step*
	Floating :: needDeclaration
	(
		const mm :: source :: Assertion* const assertion,
		const mm :: source :: Proof* const proof
	) const
	{
		const value :: Literal
			literal = variable_.getLiteral();
		if (!assertion->newVariable (literal)) {
			return NULL;
		}
		if (!proof->newVariable (literal)) {
			return NULL;
		}
		const mm :: target :: Typing* const
			variable = new ast :: target :: Variable (variable_, type_);
		return new ast :: target :: step :: Declaration (variable);
	}
	const mm :: source :: Hypothesis*
	Floating :: getPrevious() const {
		return previous_;
	}

	// object :: Expressive implementation
	bool
	Floating :: isEqual (const Expression* const expression) const
	{
		if (expression->getSize() != 2) {
			return false;
		}
		const Symbol& firstSymbol = expression->getSymbol (0);
		const Symbol& secondSymbol = expression->getSymbol (1);
		return
			(firstSymbol == type_) &&
			(secondSymbol == variable_);
	}
	void
	Floating :: assignTo (const Expression* const expression)
	{
		const_cast<Symbol&>(type_) = expression->getSymbol(0);
		const_cast<Symbol&>(variable_) = expression->getSymbol(1);
	}

	// object :: Labeled implementation
	value :: Label
	Floating :: getLabel() const {
		return label_;
	}

	// object :: Translatable implementation
	const object :: Targetive*
	Floating :: translate() const {
		return new ast :: target :: Variable (variable_, type_);
	}
	bool
	Floating :: isBlock() const {
		return false;
	}
	bool
	Floating :: isDisjoined() const {
		return false;
	}
	bool
	Floating :: isFloating() const {
		return true;
	}
	bool
	Floating :: isEssential() const {
		return false;
	}

using manipulator :: space;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Floating :: write (String& string) const
	{
		string << tab << Table :: hypothesisLabels()->get (label_) << space;
		string << mm :: Token :: floating_ << space << type_ << variable_;
		string << mm :: Token :: end_ << endLine;
	}

	// object :: Object implementation
	void
	Floating :: commitSuicide() {
		delete this;
	}
	Size_t
	Floating :: getVolume() const {
		return location_.getVolume();
	}
	Size_t
	Floating :: getSizeOf() const {
		return sizeof (Floating);
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Floating :: checkSemanticCorrectness (const mm :: source :: Block* const block) const
	{
		const mm :: source :: Variables* const
			variables = block->getVariables();
		//const mm :: source :: Constants* const
		//	constants = block->getConstants();

		const value :: Literal type = type_.getLiteral();
		//if (!constants->isConstant (type)) {;
		if (!Math :: constants()->contain (type)) {
			Error* error = new Error (location_, Error :: SEMANTIC);
			error->message() << "floating hypothesis first symbol is not a constant." << endLine;
			error->message() << tab << "symbol: " << Table :: literals()->get (type) << endLine;
			throw error;
		}

		const value :: Literal variable = variable_.getLiteral();
		if (!variables->isVariable (variable)) {
			Error* error = new Error (location_, Error :: SEMANTIC);
			error->message() << "floating hypothesis second symbol is not a variable." << endLine;
			error->message() << tab << "symbol: " << Table :: literals()->get (variable) << endLine;
			throw error;
		}
	}
}
}
}
}

#endif /*MM_AST_SOURCE_HYPOTHESIS_FLOATING_CPP_*/
