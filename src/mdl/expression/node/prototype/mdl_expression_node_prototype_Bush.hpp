/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_prototype_Bush.hpp                   */
/* Description:     represents a node of a bush (tree with a boolean flag)   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/expression/node/prototype/mdl_expression_node_prototype_Tree.hpp"

namespace mdl {
namespace expression {
namespace node {
namespace prototype {

template<class T, class N, template<class, class> class S, class A>
class Bush : public Tree<T, N, S, A> {
public :
	typedef T Term_;
	typedef N Node_;
	typedef A Allocator_;

	typedef Tree<Term_, Node_, S, Allocator_> Tree_;
	typedef
		typename iterator :: Forest<Node_>
		Iterator_;
	typedef
		typename iterator :: constant :: Forest<Node_>
		const_Iterator_;

	Bush
	(
		const Node_* const = NULL,
		const Direction = direction :: DEFAULT
	);
	Bush
	(
		const Symbol&,
		const bool,
		const Node_* const = NULL,
		const Direction = direction :: DEFAULT
	);
	~ Bush();

	Iterator_ getIterator();
	const_Iterator_ getIterator() const;

	bool isAccessible() const;
	void setAccessible (const bool = true);

	void operator = (const Symbol&);

	void showSymbol (String&) const;
	void showTerms (String&) const;
	void showBush (String&) const;
	void showBack (String&) const;
	static void showKind (String&);

	// object :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	void show (String&) const;
	void dump() const;

private :
	bool isAccessible_;
};

}
}
}
}


