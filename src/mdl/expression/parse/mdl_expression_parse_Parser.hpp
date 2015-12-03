/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_parse_Parser.hpp                          */
/* Description:     static class: expression parser                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_PARSE_PARSER_HPP_
#define MDL_EXPRESSION_PARSE_PARSER_HPP_

#include "mdl/expression/parse/mdl_expression_parse_Unit.hpp"
#include "mdl/expression/parse/mdl_expression_parse_Result.hpp"

namespace mdl {
namespace expression {
namespace parse {

class Parser {
public :
	Parser (Expression_*);

	bool proceed
	(
		const mdl :: Type* const type,
		const bool deep = false,
		const bool final = false
	);

private :
	friend class Unit;

	Result parseVariable (expr_Iterator_, const mdl :: Type*);
	Result parseTerm (expr_Iterator_, const mdl :: Type*, const Tree* = NULL, const value :: Integer depth = 0);
	Result parseTerm (Unit, const mdl :: Type*);
	Result parseNode (Unit, const mdl :: Type*);

	Result tryConstant (Unit, const mdl :: Type*);
	Result tryVariable (Unit, const mdl :: Type*);
	Result tryType (Unit, const mdl :: Type*, const mdl :: Type*);
	Result tryRule (Unit, const mdl :: Type*, const mdl :: Type*);
	Result tryTerm (Unit, const mdl :: Type*, const Tree*);
	Result tryVar (Unit, const mdl :: Type*, const mdl :: Type*);

	Result parseNext (Unit, const mdl :: Type*);

	bool deep_;
	bool final_;
	Expression_* expression_;
};

}
}
}

#endif /*MDL_EXPRESSION_PARSE_PARSER_HPP_*/
