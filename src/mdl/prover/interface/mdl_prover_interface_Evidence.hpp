/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_interface_Evidence.hpp                        */
/* Description:     interface for evidence (semiproof) in variant tree       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.dpp"

namespace mdl {
namespace prover {
namespace interface {

template<class A>
class Evidence : public object :: Cloneable<Evidence<A> > {
public :
	typedef A Allocator_;
	typedef Base<Allocator_> Base_;
	typedef Node<Allocator_> Node_;
	typedef Proof<Allocator_> Proof_;
	typedef Evidence<Allocator_> Evidence_;
	typedef
		typename Base_ :: Expression_
		Expression_;
	typedef
		typename Base_ :: Substitution_
		Substitution_;

	Evidence (Node_*);
	Evidence (const Evidence&);

	Node_* getNode();
	const Node_* getNode() const;
	index :: Step getMaxHeight() const;
	index :: Step getMinHeight() const;
	value :: Integer getComplexity() const;

	virtual bool growDown() = 0;
	virtual void setDown (Evidence_*) = 0;
	virtual value :: Integer getUpForking() const = 0;
	virtual value :: Integer getDownForking() const = 0;
	virtual Evidence_* getUp (const value :: Integer) = 0;
	virtual Evidence_* getDown (const value :: Integer = 0) = 0;
	virtual const Evidence_* getUp (const value :: Integer) const = 0;
	virtual const Evidence_* getDown (const value :: Integer = 0) const = 0;
	virtual void verifyIntegrity() const = 0;
	virtual Substitution_* getSubstitution() = 0;
	virtual const Substitution_* getSubstitution() const = 0;
	virtual index :: Step getDepth() const = 0;
	virtual value :: Integer getCardinality() const = 0;
	virtual Proof_* constructProof (const Substitution_* = NULL) = 0;
	virtual bool givesSameProof (const Evidence_*) const = 0;
	virtual bool hasSameSubstitution (const Evidence_*) const;

	void showInfo (String&, const int indent = 0) const;
	void showTree (String&, const int indent = 0) const;
	void dumpInfo () const;
	void dumpTree () const;
	void dumpProof() const;
	void dumpIndex() const;

	void setMapped (const bool) const;
	bool isHint() const;

	bool containsUpGlobalIndex (value :: Integer) const;

	// index of a node in a tree
	value :: Integer getGlobalIndex() const;
	value :: Integer getLevelIndex() const;
	void setGlobalIndex (const value :: Integer);
	void setLevelIndex (const value :: Integer);

protected :
	template<class>
	friend class tree :: down :: Tree;

	void showGraphInGML (String&, const value :: Integer = 0, const char* label = "") const;

	mutable bool mapped_;
	Node_* node_;
	value :: Integer complexity_;
	value :: Integer globalIndex_; // global index of a node. Used to refer to it globally.
	value :: Integer levelIndex_;  // index of a node inside a level.

private :
	void showProof (String&, const int indent = 0) const;
	void showTypes (String&, const int indent = 0) const;
	void showScalars (String&, const int indent = 0) const;
	void showKind (String&, const int indent = 0) const;
	void showHint (String&, const int indent = 0) const;

	void showExpression (String&, const int indent = 0) const;
	void showSubstitution (String&, const int indent = 0) const;
};
	template<class A>
	bool operator < (const Evidence<A>&, const Evidence<A>&);
	template<class A>
	bool operator <= (const Evidence<A>&, const Evidence<A>&);
	template<class A>
	bool operator > (const Evidence<A>&, const Evidence<A>&);
	template<class A>
	bool operator >= (const Evidence<A>&, const Evidence<A>&);
	template<class A>
	bool operator == (const Evidence<A>&, const Evidence<A>&);
}
}
}


