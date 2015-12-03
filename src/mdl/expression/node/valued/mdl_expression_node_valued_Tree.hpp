/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_valued_Tree.hpp                      */
/* Description:     value containing tree node                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_NODE_VALUED_TREE_HPP_
#define MDL_EXPRESSION_NODE_VALUED_TREE_HPP_

#include "mdl/expression/node/container/mdl_expression_node_container.hpp"
#include "mdl/expression/node/prototype/mdl_expression_node_prototype_Tree.hpp"
#include "mdl/expression/node/terms/mdl_expression_node_terms.hpp"
#include "mdl/expression/mdl_expression_Term.hpp"

namespace mdl {
namespace expression {
namespace node {
namespace valued {

template
<
	class V,
	template<class> class H,
	template<class, template<class> class, class> class S = container :: Singleton,
	class A = allocator :: Heap
>
class Tree :
	public prototype :: Tree
	<
		Term<Tree<V, H, S, A> >,
		Tree<V, H, S, A>,
		terms :: Branching, A
	> {
public :
	typedef V Value_;
	typedef A Allocator_;
	typedef S<Value_, H, Allocator_> Data_;
	typedef Tree<Value_, H, S, Allocator_> Node_;
	typedef Term<Node_> Term_;
	typedef
		typename prototype :: Tree
		<
			Term_, Node_,
			terms :: Branching, Allocator_
		>
		Tree_;
	typedef
		typename Tree_ :: Singleton_
		Singleton_;
	template<class A1>
	class Alternative {
	public :
		typedef A1 Allocator_;
		typedef
			Tree<Value_, H, S, Allocator_>
			Result_;
	};

	Tree
	(
		const Tree* const = NULL,
		const Direction = direction :: DEFAULT,
		const Value_ = Undefined<Value_> :: getValue()
	);
	Tree
	(
		const Symbol&,
		const Tree* const = NULL,
		const Direction = direction :: DEFAULT,
		const Value_ = Undefined<Value_> :: getValue()
	);
	~ Tree();

	template<class>
	Node_* cloneSelf() const;

	Data_& getData();
	const Data_& getData() const;

	Node_* getLeft();
	Node_* getRight();
	Node_* getUp();
	Node_* getDown();
	const Node_* getLeft() const;
	const Node_* getRight() const;
	const Node_* getUp() const;
	const Node_* getDown() const;

	Node_* goLeft();
	Node_* goRight();
	Node_* goUp();
	Node_* goDown();
	const Node_* goLeft() const;
	const Node_* goRight() const;
	const Node_* goUp() const;
	const Node_* goDown() const;

	void operator = (const Symbol&);

	void showSymbol (String&) const;
	void showTerms (String&) const;
	void showTree (String&) const;
	void showBack (String&) const;
	static void showKind (String&);

	// object :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	void show (String&) const;
	void dump() const;

private :
	Data_ data_;
};

	template
	<
		class V,
		template<class> class H,
		template<class, template<class> class, class> class S,
		class A
	>
	String&
	operator << (String&, const Tree<V, H, S, A>&);
}
}
}
}

#endif /*MDL_EXPRESSION_NODE_VALUED_TREE_HPP_*/
