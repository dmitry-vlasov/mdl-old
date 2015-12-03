/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_Step.hpp                                  */
/* Description:     proof step                                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_PROOF_STEP_HPP_
#define MDL_FORM_PROOF_STEP_HPP_

#include "mdl/interface/mdl_interface.hpp"

namespace mdl {
namespace form {
namespace proof {

class Step : virtual public mdl :: proof :: Step {
public :
	Step
	(
		mdl :: proof :: Line*,
		const Location&,
		const mdl :: Comments*,
		index :: Step,
		mdl :: Identificator*,
		array :: Expression*,
		mdl :: Theory* theory,
		mdl :: proof :: Scope* = NULL
	);
	Step (mdl :: proof :: Step*);
	Step
	(
		mdl :: proof :: Step*,
		index :: Step,
		array :: Expression*
	);
	Step
	(
		index :: Step,
		array :: Expression*
	);
	Step (mdl :: Proposition*);
	virtual ~ Step();

	// proof :: Step interface
	virtual Class getClass() const = 0;
	virtual mdl :: proof :: Question* questionSelf();
	virtual void addReference (mdl :: proof :: Reference*) = 0;
	virtual void addDown (mdl :: proof :: Step*) = 0;
	virtual index :: Arity getUpArity() const = 0;
	virtual index :: Arity getDownArity() const = 0;

	virtual mdl :: proof :: Link* getLink() = 0;
	virtual mdl :: proof :: Node* getUp (const index :: Arity) = 0;
	virtual mdl :: proof :: Step* getDown (const index :: Arity) = 0;

	virtual const mdl :: proof :: Link* getLink() const = 0;
	virtual const mdl :: proof :: Node* getUp (const index :: Arity) const = 0;
	virtual const mdl :: proof :: Step* getDown (const index :: Arity) const = 0;

	// proof :: Node interface
	virtual Kind getKind() const;
	virtual index :: Step getIndex() const;
	virtual void replicateReference (String&) const = 0;
	virtual void translateReference (String&) const = 0;

	// proof :: Line interface
	virtual Sort getSort() const;
	virtual void incIndex (const index :: Step);
	virtual void decIndex (const index :: Step);
	virtual void setNext (mdl :: proof :: Line*);
	virtual void setPrev (mdl :: proof :: Line*);
	virtual mdl :: proof :: Line* getNext();
	virtual mdl :: proof :: Line* getPrev();
	virtual const mdl :: proof :: Line* getNext() const;
	virtual const mdl :: proof :: Line* getPrev() const;
	virtual const Location& getLocation() const;

	// object :: Scoping interface
	virtual mdl :: proof :: Scope* buildScope (mdl :: proof :: Scope*);
	virtual void setScope (mdl :: proof :: Scope*);
	virtual mdl :: proof :: Scope* getScope();
	virtual const mdl :: proof :: Scope* getScope() const;

	// object :: Expressive interface
	virtual array :: Expression* getExpression();
	virtual mdl :: Type* getType();
	virtual const array :: Expression* getExpression() const;
	virtual const mdl :: Type* getType() const;

	// object :: Verifiable interface
	virtual void reprove();
	virtual bool isVerified() const;

	// object :: Writable interface
	virtual void translate (String&) const = 0;
	virtual void replicate (String&) const = 0;
	virtual bool lookup() const;
	virtual object :: Writable* find();
	virtual const object :: Writable* find() const;

	// object :: Object interface
	virtual void commitSuicide() = 0;
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

protected :
	friend class refactor :: redundant :: Steps;

	typedef
		form :: proof :: Step
		Step_;

	const Location location_;
	mdl :: Theory* theory_;
	const mdl :: Comments* comments_;
	index :: Step index_;
	mdl :: Identificator* identificator_;
	mdl :: Type* type_;
	array :: Expression* expression_;
	mdl :: proof :: Line* next_;
	mdl :: proof :: Line* prev_;
	mdl :: proof :: Scope* scope_;
	bool isVerified_;
};

}
}
}

#endif /*MDL_FORM_PROOF_STEP_HPP_*/
