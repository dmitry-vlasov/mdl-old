/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_strategy_Directed.hpp                         */
/* Description:     directed strategy                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace prover {
namespace strategy {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Directed<A> :: Directed (Tree_* tree) :
	tree_(tree),
	proofFragment_ (NULL) {
	}

	template<class A>
	inline
	Directed<A> :: ~ Directed() {
		tree_ = NULL;
	}

	// prover :: Strategy implementation
	template<class A>
	bool
	Directed<A> :: use() {


	}

	// object :: Object implementation
	template<class A>
	void
	Directed<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Directed<A> :: getVolume() const {
		return 0;
	}
	template<class A>
	Size_t
	Directed<A> :: getSizeOf() const {
		return sizeof (Directed);
	}
	template<class A>
	void
	Directed<A> :: show (String&) const {
	}
}
}
}



