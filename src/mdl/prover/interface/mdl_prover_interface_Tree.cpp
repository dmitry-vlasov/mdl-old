/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_interface_Tree.cpp                            */
/* Description:     main prover tree interface                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_INTERFACE_TREE_CPP_
#define MDL_PROVER_INTERFACE_TREE_CPP_

namespace mdl {
namespace prover {
namespace interface {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	Tree<A> :: Tree()
	{
		if (tree_ != NULL) {
			Error* error = new Error(Error :: SEMANTIC, "double instance of prover tree");
			throw error;
		}
		tree_ = this;
	}
	template<class A>
	Tree<A> :: ~ Tree() {
		tree_ = NULL;
	}

	template<class A>
	inline Tree<A>*
	Tree<A> :: get() {
		return tree_;
	}

	/*********************************
	 *		Static private members
	 *********************************/

	template<class A>
	Tree<A>* Tree<A> :: tree_ = NULL;
}
}
}

#endif /*MDL_PROVER_INTERFACE_TREE_CPP_*/
