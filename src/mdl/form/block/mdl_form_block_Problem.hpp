/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_block_Problem.hpp                               */
/* Description:     problem class                                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_BLOCK_PROBLEM_HPP_
#define MDL_FORM_BLOCK_PROBLEM_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/form/mdl_form_Identifiable.hpp"
#include "mdl/form/block/mdl_form_block_Theorem.hpp"

namespace mdl {
namespace form {
namespace block {

class Problem :
	public mdl :: Theorem,
	public Scalar<Problem> {
public :
	Problem
	(
		const Location&,
		const mdl :: Comments*,
		lexer :: Indent,
		value :: Name,
		mdl :: Variables*,
		mdl :: Disjointeds*,
		const vector :: parser :: Hypothesis&,
		const vector :: parser :: Provable&,
		mdl :: Theory*
	);
	virtual ~ Problem();

	// object :: Provable interface
	virtual void addProof (mdl :: Proof*);

	virtual mdl :: proof :: Scope* getScope();
	virtual vector :: Proof& getProofVector();
	virtual mdl :: Proof* getProof (const value :: Name name);

	virtual const vector :: Proof& getProofVector() const;
	virtual const mdl :: Proof* getProof (const value :: Name name) const;
	virtual const mdl :: proof :: Scope* getScope() const;

	// mdl :: Assertion interface
	virtual void addEvaluation (mdl :: Evaluation*) const;
	virtual mdl :: Assertion :: Kind getKind() const;
	virtual index :: Assertion getIndex() const;
	virtual index :: Arity getHypArity() const;
	virtual index :: Arity getPropArity() const;

	virtual mdl :: Variables* getVariables();
	virtual mdl :: Disjointeds* getDisjointeds() const;
	virtual mdl :: Hypothesis* getHypothesis (const index :: Arity);
	virtual mdl :: Proposition* getProposition (const index :: Arity);
	virtual mdl :: Evaluation* getEvaluation (const value :: Name);

	virtual const mdl :: Variables* getVariables() const;
	virtual const mdl :: Disjointeds* getDisjointeds() const;
	virtual const mdl :: Hypothesis* getHypothesis (const index :: Arity) const;
	virtual const mdl :: Proposition* getProposition (const index :: Arity) const;
	virtual const mdl :: Evaluation* getEvaluation (const value :: Name) const;

	// object :: Identifiable interface
	virtual const Location& getLocation() const;
	virtual value :: Name getName() const;

	virtual void translateName (String&, const index :: Arity = 0) const;
	virtual void replicateName (String&) const;

	virtual mdl :: Theory* getTheory();
	virtual mdl :: Identificator* getIdentificator();
	virtual const mdl :: Theory* getTheory() const;
	virtual const mdl :: Identificator* getIdentificator() const;

	// object :: Verifiable interface
	virtual void check();
	virtual void compress();
	virtual void prove();
	virtual void reprove();
	virtual bool isVerified() const;
	virtual void mine (String&) const;
	virtual void setContents (mdl :: Contents*);

	// object :: Buildable interface
	virtual void build();

	// object :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;
	virtual bool lookup() const;
	virtual object :: Writable* find();
	virtual const object :: Writable* find() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getSizeOf() const;
	virtual Size_t getVolume() const;

private :
	friend class Proof;

	Theorem theorem_;
	bool proved_;
};

}
}
}

#endif /*MDL_FORM_BLOCK_PROBLEM_HPP_*/
