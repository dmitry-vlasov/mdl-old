/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_block_Assertion.hpp                             */
/* Description:     assertion class                                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_BLOCK_ASSERTION_HPP_
#define MDL_FORM_BLOCK_ASSERTION_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/form/mdl_form_Identifiable.hpp"

namespace mdl {
namespace form {
namespace block {

template<class H, class P>
class Assertion :
	public form :: Identifiable,
	virtual public mdl :: Assertion {
protected :
	typedef
		typename form :: Identifiable
		Ancestor_;
	typedef H Hypothesis_;
	typedef P Proposition_;
	typedef
		vector :: Vector
		<
			Proposition_,
			storage :: ByPointer,
			allocator :: Heap
		>
		PropositionVector_;
	typedef
		vector :: Vector
		<
			Proposition_*,
			storage :: ByValue,
			allocator :: Heap
		>
		ParserPropositionVector_;
	typedef
		vector :: Vector
		<
			Hypothesis_,
			storage :: ByPointer,
			allocator :: Heap
		>
		HypothesisVector_;
	typedef
		vector :: Vector
		<
			Hypothesis_*,
			storage :: ByValue,
			allocator :: Heap
		>
		ParserHypothesisVector_;

public :
	Assertion
	(
		const Location&,
		const mdl :: Comments*,
		const lexer :: Indent,
		const value :: Name,
		mdl :: Variables*,
		mdl :: Disjointeds*,
		const ParserHypothesisVector_&,
		const ParserPropositionVector_&,
		mdl :: Theory*
	);
	virtual ~ Assertion();

	// mdl :: Assertion interface
	virtual void addEvaluation (mdl :: Evaluation*);
	virtual mdl :: Assertion :: Kind getKind() const = 0;
	virtual index :: Assertion getIndex() const;
	virtual index :: Arity getHypArity() const;
	virtual index :: Arity getPropArity() const;

	virtual mdl :: Variables* getVariables();
	virtual mdl :: Disjointeds* getDisjointeds();
	virtual mdl :: Hypothesis* getHypothesis (const index :: Arity);
	virtual mdl :: Proposition* getProposition (const index :: Arity);
	virtual mdl :: Evaluation* getEvaluation (const value :: Name);

	virtual const mdl :: Variables* getVariables() const;
	virtual const mdl :: Disjointeds* getDisjointeds() const;
	virtual const mdl :: Hypothesis* getHypothesis (const index :: Arity) const;
	virtual const mdl :: Proposition* getProposition (const index :: Arity) const;
	virtual const mdl :: Evaluation* getEvaluation (const value :: Name) const;

	// object :: Identifiable interface
	virtual void translateName (String&, const index :: Arity = 0) const;
	virtual void replicateName (String&) const;

	// object :: Verifiable interface
	virtual void mine (String&) const;

	// object :: Buildable interface
	virtual void build();

	// object :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;
	virtual bool lookup() const;
	virtual object :: Writable* find();
	virtual const object :: Writable* find() const;

	// object :: Object interface
	virtual void commitSuicide() = 0;
	virtual Size_t getSizeOf() const;
	virtual Size_t getVolume() const;

protected :
	void replicateHeader (String&) const;
	void replicateHypothesis (String&) const;
	void replicateBar (String&) const;
	void replicatePropositions (String&) const;

	void buildVariables();
	void buildHypothesis();
	void buildPropositions();
	template<class T>
	void add (T*);

	mdl :: Variables* variables_;
	mdl :: Disjointeds* disjointeds_;
	HypothesisVector_ hypothesisVector_;
	PropositionVector_ propositionVector_;

	vector :: Evaluation evaluationVector_;

private :
	friend class Problem;
	friend class refactor :: redundant :: Hypotheses;

	enum {
		INITIAL_EVALUATION_VECTOR_CAPACITY = 2
	};
	index :: Assertion index_;
	lexer :: Indent barIndent_;
};

}
}
}

#endif /*MDL_FORM_BLOCK_ASSERTION_HPP_*/
