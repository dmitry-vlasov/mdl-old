/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_List.hpp                             */
/* Description:     list expression node                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_NODE_LIST_HPP_
#define MDL_EXPRESSION_NODE_LIST_HPP_

#include "mdl/expression/node/prototype/mdl_expression_node_prototype_List.hpp"
#include "mdl/expression/node/terms/mdl_expression_node_terms.hpp"
#include "mdl/expression/mdl_expression_Term.hpp"

namespace mdl {
namespace expression {
namespace node {

template<class A = allocator :: Heap>
class List :
	public prototype :: List
	<
		Term<List<A> >,
		List<A>,
		terms :: Linear, A
	> {
public :
	typedef A Allocator_;
	typedef List<Allocator_> Node_;
	typedef Term<Node_> Term_;
	typedef
		typename prototype :: List
		<
			Term_, Node_,
			terms :: Linear, Allocator_
		>
		List_;
	template<class A1>
	class Alternative {
	public :
		typedef A1 Allocator_;
		typedef
			List<Allocator_>
			Result_;
	};

	List (const List&);
	List
	(
		const List* const = NULL,
		const Direction = direction :: DEFAULT
	);
	List
	(
		const Symbol&,
		const List* const = NULL,
		const Direction = direction :: DEFAULT
	);
	~ List();

	template<class>
	Node_* cloneSelf() const;

	Node_* getLeft();
	Node_* getRight();
	const Node_* getLeft() const;
	const Node_* getRight() const;

	Node_* goLeft();
	Node_* goRight();
	const Node_* goLeft() const;
	const Node_* goRight() const;

	void setLeft (const Node_*) const;
	void setRight (const Node_*) const;

	void operator = (const Symbol&);

	void showSymbol (String&) const;
	void showTerms (String&) const;
	void showBack (String&) const;

	// object :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	void show (String&) const;
	void dump() const;
};

}
}
}

#endif /*MDL_EXPRESSION_NODE_LIST_HPP_*/
