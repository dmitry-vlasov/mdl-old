/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_prototype_Forest.hpp                 */
/* Description:     represents a node of a forest (monotonous set of trees)  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_NODE_PROTOTYPE_FOREST_HPP_
#define MDL_EXPRESSION_NODE_PROTOTYPE_FOREST_HPP_

#include "mdl/expression/node/prototype/mdl_expression_node_prototype_Tree.hpp"

namespace mdl {
namespace expression {
namespace node {
namespace prototype {

template<class T, class N, template<class, class> class S, class A>
class Forest : public Tree<T, N, S, A> {
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

	Forest
	(
		const Node_* const = NULL,
		const Direction = direction :: DEFAULT
	);
	Forest
	(
		const Symbol&,
		const index :: Step,
		const Node_* const = NULL,
		const Direction = direction :: DEFAULT
	);
	~ Forest();

	Iterator_ getIterator();
	const_Iterator_ getIterator() const;

	index :: Step getLevel() const;
	void setLevel (const index :: Step);
	bool isReacheable (const index :: Step) const;

	void operator = (const Symbol&);

	void showSymbol (String&) const;
	void showTerms (String&) const;
	void showForest (String&) const;
	void showBack (String&) const;
	static void showKind (String&);

	// object :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	void show (String&) const;
	void dump() const;

private :
	index :: Step level_;
};

}
}
}
}

#endif /*MDL_EXPRESSION_NODE_PROTOTYPE_FOREST_HPP_*/
