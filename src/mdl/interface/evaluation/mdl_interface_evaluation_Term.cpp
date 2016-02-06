/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_evaluation_Term.cpp                        */
/* Description:     abstract interface for evaluation of fitness             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace interface {
namespace evaluation {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Term :: Term() :
	proposition_ (NULL),
	depth_ (0),
	version_ (0) {
	}
	Term :: ~ Term() {
	}

	value :: Real
	Term :: eval (const BoxedNode_* node) const {
		return eval (reinterpret_cast<const HeapNode_*>(node));
	}
	value :: Real
	Term :: eval (const value :: Real values[]) const {
		return -1;
	}

	void
	Term :: setProposition (const form :: header :: statement :: Proposition* proposition)
	{
		proposition_ = proposition;
		for (value :: Integer i = 0; i < getArity(); ++ i) {
			Term* subterm = getSubTerm (i);
			subterm->setProposition (proposition);
		}
	}
	void
	Term :: setDepth (const value :: Integer depth)
	{
		depth_ = depth;
		for (value :: Integer i = 0; i < getArity(); ++ i) {
			Term* subterm = getSubTerm (i);
			subterm->setDepth (depth + 1);
		}
	}

	inline value :: Integer
	Term :: getVersion() const {
		return version_;
	}
}
}
}



