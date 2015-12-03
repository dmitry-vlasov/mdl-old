/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_proof_Ref.cpp                                 */
/* Description:     reference proof element                                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_PROOF_REF_CPP_
#define MDL_PROVER_PROOF_REF_CPP_

namespace mdl {
namespace prover {
namespace proof {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Ref<A> :: Ref (const Ref& ref) try :
	evidence_ (ref.evidence_),
	substitution_ (Substitution_ :: create (ref.substitution_)),
	up_ (ref.up_->makeCopy()),
	reference_ (NULL) {
		evidence_->getNode()->getTree()->root().add (this);
	} catch (Exception& exception) {
		Proof_ :: deleteAggregateObject (substitution_);
		throw exception;
	}
	template<class A>
	inline
	Ref<A> :: Ref
	(
		Evidence_* evidence,
		Substitution_* substitution,
		Proof_* up
	) try :
	evidence_ (evidence),
	substitution_ (Substitution_ :: create (substitution)),
	up_ (up),
	reference_ (NULL) {
		evidence_->getNode()->getTree()->root().add (this);
	} catch (Exception& exception) {
		Proof_ :: deleteAggregateObject (substitution_);
		throw exception;
	}
	template<class A>
	Ref<A> :: ~ Ref() {
		Proof_ :: deleteAggregateObject (substitution_);
	}

	// prover :: Proof implementation
	template<class A>
	index :: Arity
	Ref<A> :: getUpArity() const {
		return 1;
	}
	template<class A>
	typename Ref<A> :: Proof_*
	Ref<A> :: getUp (const index :: Arity i) {
		return (i == 0) ? up_ : NULL;
	}
	template<class A>
	const typename Ref<A> :: Proof_*
	Ref<A> :: getUp (const index :: Arity i) const {
		return (i == 0) ? up_ : NULL;
	}
	template<class A>
	void
	Ref<A> :: checkValidity() {
		up_->checkValidity();
	}
	template<class A>
	typename Ref<A> :: Proof_*
	Ref<A> :: makeCopy() const {
		return new Ref (*this);
	}
	template<class A>
	typename Ref<A> :: Proof_ :: Kind
	Ref<A> :: getKind() const {
		return Proof_ :: REF;
	}
	template<class A>
	bool
	Ref<A> :: isIdentical (const Proof_* proof) const
	{
		if (proof->getKind() != Proof_ :: REF) {
			return false;
		}
		const Ref* ref = dynamic_cast<const Ref*>(proof);
		/*if (evidence_ != ref->evidence_) {
			return false;
		}*/
		if (!substitution_->isIdentical (ref->substitution_)) {
			return false;
		}
		return up_->isIdentical (ref->up_);
	}
	template<class A>
	bool
	Ref<A> :: isValid() const {
		return up_->isValid();
	}
	template<class A>
	void
	Ref<A> :: resetCompilation()
	{
		reference_ = NULL;
		up_->resetCompilation();
	}
	template<class A>
	void
	Ref<A> :: verifyIntegrity() {
		evidence_->verifyIntegrity();
	}
	template<class A>
	const typename Ref<A> :: Evidence_*
	Ref<A> :: getEvidence() const {
		return evidence_;
	}
	template<class A>
	index :: Step
	Ref<A> :: getDepth() const {
		return up_->getDepth();
	}
	template<class A>
	value :: Integer
	Ref<A> :: getCardinality() const {
		return up_->getCardinality();
	}
	template<class A>
	mdl :: proof :: Step*
	Ref<A> :: compileStep (mdl :: proof :: Question* question)
	{
		up_->compileStep (question);
		reference_ = up_->getReference();
		return up_->getStep();
	}
	template<class A>
	void
	Ref<A> :: compileClaim (mdl :: proof :: Claim* claim)
	{
		if (reference_ != NULL) {
			return;
		}
		up_->compileClaim (claim);
		reference_ = up_->getReference();

		/*if (up_->getReference() == NULL) {
			up_->compileClaim (claim);
			reference_ = up_->getReference();
		} else {
			const mdl :: proof :: Reference* const
				reference = up_->getReference();
			reference_ = new form :: proof :: Reference (reference);
		}*/
	}
	template<class A>
	mdl :: proof :: Reference*
	Ref<A> :: getReference() {
		return reference_;
	}
	template<class A>
	mdl :: proof :: Step*
	Ref<A> :: getStep() {
		return up_->getStep();
	}
	template<class A>
	const mdl :: proof :: Reference*
	Ref<A> :: getReference() const {
		return reference_;
	}
	template<class A>
	const mdl :: proof :: Step*
	Ref<A> :: getStep() const {
		return up_->getStep();
	}
	template<class A>
	void
	Ref<A> :: showAsTerm(String& string) const {
		up_->showAsTerm (string);
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;

	// object :: Object interface
	template<class A>
	void
	Ref<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Ref<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += Proof_ :: getAggregateVolume (substitution_);
		return volume;
	}
	template<class A>
	Size_t
	Ref<A> :: getSizeOf() const {
		return sizeof (Ref);
	}
	template<class A>
	void
	Ref<A> :: show (String& string) const
	{
		string << "PROOF_REF: ";
		if (substitution_ == NULL) {
			string << "{ }";
		} else {
			string << *substitution_;
		}
		string << ", ";
		if (reference_ != NULL) {
			string << *reference_;
		}
	}
}
}
}

#endif /*MDL_PROVER_PROOF_REF_CPP_*/
