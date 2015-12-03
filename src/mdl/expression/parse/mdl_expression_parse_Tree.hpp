/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_parse_Tree.hpp                            */
/* Description:     tree of expression terms for parser (subexpression)      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_PARSE_TREE_HPP_
#define MDL_EXPRESSION_PARSE_TREE_HPP_

#include "mdl/interface/mdl_interface.dpp"

namespace mdl {
namespace expression {
namespace parse {

class Tree : public Scalar<Tree, allocator :: Stack> {
public :
	Tree
	(
		const Term_* term,
		const bool   initial,
		const bool   final,
		const Tree*  next = NULL
	);

	void confirm() const;
	bool isInitial() const;
	bool isFinal() const;
	bool isTop() const;
	const Term_* getTerm() const;

	void show (String&) const;

private :
	const Term_* term_;
	const bool   initial_;
	const bool   final_;
	const Tree*  next_;
};

}
}
}

#endif /*MDL_EXPRESSION_PARSE_TREE_HPP_*/
