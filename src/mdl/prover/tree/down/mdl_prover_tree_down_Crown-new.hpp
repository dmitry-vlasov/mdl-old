/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_tree_down_Crown.hpp                           */
/* Description:     crown (bottom) in proof variant tree                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_TREE_DOWN_DOWN_CROWN_HPP_
#define MDL_PROVER_TREE_DOWN_CROWN_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/prover/mdl_prover.dpp"

namespace mdl {
namespace prover {
namespace tree {
namespace down {

template<class A>
class Crown : public object :: Object {
public :
	typedef A Allocator_;
	typedef Tree<Allocator_> Tree_;
	typedef
		Types<Allocator_> Types_;
	typedef
		typename tree :: Tree<Allocator_> MainTree_;
	typedef
		typename Types_ :: PremiseTree_
		PremiseTree_;
	typedef
		typename Types_ :: ExpressionTree_
		ExpressionTree_;
	typedef
		typename Types_ :: Expression_
		Expression_;
	typedef
		typename Types_ :: Evidence_
		Evidence_;

	// prover :: Crown interface
	virtual bool grow() = 0;
	virtual void add (Evidence_*) = 0;
	virtual void remove (Evidence_*) = 0;
	virtual bool contains (Evidence_*) const = 0;
	virtual bool isEmpty () const = 0;
};

}
}
}
}

#endif /*MDL_PROVER_TREE_DOWN_CROWN_HPP_*/
