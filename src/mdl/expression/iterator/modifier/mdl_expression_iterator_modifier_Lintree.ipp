/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_iterator_modifier_Lintree.ipp             */
/* Description:     modifier for making tree from linear iterator            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_ITERATOR_MODIFIER_LINTREE_IPP_
#define MDL_EXPRESSION_ITERATOR_MODIFIER_LINTREE_IPP_

namespace mdl {
namespace expression {
namespace iterator {
namespace modifier {

	/****************************
	 *		Public members
	 ****************************/

	template<class I>
	inline
	Lintree<I> :: Lintree () :
	Iterator_ () {
	}
	template<class I>
	inline
	Lintree<I> :: Lintree (const Iterator_& iterator) :
	Iterator_ (iterator) {
	}
	template<class I>
	inline
	Lintree<I> :: Lintree (const Lintree& iterator) :
	Iterator_ (static_cast<const Iterator_&> (iterator)) {
	}

	template<class I>
	inline void
	Lintree<I> :: operator +() {
		Iterator_ :: setNull();
	}
	template<class I>
	inline void
	Lintree<I> :: operator -() {
		Iterator_ :: setNull();
	}
}
}
}
}

#endif /*MDL_EXPRESSION_ITERATOR_MODIFIER_LINTREE_HPP_*/
