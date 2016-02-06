/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_parse.hpp                                 */
/* Description:     expression parser module                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace expression {
namespace parse {

	typedef
		array :: Expression
		Expression_;
	typedef
		Expression_ :: Term_
		Term_;
	typedef
		Substitution<Term_>
		Substitution_;
	typedef
		tree :: Rule :: const_Iterator_
		tree_Iterator_;
	typedef
		Expression_ :: Iterator_
		expr_Iterator_;
}
}
}

#include "mdl/expression/parse/mdl_expression_parse_Parser.hpp"
#include "mdl/expression/parse/mdl_expression_parse_Result.hpp"
#include "mdl/expression/parse/mdl_expression_parse_Term.hpp"
#include "mdl/expression/parse/mdl_expression_parse_Tree.hpp"
#include "mdl/expression/parse/mdl_expression_parse_Unit.hpp"


