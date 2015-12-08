/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_tree_Tree.hpp                                 */
/* Description:     variant tree                                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_TREE_TREE_HPP_
#define MDL_PROVER_TREE_TREE_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/prover/mdl_prover.dpp"
#include "mdl/prover/tree/up/mdl_prover_tree_up.hpp"
#include "mdl/prover/tree/down/mdl_prover_tree_down.hpp"

namespace mdl {
namespace prover {
namespace tree {

template<class A>
class Tree :
	public interface :: Tree<A>,
	public Scalar<Tree<A>, A> {
public :
	typedef A Allocator_;
	typedef Root<Allocator_> Root_;
	typedef
		typename up :: Tree<Allocator_>
		UpTree_;
	typedef
		typename down :: Tree<Allocator_>
		DownTree_;
	typedef
		Types<Allocator_> Types_;
	typedef
		typename Types_ :: Node_
		Node_;
	typedef
		typename Types_ :: Evidence_
		Evidence_;
	typedef
		typename Types_ :: PremiseTree_
		PremiseTree_;
	typedef
		typename Types_ :: PremiseVector_
		PremiseVector_;
	typedef
		typename Types_ :: ExpressionTree_
		ExpressionTree_;
	typedef
		typename Types_ :: Expression_
		Expression_;

	// constructor for up-tree, for learning
	Tree (Format&, Format&, mdl :: proof :: Step* step);
	// constructor for up-down tree (proving)
	Tree (Format&, Format&, mdl :: proof :: Question* question);
	virtual ~ Tree();

	// prover :: Tree interface
	bool prove (const Time);
	void start (String& message);
	void grow  ();
	void stop  ();
	void info  (String&);
	void confirm ();
	bool isProved();
	void showVolume (String&, const int indent = 0) const;
	void showTiming (String&, const int indent = 0) const;
	virtual Data* getData() const;

	static void writeHeader (String& string, const char* header, const int indent = 0);
	static void writeEnding (String& string, const char* header, const int indent = 0);

	void verifyDeterminedGrowUp();
	void verifyDeterminedGrowDown();

	void init();

	void growUpForLearning (const Time timeLimit, const value :: Integer sizeLimit);

	Root_& root();
	UpTree_& up();
	DownTree_& down();

	bool canGrowDown() const;
	value :: Real evalFitness() const;
	const mdl :: Assertion* getProblem() const;
	const PremiseTree_* getPremiseTree() const;
	const PremiseVector_* getPremiseVector() const;
	index :: Assertion getProblemIndex();
	index :: Step getStepBoundary();
	const mdl :: proof :: Question* getQuestion() const;
	mdl :: proof :: Question* getQuestion();
	Symbol createVariable (const Symbol&);

	void refresh
	(
		const char* message = "",
		const bool forceStatus = false
	) const;
	const Timers* getTimers() const;
	Timers* getTimers();
	void showInGML() const;
	void showInGML (const String& fileName) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	friend class data :: Tree;
	template<class> friend class node :: Hyp;
	template<class> friend class up :: Tree;
	template<class> friend class down :: Tree;
	template<class> friend class Root;

	enum {
		INITIAL_VARIABLES_CAPACITY = nstd :: size :: KILOBYTE * 64,
		INITIAL_MESSAGE_CAPACITY   = 256,
		INITIAL_PREMISE_VECTOR_CAPACITY = 256
	};
	typedef
		map :: Scalar
		<
			value :: Literal,
			value :: Integer,
			Allocator_
		>
		Variables_;

	bool growUpDown();
	void arrangePremises();
	void addLinePremises();
	bool addClaimPremises();
	void addAssertionPremises();

	void showStart (const Time timeLimit) const;
	void showResult() const;
	void showStatus (const char* = "") const;

	void showNodeInfo (String&) const;
	void showEvidenceInfo (String&) const;
	void showUpTreeInfo (String&) const;
	void showDownTreeInfo (String&) const;
	void showTreeInfo (String&) const;
	void showSproutInfo (String&) const;

	Format& format_;
	Format& subFormat_;
	Timers* timers_;
	mdl :: Assertion*           problem_;
	const mdl :: proof :: Step* hint_;
	mdl :: proof :: Question*   question_;
	mdl :: proof :: Step*       answer_;
	mdl :: proof :: Scoping*    scoping_;

	PremiseTree_*    premiseTree_;
	PremiseVector_*  premiseVector_;
	ExpressionTree_* expressionTree_;
	Variables_*      variables_;

	Root_*     root_;
	UpTree_*   up_;
	DownTree_* down_;

	const bool canGrowDown_;
	pthread_mutex_t mutex_;
};

}
}
}

#endif /*MDL_PROVER_TREE_TREE_HPP_*/
