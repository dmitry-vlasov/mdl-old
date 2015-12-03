/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_step_Claim.hpp                            */
/* Description:     step with claim inference                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_PROOF_STEP_CLAIM_HPP_
#define MDL_FORM_PROOF_STEP_CLAIM_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/form/proof/mdl_form_proof_Step.hpp"

namespace mdl {
namespace form {
namespace proof {
namespace step {

class Claim :
	virtual public proof :: Step,
	virtual public mdl :: proof :: Claim,
	public Scalar<Claim> {
	typedef
		proof :: Step
		Ancestor_;
public :
	Claim
	(
		mdl :: proof :: Line*,
		const Location&,
		const mdl :: Comments*,
		index :: Step,
		mdl :: Identificator*,
		mdl :: proof :: Link*,
		array :: Expression*,
		mdl :: Proof*,
		mdl :: Theory*
	);
	Claim (mdl :: proof :: Step*, index :: Step);
	virtual ~ Claim();

	// proof :: Claim interface
	virtual void addStep (mdl :: proof :: Step*);
	virtual void addVariable (const Symbol&);
	virtual mdl :: Proof* getProof();
	virtual const mdl :: Proof* getProof() const;

	// proof :: Provable interface
	virtual void setProof (mdl :: proof :: Node*);

	// proof :: Step interface
	virtual Class getClass() const;
	virtual void addReference (mdl :: proof :: Reference*);
	virtual void addDown (mdl :: proof :: Step*);
	virtual index :: Arity getUpArity() const;
	virtual index :: Arity getDownArity() const;
	virtual mdl :: proof :: Link* getLink();
	virtual mdl :: proof :: Node* getUp (const index :: Arity);
	virtual mdl :: proof :: Step* getDown (const index :: Arity);
	virtual const mdl :: proof :: Link* getLink() const;
	virtual const mdl :: proof :: Node* getUp (const index :: Arity) const;
	virtual const mdl :: proof :: Step* getDown (const index :: Arity) const;

	// proof :: Node interface
	virtual void replicateReference (String&) const;
	virtual void translateReference (String&) const;

	// object :: Scoping interface
	virtual mdl :: proof :: Scope* buildScope (mdl :: proof :: Scope*);

	// object :: Verifiable interface
	virtual void check();
	virtual void compress();
	virtual void prove();

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
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	enum {
		INITIAL_DOWN_STEPS_CAPACITY = 8
	};

	mdl :: proof :: Link* link_;
	vector :: proof :: Step downSteps_;
	mdl :: Proof* proof_;
	mdl :: proof :: Node* node_;
	mdl :: proof :: Scope* scope_;
};

}
}
}
}

#endif /*MDL_FORM_PROOF_STEP_CLAIM_HPP_*/
