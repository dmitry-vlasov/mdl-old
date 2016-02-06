/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_iterator_Tree.hpp                         */
/* Description:     tree (2-dimensional) iterator                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/expression/iterator/mdl_expression_iterator_Linear.hpp"

namespace mdl {
namespace expression {
namespace iterator {

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
	Tree (Node_*);
	Tree (const Tree&);

	void operator +();
	void operator - ();

	void dump() const;
};

}
}
}


