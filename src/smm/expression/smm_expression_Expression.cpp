/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_expression_Expression.cpp                            */
/* Description:     smm symbolic expression                                  */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "smm/math/smm_math.hpp"
#include "smm/expression/smm_expression.hpp"

namespace smm {
namespace expression {

	/****************************
	 *		Public members
	 ****************************/

	Expression :: Expression
	(
		const Location& location,
		const smm :: vector :: Literal& expression
	) :
	expression_ (expression.getSize())
	{
		for (index :: Literal index = 0; index < expression.getSize(); ++ index) {
			Symbol& symbol = expression_.push ();
			const value :: Literal literal = expression.getValue (index);
			symbol.setLiteral (literal);
			const bool isConstant = Math :: constants()->contain (literal);
			symbol.setVariable (!isConstant);
		}
	}
	Expression :: ~ Expression() {
	}
}
}


