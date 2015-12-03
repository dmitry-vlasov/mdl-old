/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_iterator_constant_Tree.ipp                */
/* Description:     tree (2-dimensional) const iterator                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_ITERATOR_CONSTANT_TREE_IPP_
#define MDL_EXPRESSION_ITERATOR_CONSTANT_TREE_IPP_

namespace mdl {
namespace expression {
namespace iterator {
namespace constant {

	/****************************
	 *		Public members
	 ****************************/

	template<class N>
	inline
	Tree<N> :: Tree () :
	Ancestor_ (NULL) {
	}
	template<class N>
	inline
	Tree<N> :: Tree (const Node_* node) :
	Ancestor_ (node) {
	}
	template<class N>
	inline
	Tree<N> :: Tree (const typename iterator :: Tree<N>& iterator) :
	Ancestor_ (iterator) {
	}
	template<class N>
	inline
	Tree<N> :: Tree (const Tree& iterator) :
	Ancestor_ (iterator) {
	}

	template<class N>
	inline void
	Tree<N> :: operator +() {
		Ancestor_ :: node_ = Ancestor_ :: node_->getUp();
	}
	template<class N>
	inline void
	Tree<N> :: operator - () {
		Ancestor_ :: node_ = Ancestor_ :: node_->getDown();
	}

	template<class N>
	void
	Tree<N> :: dump() const
	{
		Ancestor_ :: dump();
		std :: cout << "up: "   << static_cast<void*>(Ancestor_ :: node_->getUp())   << ", ";
		std :: cout << "down: " << static_cast<void*>(Ancestor_ :: node_->getDown()) << ", ";
	}
}
}
}
}

#endif /*MDL_EXPRESSION_ITERATOR_CONSTANT_TREE_HPP_*/
