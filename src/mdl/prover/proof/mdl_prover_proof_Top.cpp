/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_proof_Top.cpp                                 */
/* Description:     top (premise) proof element                              */
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
namespace proof {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Top<A> :: Top (const Top& top) try :
	evidence_ (top.evidence_),
	hypothesis_ (NULL),
	reference_ (NULL) {
		evidence_->getNode()->getTree()->root().add (this);
	} catch (Exception& exception) {
		throw exception;
	}
	template<class A>
	inline
	Top<A> :: Top (Evidence_* evidence) try :
	evidence_ (dynamic_cast<Top_*>(evidence)),
	hypothesis_ (NULL),
	reference_ (NULL) {
		evidence_->getNode()->getTree()->root().add (this);
	} catch (Exception& exception) {
		throw exception;
	}
	template<class A>
	Top<A> :: ~ Top() {
	}

	// prover :: Proof implementation
	template<class A>
	index :: Arity
	Top<A> :: getUpArity() const {
		return 0;
	}
	template<class A>
	typename Top<A> :: Proof_*
	Top<A> :: getUp (const index :: Arity i) {
		return NULL;
	}
	template<class A>
	const typename Top<A> :: Proof_*
	Top<A> :: getUp (const index :: Arity i) const {
		return NULL;
	}
	template<class A>
	void
	Top<A> :: checkValidity() {
	}
	template<class A>
	typename Top<A> :: Proof_*
	Top<A> :: makeCopy() const {
		return new Top (*this);
	}
	template<class A>
	typename Top<A> :: Proof_ :: Kind
	Top<A> :: getKind() const {
		return Proof_ :: TOP;
	}
	template<class A>
	bool
	Top<A> :: isIdentical (const Proof_* proof) const
	{
		if (proof->getKind() != Proof_ :: TOP) {
			return false;
		}
		const Top* top = dynamic_cast<const Top*>(proof);
		return (evidence_->premise_ == top->evidence_->premise_);
	}
	template<class A>
	bool
	Top<A> :: isValid() const {
		return true;
	}
	template<class A>
	void
	Top<A> :: resetCompilation()
	{
		reference_ = NULL;
		hypothesis_ = NULL;
	}
	template<class A>
	void
	Top<A> :: verifyIntegrity() {
		evidence_->verifyIntegrity();
	}
	template<class A>
	const typename Top<A> :: Evidence_*
	Top<A> :: getEvidence() const {
		return evidence_;
	}
	template<class A>
	index :: Step
	Top<A> :: getDepth() const {
		return 0;
	}
	template<class A>
	value :: Integer
	Top<A> :: getCardinality() const {
		return 0;
	}
	template<class A>
	mdl :: proof :: Step*
	Top<A> :: compileStep (mdl :: proof :: Question* question)
	{
		const index :: Step
			index = evidence_->premise_->getIndex();
		reference_ = new form :: proof :: Reference
		(
			question->getLocation(),
			evidence_->premise_->getKind(),
			index,
			evidence_->premise_
		);
		reference_->build (question->getScope());
		return question;
	}
	template<class A>
	void
	Top<A> :: compileClaim (mdl :: proof :: Claim* claim)
	{
		if (reference_ != NULL) {
			return;
		}
		index :: Arity
			refIndex = claim->getLink()->getReferences()->find (evidence_->premise_);

		if (refIndex == index :: undefined :: ARITY) {
			const index :: Step
				hypIndex = evidence_->premise_->getIndex();
			hypothesis_ = new form :: proof :: Reference
			(
				claim->getLocation(),
				evidence_->premise_->getKind(),
				hypIndex,
				evidence_->premise_
			);
			hypothesis_->build (claim->getScope());
			refIndex = claim->getLink()->getReferences()->getArity();
			claim->getLink()->getReferences()->add (hypothesis_);
		} else {
			hypothesis_ = claim->getLink()->getReferences()->get (refIndex);
		}
		reference_ = new form :: proof :: Reference
		(
			claim->getLocation(),
			Token :: HYP,
			refIndex,
			evidence_->premise_
		);
		reference_->build (claim->getScope());
	}
	template<class A>
	mdl :: proof :: Reference*
	Top<A> :: getReference() {
		return reference_;
	}
	template<class A>
	mdl :: proof :: Step*
	Top<A> :: getStep() {
		return NULL;
	}
	template<class A>
	const mdl :: proof :: Reference*
	Top<A> :: getReference() const {
		return reference_;
	}
	template<class A>
	const mdl :: proof :: Step*
	Top<A> :: getStep() const {
		return NULL;
	}
	template<class A>
	void
	Top<A> :: showAsTerm(String& string) const {
		evidence_->premise_->replicateReference (string);
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;

	// object :: Object implementation
	template<class A>
	void
	Top<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Top<A> :: getVolume() const {
		return 0;
	}
	template<class A>
	Size_t
	Top<A> :: getSizeOf() const {
		return sizeof (Top);
	}
	template<class A>
	void
	Top<A> :: show (String& string) const
	{
		string << "PROOF_TOP: ";
		if (reference_ != NULL) {
			string << *reference_<< ", ";
		}
		string << "premise " << *evidence_->premise_;
	}
}
}
}


