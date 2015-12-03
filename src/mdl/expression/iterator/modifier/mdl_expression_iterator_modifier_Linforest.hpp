/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_iterator_modifier_Linforest.hpp           */
/* Description:     modifier for making forest from linear iterator          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_ITERATOR_MODIFIER_LINFOREST_HPP_
#define MDL_EXPRESSION_ITERATOR_MODIFIER_LINFOREST_HPP_

#include "mdl/expression/iterator/modifier/mdl_expression_iterator_modifier_Lintree.hpp"

namespace mdl {
namespace expression {
namespace iterator {
namespace modifier {

template<class I>
class Linforest : public Lintree<I> {
public :
	typedef
		Lintree<I>
		Lintree_;
	typedef
		typename Lintree_ :: Iterator_
		Iterator_;

	Linforest ();
	Linforest (const Iterator_&);
	Linforest (const Lintree_&);
	Linforest (const Linforest&);

	bool isReacheable (const index :: Step) const;
};

}
}
}
}

#endif /*MDL_EXPRESSION_ITERATOR_MODIFIER_LINFOREST_HPP_*/
