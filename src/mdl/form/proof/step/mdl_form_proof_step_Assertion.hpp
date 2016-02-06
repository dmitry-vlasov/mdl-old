/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_step_Assertion.hpp                        */
/* Description:     assertion step inference                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/form/proof/mdl_form_proof_Step.hpp"

namespace mdl {
namespace form {
namespace proof {
namespace step {

class Assertion :
	public mdl :: proof :: Assertion,
	public form :: proof :: Step,
	public Scalar<Assertion> {
public :
	Assertion
	(
		mdl :: proof :: Line*,
		const Location&,
		const mdl :: Comments*,
		const index :: Step,
		mdl :: Identificator*,
		mdl :: proof :: Link*,
		array :: Expression*,
		mdl :: Theory*
	);
	Assertion
	(
		mdl :: proof :: Step*,
		const index :: Step,
		mdl :: proof :: Link*,
		array :: Expression*
	);
	virtual ~ Assertion();

	// proof :: Assertion interface
	virtual array :: Substitution* getSubstitution();
	virtual const array :: Substitution* getSubstitution() const;
	virtual void collectExperience();

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

	// proof :: Line interface
	virtual void incIndex (const index :: Step);
	virtual void decIndex (const index :: Step);
	virtual void setNext (mdl :: proof :: Line*);
	virtual void setPrev (mdl :: proof :: Line*);
	virtual mdl :: proof :: Line* getNext();
	virtual mdl :: proof :: Line* getPrev();
	virtual const mdl :: proof :: Line* getNext() const;
	virtual const mdl :: proof :: Line* getPrev() const;

	// object :: Scoping interface
	virtual mdl :: proof :: Scope* buildScope (mdl :: proof :: Scope*);
	virtual void setScope (mdl :: proof :: Scope*);
	virtual mdl :: proof :: Scope* getScope();
	virtual const mdl :: proof :: Scope* getScope() const;

	// object :: Expressive interface
	virtual const array :: Expression* getExpression() const;
	virtual const mdl :: Type* getType() const;

	// object :: Verifiable interface
	virtual void check();

	// object :: Buildable interface
	virtual void build();

	// object :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;
	virtual bool lookup() const;
	virtual const object :: Writable* find() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

protected :
	void translateVariables (String& string) const;

	void checkProposition() const;
	void checkHypotheses() const;
	void checkDisjoineds() const;

	void addPositiveExperience();
	void addNegativeExperience();

	void referenceToUnverifiedError() const;
	void propositionUnificationError() const;
	void hypothesisUnificationError (const index :: Arity) const;

	enum {
		INITIAL_DOWN_STEPS_CAPACITY = 8
	};

	mdl :: proof :: Link* link_;
	vector :: proof :: Step downSteps_;
	array :: Substitution* substitution_;
};

}
}
}
}


