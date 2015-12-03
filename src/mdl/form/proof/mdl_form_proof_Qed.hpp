/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_Qed.hpp                                   */
/* Description:     proof q.e.d. class                                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_PROOF_QED_HPP_
#define MDL_FORM_PROOF_QED_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/lexer/mdl_lexer.hpp"

namespace mdl {
namespace form {
namespace proof {

class Qed :
	public mdl :: proof :: Qed,
	public Scalar<Qed> {
public :
	enum {
		PROP = Token :: PROP,
		CLAIM = Token :: CLAIM
	};

	Qed
	(
		mdl :: proof :: Line*,
		const Location&,
		const mdl :: Comments*,
		const value :: Kind,
		const index :: Arity,
		const index :: Step,
		mdl :: Theory*
	);
	Qed
	(
		mdl :: proof :: Provable*,
		mdl :: proof :: Step*
	);
	Qed
	(
		const index :: Arity,
		const index :: Step,
		const value :: Kind = PROP
	);
	Qed (const mdl :: Proposition*);

	virtual ~ Qed();

	// proof :: Qed interface
	virtual index :: Arity  getIndexProp() const;
	virtual index :: Step   getIndexStep() const;
	virtual mdl :: proof :: Provable* getProp();
	virtual mdl :: proof :: Step* getStep();
	virtual const mdl :: proof :: Provable* getProp() const;
	virtual const mdl :: proof :: Step* getStep() const;

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

	// object :: Verifiable interface
	virtual void check();
	virtual bool isVerified() const;

	// object :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	friend class refactor :: redundant :: Steps;

	const Location location_;
	const mdl :: Comments* const comments_;
	const value :: Kind kind_;
	const index :: Arity  indexProp_;
	mutable index :: Step indexStep_;

	mdl :: proof :: Line* next_;
	mdl :: proof :: Line* prev_;
	mdl :: proof :: Provable* prop_;
	mdl :: proof :: Step* step_;
	mdl :: proof :: Scope* scope_;
	mutable bool isVerified_;
};

}
}
}

#endif /*MDL_FORM_PROOF_QED_HPP_*/
