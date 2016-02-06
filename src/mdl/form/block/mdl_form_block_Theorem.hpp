/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_block_Theorem.hpp                               */
/* Description:     theorem class                                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/form/mdl_form_Identifiable.hpp"
#include "mdl/form/block/mdl_form_block_Assertion.hpp"

namespace mdl {
namespace form {
namespace block {

class Theorem :
	public mdl :: Theorem,
	public form :: block :: Assertion
	<
		mdl :: Hypothesis,
		mdl :: statement :: Provable
	>,
	public Scalar<Theorem> {
public :
	Theorem
	(
		const Location&,
		const mdl :: Comments*,
		lexer :: Indent,
		value :: Name,
		mdl :: Variables*,
		mdl :: Disjointeds*,
		const vector :: parser :: Hypothesis&,
		const vector :: parser :: Provable&,
		mdl :: Theory*,
		bool isProblem = false
	);
	virtual ~ Theorem();

	void verifyStructure() const;

	// object :: Provable interface
	virtual void addProof (mdl :: Proof*);

	virtual mdl :: proof :: Scope* getScope();
	virtual vector :: Proof& getProofVector();
	virtual mdl :: Proof* getProof (const value :: Name name);

	virtual const mdl :: proof :: Scope* getScope() const;
	virtual const vector :: Proof& getProofVector() const;
	virtual const mdl :: Proof* getProof (const value :: Name name) const;

	// mdl :: Assertion interface
	virtual mdl :: Assertion :: Kind getKind() const;

	// object :: Verifiable interface
	virtual void check();
	virtual void compress();
	virtual void reprove();
	virtual void prove();
	virtual bool isVerified() const;

	// object :: Buildable interface
	virtual void build();

	// object :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;
	//virtual bool lookup() const;
	//virtual object :: Writable* find();
	//virtual const object :: Writable* find() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getSizeOf() const;
	virtual Size_t getVolume() const;

private :
	typedef
		form :: block :: Assertion
		<
			mdl :: Hypothesis,
			mdl :: statement :: Provable
		>
		Ancestor_;

	//friend class Problem;
	friend class Proof;
	enum {
		INITIAL_PROOF_VECTOR_CAPACITY = 1
	};

	void buildHypothesisNodes();
	void buildPropositionNodes();
	void replicateHeader (String&) const;
	//void replicateBody (String&) const;

	vector :: Proof proofVector_;
	mdl :: proof :: Scope* scope_;
	mutable bool isProved_;
	mutable bool isProblem_;
};

}
}
}


