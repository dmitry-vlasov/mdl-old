/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_parse_Parser.ipp                          */
/* Description:     static class: expression parser                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_PARSE_PARSER_IPP_
#define MDL_EXPRESSION_PARSE_PARSER_IPP_

#include "mdl/expression/parse/mdl_expression_parse_Unit.ipp"

namespace mdl {
namespace expression {
namespace parse {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Parser :: Parser (Expression_* expression) :
	expression_ (expression),
	deep_ (false),
	final_ (false) {
	}

	inline bool
	Parser :: proceed
	(
		const mdl :: Type* const type,
		const bool deep,
		const bool final
	)
	{
		deep_ = deep;
		final_ = final;
		if (expression_->isEmpty()) {
			Error* error = new Error (Error :: SEMANTIC);
			error->message() << "expression fails parsing:" << endLine;
			error->message() << tab << "empty expression." << endLine;
			throw error;
		}
		const expr_Iterator_ begin = expression_->getBegin();

		const Result result =
			(expression_->isVariable()) ?
			parseVariable (begin, type) :
			parseTerm (begin, type);

		bool success = false;
		try {
			success = result.confirm();
		} catch (Error* error) {
			error->message() << "expression: " << *expression_ << endLine;
			throw error;
		}
		return success;
	}

	/****************************
	 *		Private members
	 ****************************/


	inline Result
	Parser :: parseVariable (expr_Iterator_ begin, const mdl :: Type* type)
	{
		if (begin->getType() != type) {
			Error* error = new Error (Error :: SEMANTIC);
			error->message() << "variable expression fails parsing:" << endLine;
			error->message() << tab << "type of a variable differs a the type of the expression." << endLine;
			throw error;
		}
		const Term_*
			term = Term_ :: create<allocator :: Stack> (begin, type);
		const Tree* tree = new Tree (term, true, true);
		return Result (tree, final_);
	}
	inline Result
	Parser :: parseTerm
	(
		expr_Iterator_ begin,
		const mdl :: Type* type,
		const Tree* tree,
		const value :: Integer depth
	)
	{
		const tree :: Rule* rules = type->getRuleTree();
		if (rules == NULL) {
			return Result();
		}
		Unit unit (this, begin, rules->getBegin(), tree, depth);
		return parseNode (unit, type);
	}
	inline Result
	Parser :: parseTerm (Unit unit, const mdl :: Type* type)
	{
		const expr_Iterator_ begin = unit.getEnd();
		const Tree* tree = unit.getTree();
		return parseTerm (begin, type, tree, unit.getDepth() + 1);
	}
	Result
	Parser :: parseNode (Unit unit, const mdl :: Type* type)
	{
		Result result;
		while (unit != NULL) {
			result.join (tryConstant (unit, type));
			if (!deep_ && result.isObtained()) {
				return result;
			}
			+ unit;
		}
		unit.recall();
		while (unit != NULL) {
			result.join (tryVariable (unit, type));
			if (!deep_ && result.isObtained()) {
				return result;
			}
			+ unit;
		}
		return result;
	}

	Result
	Parser :: tryConstant (Unit unit, const mdl :: Type* type)
	{
		if (!unit.isConstant()) {
			return Result();
		}
		if (!unit.isEqual()) {
			return Result();
		}
		return parseNext (unit, type);
	}
	Result
	Parser :: tryVariable (Unit unit, const mdl :: Type* type)
	{
		if (!unit.isVariable()) {
			return Result();
		}
		const mdl :: Type* localType = unit.getTreeType();
		Result result = tryType (unit, type, localType);
		if (!deep_ && result.isObtained()) {
			return result;
		}
		for (index :: Type i = 0; i < localType->getInferCount(); ++ i) {
			const mdl :: Type* localSubtype = localType->getInfer (i);
			result.join (tryType (unit, type, localSubtype));
			if (!deep_ && result.isObtained()) {
				return result;
			}
		}
		return result;
	}
	Result
	Parser :: tryType (Unit unit, const mdl :: Type* type, const mdl :: Type* localType)
	{
		Result result;
		result.join (tryRule (unit, type, localType));
		if (!deep_ && result.isObtained()) {
			return result;
		}
		result.join (tryVar (unit, type, localType));
		if (!deep_ && result.isObtained()) {
			return result;
		}
		return result;
	}
	Result
	Parser :: tryRule (Unit unit, const mdl :: Type* type, const mdl :: Type* localType)
	{
		Result result;
		const Result
			subterms = parseTerm (unit, localType);
		const typename Result :: Node_*
			node = subterms.getList().getFirst();
		while (node != NULL) {
			const Tree* tree = node->getValue();
			result.join (tryTerm (unit, type, tree));
			if (!deep_ && result.isObtained()) {
				return result;
			}
			node = node->getNext();
		}
		return result;
	}
	inline Result
	Parser :: tryTerm (Unit unit, const mdl :: Type* type, const Tree* tree)
	{
		const Term_* term = tree->getTerm();
		unit.newSubstitution (term);
		unit.setEnd (const_cast<Term_*>(term)->getEnd());
		unit.setTree (tree);
		return parseNext (unit, type);
	}
	inline Result
	Parser :: tryVar (Unit unit, const mdl :: Type* type, const mdl :: Type* localType)
	{
		if (unit.getExprType() != localType) {
			return Result();
		}
		unit.newVarTerm (localType);
		return parseNext (unit, type);
	}

	Result
	Parser :: parseNext (Unit unit, const mdl :: Type* type)
	{
		switch (unit.getState()) {
		case Unit :: TRANSIT :
			++ unit;
			return parseNode (unit, type);
		case Unit :: FINAL :
			return Result (unit.newRuleTerm (type), final_);
		case Unit :: TERMINAL :
			return Result (unit.newRuleTerm (type), final_);
		case Unit :: DEADLOCK :
			return Result();
		}
		return Result();
	}
}
}
}

#endif /*MDL_EXPRESSION_PARSE_PARSER_IPP_*/
