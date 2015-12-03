/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_iterator_modifier_Identity.ipp            */
/* Description:     identity modifier for iterator                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_ITERATOR_MODIFIER_IDENTITY_IPP_
#define MDL_EXPRESSION_ITERATOR_MODIFIER_IDENTITY_IPP_

namespace mdl {
namespace expression {
namespace iterator {
namespace modifier {

	/****************************
	 *		Public members
	 ****************************/

	template<class I>
	inline
	Identity<I> :: Identity () :
	Iterator_ () {
	}
	template<class I>
	inline
	Identity<I> :: Identity (const Iterator_& iterator) :
	Iterator_ (iterator) {
	}
	template<class I>
	inline
	Identity<I> :: Identity (const Identity& iterator) :
	Iterator_ (static_cast<const Iterator_&> (iterator)) {
	}
}
}
}
}

#endif /*MDL_EXPRESSION_ITERATOR_MODIFIER_IDENTITY_HPP_*/
