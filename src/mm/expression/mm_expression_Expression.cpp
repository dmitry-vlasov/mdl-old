/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_expression_Expression.cpp                             */
/* Description:     metamath symbolic expression                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_EXPRESSION_EXPRESSION_CPP_
#define MM_EXPRESSION_EXPRESSION_CPP_

#include "math/mm_math.hpp"
#include "ast/mm_ast.hpp"
#include "expression/mm_expression_Expression.hpp"

namespace mm {
namespace expression {

	/****************************
	 *		Public members
	 ****************************/

using manipulator :: tab;
using manipulator :: endLine;

	Expression :: Expression
	(
		const Location& location,
		const mm :: vector :: Literal& expression,
		const mm :: source :: Block* const block
	) :
	expression_ (expression.getSize())
	{
		const mm :: source :: Variables* const
			variables = block->getVariables();
		//const mm :: source :: Constants* const
		//	constants = block->getConstants();

		for (index :: Literal index = 0; index < expression.getSize(); index++) {
			Symbol& symbol = expression_.push ();
			const value :: Literal literal = expression.getValue (index);
			symbol.setLiteral (literal);
			const bool isVariable =
				(variables == NULL) ?
				false :
				variables->isVariable (literal);

			//const bool isConstant = constants->isConstant (literal);
			const bool isConstant = Math :: constants()->contain (literal);

			if (!isVariable && !isConstant) {
				Error* error = new Error (location, Error :: SEMANTIC);
				error->message() << "symbol ";
				error->message() << Table :: literals()->get (literal);
				error->message() << " is not declared." << endLine;
				throw error;
			}
			symbol.setVariable (isVariable);
		}
	}
	Expression :: ~ Expression() {
	}

	void
	Expression :: collectVariables (mm :: vector :: Literal& variables) const
	{
		for (index :: Literal i = 0; i < expression_.getSize(); ++ i) {
			const Symbol& symbol = expression_.getReference (i);
			if (symbol.isVariable() && !variables.contains(symbol.getLiteral())) {
				variables.add (symbol.getLiteral());
			}
		}
	}
	bool
	Expression :: isStatement() const
	{
		const value :: Literal
			firstLiteral = getSymbol (0).getLiteral();
		return (firstLiteral == Math :: constants()->turnstile());
	}

using manipulator :: space;

	void
	Expression :: write (String& string) const {
		string << expression_;
	}
	void
	Expression :: writeType (String& string) const
	{
		if (isStatement()) {
			const value :: Literal
				wff = Math :: constants()->wff();
			string << Table :: literals()->get (wff) << space;
		} else {
			string << getType();
		}
	}
	void
	Expression :: writeBody (String& string) const
	{
		// first symbol is not translated because it declares a type of the expression
		for (index :: Literal index = 1; index < expression_.getSize(); index++) {
			const Symbol& symbol = expression_.getReference (index);
			string << symbol;
		}
	}
}
}

#endif /* MM_EXPRESSION_EXPRESSION_CPP_ */
