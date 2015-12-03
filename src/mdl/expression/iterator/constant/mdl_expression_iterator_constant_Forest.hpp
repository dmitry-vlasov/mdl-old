/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_iterator_constant_Forest.hpp              */
/* Description:     forst (set of trees) const iterator                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_ITERATOR_CONSTANT_FOREST_HPP_
#define MDL_EXPRESSION_ITERATOR_CONSTANT_FOREST_HPP_

#include "mdl/expression/iterator/constant/mdl_expression_iterator_constant_Tree.hpp"

namespace mdl {
namespace expression {
namespace iterator {
namespace constant {

template<class N>
class Forest : public Tree<N> {
	typedef
		Tree<N>
		Ancestor_;
public :
	typedef
		typename Ancestor_ :: Node_
		Node_;

	Forest ();
	Forest (const Node_*);
	Forest (const typename iterator :: Forest<N>&);
	Forest (const Forest&);

	bool isReacheable (const index :: Step) const;
};

}
}
}
}

#endif /*MDL_EXPRESSION_ITERATOR_CONSTANT_FOREST_HPP_*/
