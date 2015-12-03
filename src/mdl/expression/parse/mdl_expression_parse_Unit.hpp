/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_parse_Unit.hpp                            */
/* Description:     expression parser unit: pair of iterators& substitutiuon */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_PARSE_UNIT_HPP_
#define MDL_EXPRESSION_PARSE_UNIT_HPP_

#include "mdl/expression/iterator/mdl_expression_iterator.hpp"
#include "mdl/expression/parse/mdl_expression_parse_Parser.hpp"

namespace mdl {
namespace expression {
namespace parse {

class Unit : public
	iterator :: modifier :: Pair
	<
		expr_Iterator_,
		tree_Iterator_
	> {
public :
	typedef
		iterator :: modifier :: Pair
		<
			expr_Iterator_,
			tree_Iterator_
		>
		Pair_;

	Unit
	(
		Parser* parser,
		const expr_Iterator_&,
		const tree_Iterator_&,
		const Tree*,
		const value :: Integer depth
	);
	Unit (const Unit&);

	bool isConstant() const;
	bool isVariable() const;

	enum State {
		DEADLOCK,
		FINAL,
		TERMINAL,
		TRANSIT
	};
	State getState() const;

	void operator ++ ();
	void operator + ();
	void operator - ();

	const Symbol& getTreeSymbol() const;
	const mdl :: Type* getTreeType() const;
	const mdl :: Type* getExprType() const;
	const mdl :: Rule* getTreeRule() const;

	expr_Iterator_ getBegin() const;
	expr_Iterator_ getEnd() const;
	const Tree* getTree() const;
	void setEnd (const expr_Iterator_);
	void setTree (const Tree*);

	const Substitution_* getSubstitution() const;
	void newSubstitution (const Term_*);

	const Tree* newRuleTerm (const mdl :: Type*);
	const Tree* newVarTerm (const mdl :: Type*);

	value :: Integer getExpressionLength() const;
	value :: Integer getTreeLength() const;
	value :: Integer getDepth() const;

	void show (String&) const;
	void dump() const;

private :
	void showExpression (String&) const;
	void showTreeBranch (String&) const;

	Parser*        parser_;
	expr_Iterator_ begin_;
	tree_Iterator_ root_;
	Substitution_* substitution_;
	const Tree*    tree_;
	const value :: Integer depth_;
};

	String&
	operator << (String&, const Unit&);
	std :: ostream&
	operator << (std :: ostream&, const Unit&);
}
}
}

#endif /*MDL_EXPRESSION_PARSE_UNIT_HPP_*/
