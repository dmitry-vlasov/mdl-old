/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_iterator_modifier_Lintree.hpp             */
/* Description:     modifier for making tree from linear iterator            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_ITERATOR_MODIFIER_LINTREE_HPP_
#define MDL_EXPRESSION_ITERATOR_MODIFIER_LINTREE_HPP_

namespace mdl {
namespace expression {
namespace iterator {
namespace modifier {

template<class I>
class Lintree : public I {
public :
	typedef I Iterator_;

	Lintree ();
	Lintree (const Iterator_&);
	Lintree (const Lintree&);

	void operator +();
	void operator -();
};

}
}
}
}

#endif /*MDL_EXPRESSION_ITERATOR_MODIFIER_LINTREE_HPP_*/
