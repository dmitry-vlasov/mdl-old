/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_guess_Question.hpp                         */
/* Description:     unknown step inference                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_PROOF_STEP_QUESTION_HPP_
#define MDL_FORM_PROOF_STEP_QUESTION_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/form/proof/mdl_form_proof_Step.hpp"

namespace mdl {
namespace form {
namespace proof {
namespace step {

class Question :
	public mdl :: proof :: Question,
	public proof :: Step,
	public Scalar<Question> {
	typedef proof :: Step Ancestor_;
public :
	Question
	(
		mdl :: proof :: Line*,
		const Location&,
		const mdl :: Comments* const,
		index :: Step,
		mdl :: Identificator*,
		array :: Expression*,
		mdl :: Theory*,
		mdl :: proof :: Scope* = NULL
	);
	Question (proof :: Step* answer);
	Question
	(
		index :: Step index,
		array :: Expression* expression,
		const mdl :: proof :: Step* hint = NULL
	);
	Question (mdl :: Proposition*);
	virtual ~ Question();

	// proof :: step :: Question interface
	virtual void compress (const Time timeLimit);
	virtual void prove (const Time timeLimit);
	virtual void clear();
	virtual bool isProved() const;
	virtual void confirmAnswer (mdl :: proof :: Step*);
	virtual void confirmGuess();
	virtual void rejectGuess();
	virtual mdl :: proof :: Step* getAnswer();
	virtual mdl :: proof :: Step* getGuess();
	virtual const mdl :: proof :: Step* getHint();
	virtual const mdl :: proof :: Step* getAnswer() const;
	virtual const mdl :: proof :: Step* getGuess() const;
	virtual const mdl :: proof :: Step* getHint() const;

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

	// object :: Verifiable interface
	virtual void check();
	virtual void compress();
	virtual void prove();

	// object :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;
	virtual bool lookup() const;
	virtual const object :: Writable* find() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	friend class form :: proof :: Step;
	bool isProved_;
	mdl :: proof :: Step* answer_;
	mdl :: proof :: Step* guess_;
	const mdl :: proof :: Step* hint_;
};

}
}
}
}

#endif /*MDL_FORM_PROOF_STEP_QUESTION_HPP_*/
