/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_tree_down_crown_Sequental.hpp                 */
/* Description:     crown (bottom) in proof variant tree                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_TREE_DOWN_CROWN_SEQUENTAL_HPP_
#define MDL_PROVER_TREE_DOWN_CROWN_SEQUENTAL_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/prover/mdl_prover.dpp"

namespace mdl {
namespace prover {
namespace tree {
namespace down {
namespace crown {

template<class A>
class Sequental :
	public object :: Object,
	public Scalar<Sequental<A>, A> {
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
	typedef
		typename Types_ :: Proof_
		Proof_;
	typedef
		typename Types_ :: Node_
		Node_;

	Sequental (MainTree_*, Tree_*);
	virtual ~ Sequental();

	// prover :: Crown interface
	bool grow();

	void add (Evidence_*);
	void remove (Evidence_*);
	bool contains (Evidence_*) const;
	bool isEmpty () const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	enum {
		INITIAL_EVIDENCES_CAPACITY = size :: KILOBYTE * 64
	};

	typedef
		mdl :: set :: Set
		<
			Evidence_,
			storage :: ByWeakPointer,
			Allocator_
		>
		EvidenceSet_;

	typedef
		mdl :: vector :: Vector
		<
			Evidence_*,
			storage :: ByValue,
			Allocator_
		>
		EvidenceVector_;

	bool growSingleThreaded();
	bool growStep (index :: Step& minHeight);

	index :: Step getMinHeight() const;

	/*template<class>
	friend void* growInThread (void* pointer);
	struct Arguments_ {
		Arguments_() :
		threadIndex_ (0),
		threadCount_ (0),
		evidences_ (NULL),
		crown_ (NULL) {
		}
		int threadIndex_;
		int threadCount_;
		EvidenceVector_* evidences_;
		Sequental*       crown_;
	};*/

	void showStatistics (String&) const;
	void showPlain (String&) const;

	MainTree_*    mainTree_;
	Tree_*        tree_;
	EvidenceSet_  evidences_;
	mutable Timer timer_;
	mutable value :: Integer counter_;
};

}
}
}
}
}

#endif /*MDL_PROVER_TREE_DOWN_CROWN_SEQUENTAL_HPP_*/
