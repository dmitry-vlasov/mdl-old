/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_expression_Substitution.cpp                           */
/* Description:     metamath substitution                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "expression/mm_expression_Substitution.hpp"

namespace mm {
namespace expression {

	/****************************
	 *		Public members
	 ****************************/

	const Expression*
	Substitution :: execute (const Expression* const argument) const
	{
		result_.clear();
		for (index :: Literal i = 0; i < argument->getSize(); i++)
		{
			const Symbol&
				symbol = argument->getSymbol (i);
			const index :: Arity
				index = variables_.find (symbol.getLiteral());

			if (index != index :: undefined :: LITERAL) {
				insertExpression (index);
			} else {
				result_.addSymbol (symbol);
			}
		}
		return &result_;
	}

	void
	Substitution :: checkDisjoinedRestrictions
	(
		const mm :: source :: Assertion* const assertion,
		const mm :: source :: Assertion* const theorem
	) const
	{
		if (variables_.isEmpty()) {
			return;
		}
		for (index :: Literal i = 0; i < variables_.getSize() - 1; i ++)
		{
			const value :: Literal
				var_1 = variables_ [i];
			const Expression* const
				exp_1 = expressions_ [i];

			for (index :: Literal j = i + 1; j < variables_.getSize(); j ++)
			{
				const value :: Literal
					var_2 = variables_ [j];
				const Expression* const
					exp_2 = expressions_ [j];

				if (assertion->areDisjoined (var_1, var_2)) {
					checkDisjoinedVariablesPair (exp_1, exp_2, theorem);
				}
			}
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Substitution :: insertExpression (const index :: Arity index) const
	{
		const Expression* const
			expression = expressions_ [index];

		// first member in expression is a type of the expression,
		// therefore it is skipped for substitution
		for (index :: Literal i = 1; i < expression->getSize(); i++) {
			const Symbol&
				symbol = expression->getSymbol (i);
			result_.addSymbol (symbol);
		}
	}

	void
	Substitution :: checkDisjoinedVariablesPair
	(
		const Expression* const exp_1,
		const Expression* const exp_2,
		const mm :: source :: Assertion* const theorem
	) const
	{
		for (index :: Literal p = 0; p < exp_1->getSize(); p ++)
		{
			const Symbol& symbol_1 = exp_1->getSymbol (p);
			if (!symbol_1.isVariable()) { continue; }
			const value :: Literal v_1 = symbol_1.getLiteral();

			for (index :: Literal q = 0; q < exp_2->getSize(); q ++)
			{
				const Symbol& symbol_2 = exp_2->getSymbol (q);
				if (!symbol_2.isVariable()) { continue; }
				const value :: Literal v_2 = symbol_2.getLiteral();

				checkSingleDisjoinedRestriction (exp_1, exp_2, v_1, v_2, theorem);
			}
		}
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	void
	Substitution :: checkSingleDisjoinedRestriction
	(
		const Expression* const exp_1,
		const Expression* const exp_2,
		const value :: Literal v_1,
		const value :: Literal v_2,
		const mm :: source :: Assertion* const theorem
	) const
	{
		if (v_1 == v_2) {
			Error* error = new Error (Error :: CHECKER);
			error->message() << "disjoint variables" << space;
			error->message() << Table :: literals()->get (v_1) << " and ";
			error->message() << Table :: literals()->get (v_2) << space;
			error->message() << "violation:" << endLine;
			throwDisjoinedViolationError (exp_1, exp_2, v_1, v_2, error);
		}
		if (!theorem->areDisjoined (v_1, v_2)) {
			Error* error = new Error (Error :: CHECKER);
			error->message() << "variables" << space;
			error->message() << Table :: literals()->get (v_1) << " and ";
			error->message() << Table :: literals()->get (v_2) << space;
			error->message() << "are not inherently disjoint:" << endLine;
			throwDisjoinedViolationError (exp_1, exp_2, v_1, v_2, error);
		}
	}
	void
	Substitution :: throwDisjoinedViolationError
	(
		const Expression* const exp_1,
		const Expression* const exp_2,
		const value :: Literal var_1,
		const value :: Literal var_2,
		Error* error
	) const
	{
		error->message() << "expression 1: " << endLine;
		error->message() << *exp_1  << endLine;
		error->message() << "expression 2: " << endLine;
		error->message() << *exp_2  << endLine;
		error->message() << "disjoint variables: " << endLine;
		error->message() << Table :: literals()->get (var_1);
		error->message() << " and ";
		error->message() << Table :: literals()->get (var_2);
		error->message() << endLine;
		throw error;
	}
}
}


