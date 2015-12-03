/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_tree_down_Level.hpp                           */
/* Description:     level in proof variant tree                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_TREE_DOWN_LEVEL_HPP_
#define MDL_PROVER_TREE_DOWN_LEVEL_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/prover/mdl_prover.dpp"

namespace mdl {
namespace prover {
namespace tree {
namespace down {

template<class A>
class Level :
	public object :: Object,
	public Scalar<Level<A>, A> {
public :
	typedef A Allocator_;
	typedef
		Types<Allocator_> Types_;
	typedef
		typename Types_ :: Evidence_
		Evidence_;

	Level (const value :: Integer initialCapacity = INITIAL_LEVEL_CAPACITY);
	virtual ~ Level();

	// tree :: up :: Level interface
	value :: Integer getSize () const;
	Evidence_* getValue (const value :: Integer) const;

	bool isEmpty() const;
	void add (Evidence_*);
	void remove (Evidence_*);
	bool contains (Evidence_*) const;

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
			Evidence_,
			storage :: ByPointer,
			Allocator_
		>
		Level_;

	mutable Level_   level_;
};

}
}
}
}

#endif /*MDL_PROVER_TREE_DOWN_LEVEL_HPP_*/
