/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_iterator_modifier_Linforest.ipp           */
/* Description:     modifier for making forest from linear iterator          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_ITERATOR_MODIFIER_LINFOREST_IPP_
#define MDL_EXPRESSION_ITERATOR_MODIFIER_LINFOREST_IPP_

namespace mdl {
namespace expression {
namespace iterator {
namespace modifier {

	/****************************
	 *		Public members
	 ****************************/

	template<class I>
	inline
	Linforest<I> :: Linforest () :
	Lintree_ () {
	}
	template<class I>
	inline
	Linforest<I> :: Linforest (const Iterator_& iterator) :
	Lintree_ (iterator) {
	}
	template<class I>
	inline
	Linforest<I> :: Linforest (const Lintree_& iterator) :
	Lintree_ (iterator) {
	}
	template<class I>
	inline 
	Linforest<I> :: Linforest (const Linforest& iterator) :
	Lintree_ (static_cast<const Lintree_&> (iterator)) {
	}

	template<class I>
	inline bool
	Linforest<I> :: isReacheable (const index :: Step) const {
		return true;
	}
}
}
}
}

#endif /*MDL_EXPRESSION_ITERATOR_MODIFIER_LINFOREST_HPP_*/
