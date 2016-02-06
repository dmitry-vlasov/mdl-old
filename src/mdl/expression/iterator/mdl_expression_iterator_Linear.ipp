/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_iterator_Linear.ipp                       */
/* Description:     linear iterator                                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace expression {
namespace iterator {

	/****************************
	 *		Public members
	 ****************************/

	template<class N>
	inline
	Linear<N> :: Linear () :
	Ancestor_ () {
	}
	template<class N>
	inline
	Linear<N> :: Linear (Node_* node) :
	Ancestor_ (node) {
	}
	template<class N>
	inline
	Linear<N> :: Linear (const Linear& iterator) :
	Ancestor_ (iterator) {
	}

	template<class N>
	inline void
	Linear<N> :: operator ++() {
		Ancestor_ :: node_ = Ancestor_ :: node_->goRight();
	}
	template<class N>
	inline void
	Linear<N> :: operator --() {
		Ancestor_ :: node_ = Ancestor_ :: node_->goLeft();
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


