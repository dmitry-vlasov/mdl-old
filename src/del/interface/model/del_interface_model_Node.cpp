/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_model_Node.cpp                             */
/* Description:     abstract interface for nodes in model trees              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace del {
namespace interface {
namespace model {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Node :: Node() :
	clone_ (NULL),
	isVisited_ (false),
	isTrue_ (false),
	interpolant_ (NULL) {
	}
	Node :: ~ Node() {
		deleteAggregateObject (interpolant_);
	}

	inline bool
	Node :: isVisited() const {
		return isVisited_;
	}
	inline bool
	Node :: isTrue() const {
		return isTrue_;
	}
	inline bool
	Node :: isFalse() const {
		return !isTrue_;
	}
	inline const Term*
	Node :: getInterpolant() const {
		return interpolant_;
	}

	inline void
	Node :: setVisited() const {
		isVisited_ = true;
	}
	inline void
	Node :: setTrue() const {
		isTrue_ = true;
	}
	inline void
	Node :: setFalse() const {
		isTrue_ = false;
	}
	inline void
	Node :: setInterpolant (const Term* interpolant) const {
		interpolant_ = interpolant;
	}

	inline void
	Node :: clear() const
	{
		isVisited_ = false;
		isTrue_ = false;
		if (interpolant_ != NULL) {
			const_cast<del :: Term*>(interpolant_)->commitSuicide();
		}
		interpolant_ = NULL;
		clone_ = NULL;
	}

	// del :: Object implementation
	Size_t
	Node :: getVolume() const {
		return getAggregateVolume (interpolant_);
	}
	Size_t
	Node :: getSizeOf() const {
		return sizeof (Node);
	}
}
}
}


