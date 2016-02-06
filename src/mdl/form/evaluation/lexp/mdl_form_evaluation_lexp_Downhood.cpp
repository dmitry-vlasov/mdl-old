/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_lexp_Downhood.cpp                    */
/* Description:     a downhood of a point in a proof                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace form {
namespace evaluation {
namespace lexp {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Downhood<A> :: Downhood (const mdl :: proof :: Step* step) :
	step_ (step),
	node_ (NULL),
	tree_ (new Tree_ (step_)) {
	}
	template<class A>
	inline
	Downhood<A> :: Downhood (const Node_* node) :
	step_ (NULL),
	node_ (node),
	tree_ (new Tree_ (node_)) {
	}
	template<class A>
	inline
	Downhood<A> :: Downhood (const Downhood& downhood) :
	step_ (downhood.step_),
	node_ (downhood.node_),
	tree_ (new Tree_ (downhood.tree_)) {
	}
	template<class A>
	Downhood<A> :: ~ Downhood() {
		deleteAggregateObject (tree_);
	}

	template<class A>
	inline value :: Real
	Downhood<A> :: getDistance (const Downhood& downhood, const Factors& factors) const {
		return tree_->getDistance (downhood.tree_, factors);
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	// object :: Object implementation
	template<class A>
	void
	Downhood<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Downhood<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (tree_);
		return volume;
	}
	template<class A>
	Size_t
	Downhood<A> :: getSizeOf() const {
		return sizeof (Downhood);
	}
	template<class A>
	void
	Downhood<A> :: show (String& string) const {
 	}

	/****************************
	 *		Private members
	 ****************************/
}
}
}
}


