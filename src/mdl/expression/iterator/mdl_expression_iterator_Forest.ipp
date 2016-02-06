/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_iterator_Forest.ipp                       */
/* Description:     forst (set of trees) iterator                            */
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
	Forest<N> :: Forest () :
	Ancestor_ () {
	}
	template<class N>
	inline
	Forest<N> :: Forest (Node_* node) :
	Ancestor_ (node) {
	}
	template<class N>
	inline
	Forest<N> :: Forest (const Forest& iterator) :
	Ancestor_ (iterator) {
	}

	template<class N>
	inline bool
	Forest<N> :: isReacheable (const index :: Step level) const {
		return Ancestor_ :: node_->isReacheable (level);
	}

	template<class N>
	void
	Forest<N> :: dump() const {
		Ancestor_ :: dump();
	}
}
}
}


