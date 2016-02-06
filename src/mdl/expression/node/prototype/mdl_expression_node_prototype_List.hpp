/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_prototype_List.hpp                   */
/* Description:     represents a node of a list (1-dimensional)              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/expression/node/prototype/mdl_expression_node_prototype_Singleton.hpp"

namespace mdl {
namespace expression {
namespace node {
namespace prototype {

template<class T, class N, template<class, class> class S, class A>
class List : public Singleton<T, N, S, A> {
public :
	typedef T Term_;
	typedef N Node_;
	typedef A Allocator_;
	typedef
		Singleton<Term_, Node_, S, Allocator_>
		Singleton_;
	typedef
		typename iterator :: modifier :: Lintree
		<
			iterator :: Linear<Node_>
		>
		Iterator_;
	typedef
		typename iterator :: modifier :: Lintree
		<
			iterator :: constant :: Linear<Node_>
		>
		const_Iterator_;
	enum {
		IS_ITERABLE_FORTH = true,
		IS_ITERABLE_BACK = true
	};

	List
	(
		const Node_* const = NULL,
		const Direction = direction :: DEFAULT
	);
	List
	(
		const Symbol&,
		const Node_* const = NULL,
		const Direction = direction :: DEFAULT
	);
	~ List();

	void deleteNodes() const;

	Iterator_ getIterator();
	const_Iterator_ getIterator() const;

	Node_* getLeft (Node_*);
	Node_* getRight (Node_*);
	const Node_* getLeft (const Node_*) const;
	const Node_* getRight (const Node_*) const;

	const Node_* goLeft (const Node_*) const;
	const Node_* goRight (const Node_*) const;
	void setLeft (const Node_*) const;
	void setRight (const Node_*) const;

	void operator = (const Symbol&);

	template<Direction>
	void link (const Node_*);
	template<Direction>
	bool isTerminal () const;

	void showSymbol (String&) const;
	void showTerms (String&) const;
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

	mutable Node_* left_;
	mutable Node_* right_;
};

}
}
}
}


