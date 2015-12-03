/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_data_Tree.hpp                                 */
/* Description:     prover tree statistics data                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_DATA_TREE_HPP_
#define MDL_PROVER_DATA_TREE_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/prover/mdl_prover.dpp"

#include "mdl/prover/data/mdl_prover_data_Down.hpp"
#include "mdl/prover/data/mdl_prover_data_Root.hpp"
#include "mdl/prover/data/mdl_prover_data_Up.hpp"

namespace mdl {
namespace prover {
namespace data {

class Tree :
	public object :: Object,
	public Scalar<Tree, allocator :: Heap> {
public :
	Tree();
	template<class A>
	Tree (const tree :: Tree<A>&);
	virtual ~ Tree();

	void operator += (const Tree&);
	void operator /= (const int);

	void showVolume (String&, const int indent = 0) const;
	void showTiming (String&, const int indent = 0) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	Up   up_;
	Down down_;
	Root root_;

	Size_t totalVolume_;
	Size_t premiseTreeVolume_;
	Size_t premiseVectorVolume_;
	Size_t expressionTreeVolume_;
	Size_t variablesVolume_;

	Timer growUpTimer_;
	Timer growDownTimer_;
};

}
}
}

#endif /*MDL_PROVER_DATA_TREE_HPP_*/
