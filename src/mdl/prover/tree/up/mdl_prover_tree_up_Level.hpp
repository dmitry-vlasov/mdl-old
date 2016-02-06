/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_tree_up_Level.hpp                             */
/* Description:     level in proof variant tree                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/prover/mdl_prover.dpp"

namespace mdl {
namespace prover {
namespace tree {
namespace up {

template<class A, template<class> class S>
class Level :
	public object :: Object,
	public Scalar<Level<A, S>, A> {
public :
	typedef A Allocator_;
	typedef Prop<Allocator_> Prop_;
	typedef Hyp<Allocator_> Hyp_;
	typedef Ref<Allocator_> Ref_;
	typedef
		Types<Allocator_> Types_;
	typedef
		typename Types_ :: Node_
		Node_;

	Level (const value :: Integer initialCapacity = INITIAL_LEVEL_CAPACITY);
	virtual ~ Level();

	// tree :: up :: Level interface
	value :: Integer getSize () const;
	Node_* getValue (const value :: Integer) const;
	Node_* takeBest();
	Node_* takeBestHint();
	Node_* takeBestRestricted();

	bool isEmpty (const bool onlyHint = false, const bool restricted = false) const;
	void add (Node_*);
	void remove (Node_*);
	bool contains (Node_*) const;
	void evalPartition (value :: Integer& boundary, value :: Integer& size) const;
	void showPartition (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	enum {
		INITIAL_LEVEL_CAPACITY = size :: KILOBYTE
	};

	typedef
		mdl :: set :: Set
		<
			Node_,
			S,
			Allocator_
		>
		Level_;

	value :: Integer evalPartitionBoundary() const;
	value :: Integer evalPartitionSize (const value :: Integer boundary = 0) const;

	bool showPropNode (const Node_*, String&) const;
	bool showHypNode (const Node_*, String&) const;
	//void verifySize() const;

	mutable Level_   level_;
};

}
}
}
}


