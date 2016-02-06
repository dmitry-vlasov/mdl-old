/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_iterator_constant_Tree.hpp                */
/* Description:     tree (2-dimensional) const iterator                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/expression/iterator/constant/mdl_expression_iterator_constant_Linear.hpp"

namespace mdl {
namespace expression {
namespace iterator {
namespace constant {

template<class N>
class Tree : public Linear<N> {
	typedef
		Linear<N>
		Ancestor_;
public :
	typedef
		typename Ancestor_ :: Node_
		Node_;

	Tree ();
	Tree (const Node_*);
	Tree (const typename iterator :: Tree<N>&);
	Tree (const Tree&);

	void operator +();
	void operator - ();

	void dump() const;
};

}
}
}
}


