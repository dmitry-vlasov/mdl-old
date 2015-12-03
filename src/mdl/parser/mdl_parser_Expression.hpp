/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_parser_Expression.hpp                                */
/* Description:     expression parser                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PARSER_EXPRESSION_HPP_
#define MDL_PARSER_EXPRESSION_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/lexer/mdl_lexer.hpp"
#include "mdl/parser/mdl_parser.dpp"

namespace mdl {
namespace parser {

class Expression :
	public object :: Object,
	public Scalar<Expression> {
public :
	Expression (const bool variablesAreReplaceable = true);
	virtual ~ Expression();

	array :: Expression* parse (Lexer*, const bool create = true);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	// internal part
	const bool variablesAreReplaceable_;

	// external part
	vector :: value :: Literal literalVector_;

	enum {
		INITIAL_LITERAL_VECTOR_CAPACITY = 256
	};
};

}
}

#endif /*MDL_PARSER_EXPRESSION_HPP_*/
