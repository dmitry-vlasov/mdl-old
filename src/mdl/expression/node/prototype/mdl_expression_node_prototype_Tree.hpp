/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_prototype_Tree.hpp                   */
/* Description:     represents a tree node (2-dimensional)                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/expression/node/prototype/mdl_expression_node_prototype_List.hpp"

namespace mdl {
namespace expression {
namespace node {
namespace prototype {

template<class T, class N, template<class, class> class S, class A>
class Tree : public List<T, N, S, A> {
public :
	typedef T Term_;
	typedef N Node_;
	typedef A Allocator_;

	typedef List<Term_, Node_, S, Allocator_> List_;
	typedef
		typename List_ :: Singleton_
		Singleton_;
	typedef
		typename iterator :: Tree<Node_>
		Iterator_;
	typedef
		typename iterator :: constant :: Tree<Node_>
		const_Iterator_;
	enum {
		IS_ITERABLE_FORTH = false,
		IS_ITERABLE_BACK = true
	};

	Tree
	(
		const Node_* const = NULL,
		const Direction = direction :: DEFAULT
	);
	Tree
	(
		const Symbol&,
		const Node_* const = NULL,
		const Direction = direction :: DEFAULT
	);
	~ Tree();

	void deleteNodes() const;

	Iterator_ getIterator();
	const_Iterator_ getIterator() const;

	Node_* getLeft (Node_*);
	Node_* getRight (Node_*);
	Node_* getUp();
	Node_* getDown();

	const Node_* getLeft (const Node_*) const;
	const Node_* getRight (const Node_*) const;
	const Node_* getUp() const;
	const Node_* getDown() const;

	const Node_* goLeft (const Node_*) const;
	const Node_* goRight (const Node_*) const;
	const Node_* goUp() const;
	const Node_* goDown() const;

	void operator = (const Symbol&);

	template<Direction>
	bool isTerminal () const;

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

protected :
	Node_* goLeft (Node_*);
	Node_* goRight (Node_*);
	Node_* goUp (Node_*);
	Node_* goDown (Node_*);

	mutable Node_* up_;
	mutable Node_* down_;
};

	template<class T, class N, template<class, class> class S, class A>
	String&
	operator << (String&, const Tree<T, N, S, A>&);
}
}
}
}


