/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_iterator_constant_Linear.ipp              */
/* Description:     linear const iterator                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_ITERATOR_CONSTANT_LINEAR_IPP_
#define MDL_EXPRESSION_ITERATOR_CONSTANT_LINEAR_IPP_

namespace mdl {
namespace expression {
namespace iterator {
namespace constant {

	/****************************
	 *		Public members
	 ****************************/

	template<class N>
	inline
	Linear<N> :: Linear () :
	Ancestor_ (NULL) {
	}
	template<class N>
	inline
	Linear<N> :: Linear (const Node_* node) :
	Ancestor_ (node) {
	}
	template<class N>
	inline
	Linear<N> :: Linear (const typename iterator :: Linear<N>& iterator) :
	Ancestor_ (iterator) {
	}
	template<class N>
	inline
	Linear<N> :: Linear (const Linear& iterator) :
	Ancestor_ (iterator) {
	}

	template<class N>
	inline void
	Linear<N> :: operator ++() {
		Ancestor_ :: node_ = Ancestor_ :: node_->getRight();
	}
	template<class N>
	inline void
	Linear<N> :: operator -- () {
		Ancestor_ :: node_ = Ancestor_ :: node_->getLeft();
	}

	template<class N>
	void
	Linear<N> :: dump() const
	{
		Ancestor_ :: dump();
		std :: cout << "right: " << static_cast<void*>(Ancestor_ :: node_->getRight()) << ", ";
		std :: cout << "left: "  << static_cast<void*>(Ancestor_ :: node_->getLeft())  << ", ";
	}
}
}
}
}

#endif /*MDL_EXPRESSION_ITERATOR_CONSTANT_LINEAR_IPP_*/
