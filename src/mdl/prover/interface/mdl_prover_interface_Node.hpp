/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_interface_Node.hpp                            */
/* Description:     interface for a node of the variant tree                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace prover {
namespace interface {

template<class A>
class Node : public object :: Cloneable<Node<A> > {
public :
	typedef A Allocator_;
	typedef Base<Allocator_> Base_;
	typedef Node<Allocator_> Node_;
	typedef Proof<Allocator_> Proof_;
	typedef Evidence<Allocator_> Evidence_;
	typedef Evidences<Allocator_> Evidences_;
	typedef
		typename Base_ :: Expression_
		Expression_;
	typedef
		typename Base_ :: Substitution_
		Substitution_;
	typedef
		typename tree :: Tree<Allocator_>
		Tree_;
	typedef
		typename vector :: Vector<Node*, storage :: ByValue, allocator :: Standard>
		NodeVector_;
	typedef
		typename set :: Set<const Node*, storage :: ByValue, allocator :: Standard>
		NodeSet_;

	Node (Tree_*);
	virtual ~ Node();

	virtual const mdl :: proof :: Node* getHint() const = 0; // for learning - a true proof hint
	virtual void markHint (const mdl :: proof :: Node*) = 0;

	virtual value :: Integer getUpArity() const = 0;
	virtual value :: Integer getDownArity() const = 0;
	virtual Node_* getUp (const value :: Integer) = 0;
	virtual Node_* getDown (const value :: Integer = 0) = 0;
	virtual const Node_* getUp (const value :: Integer) const = 0;
	virtual const Node_* getDown (const value :: Integer = 0) const = 0;

	virtual void growUp() = 0;
	virtual bool growDown (Evidence_*) = 0;

	virtual Expression_* getExpression() = 0;
	virtual mdl :: Proposition* getProposition() = 0;
	virtual const Expression_* getExpression() const = 0;
	virtual const mdl :: Proposition* getProposition() const = 0;
	virtual Evidences_& getEvidences() = 0;
	virtual const Evidences_& getEvidences() const = 0;
	virtual value :: Integer getMaxHeight() const = 0;
	virtual value :: Integer getMinHeight() const = 0;
	virtual value :: Real getWeight() const = 0;
	virtual bool isProved() const = 0;
	virtual bool isRoot() const = 0;
	virtual bool mayGrowUp() const = 0;
	virtual void addDown (Node_*) = 0;
	virtual bool liesDown (const Node_*) const = 0;
	virtual void showBack (String&) const = 0;
	virtual void showTreeBriefly (String&) const = 0;
	virtual void showInfo (String&, const int indent = 0) const = 0;

	value :: Integer countPropHintNodes() const;
	void findUnprovedNodes (NodeVector_&);
	void findUnprovedHintNodes (NodeVector_&);
	bool isProvedWithHint() const;

	void showTree
	(
		String&,
		bool onlyHint = false,
		bool showEvidences = true,
		int  upToLevel = -1,
		const int indent = 0
	) const;
	void dumpTree
	(
		bool onlyHint = false,
		bool showEvidences = true,
		int  upToLevel = -1
	) const;
	void dumpEvidences () const;

	value :: Real getSubComplexity() const;
	value :: Real getExpComplexity() const;
	virtual value :: Integer getForking() const;

	// for the graph representation
	int getXCoord() const;
	int getYCoord() const;
	virtual int getXGraphCoord() const;
	virtual int getYGraphCoord() const;

	Tree_* getTree();
	const Tree_* getTree() const;
	bool isHint() const;

	// index of a node in a tree
	value :: Integer getGlobalIndex() const;
	value :: Integer getLevelIndex() const;
	void setGlobalIndex (const value :: Integer);
	void setLevelIndex (const value :: Integer);

protected :
	// constants for the graph representation
	enum {
		X_SCALE = 100,
		Y_SCALE = X_SCALE * 30
	};
	void setMapped (const bool) const;
	void showGraphInGML (String&, const value :: Integer = 0, const char* label = "") const;

	mutable bool mapped_;
	mutable value :: Integer forking_;
	value :: Integer globalIndex_; // global index of a node. Used to refer to it globally.
	value :: Integer levelIndex_;  // index of a node inside a level.

	mutable Tree_* tree_;
};

	template<class A>
	bool operator < (const Node<A>&, const Node<A>&);
	template<class A>
	bool operator <= (const Node<A>&, const Node<A>&);
	template<class A>
	bool operator > (const Node<A>&, const Node<A>&);
	template<class A>
	bool operator >= (const Node<A>&, const Node<A>&);
	template<class A>
	bool operator == (const Node<A>&, const Node<A>&);
}
}
}


