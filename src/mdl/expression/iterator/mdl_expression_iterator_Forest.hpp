/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_iterator_Forest.hpp                       */
/* Description:     forst (set of trees) iterator                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/expression/iterator/mdl_expression_iterator_Tree.hpp"

namespace mdl {
namespace expression {
namespace iterator {

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
	Forest (Node_*);
	Forest (const Forest&);

	bool isReacheable (const index :: Step) const;

	void dump() const;
};

}
}
}


