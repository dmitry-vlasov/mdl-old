/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_proof_Hyp.cpp                                 */
/* Description:     hyp proof element                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_PROOF_HYP_CPP_
#define MDL_PROVER_PROOF_HYP_CPP_

namespace mdl {
namespace prover {
namespace proof {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Hyp<A> :: Hyp (const Hyp& hyp) try :
	evidence_ (hyp.evidence_),
	up_ (hyp.up_->makeCopy()),
	reference_ (NULL) {
		evidence_->getNode()->getTree()->root().add (this);
	} catch (Exception& exception) {
		Proof_ :: deleteAggregateObject (up_);
		throw exception;
	}
	template<class A>
	inline
	Hyp<A> :: Hyp
	(
		Evidence_* evidence,
		Proof_* up
	) try :
	evidence_ (evidence),
	up_ (up),
	reference_ (NULL) {
		evidence_->getNode()->getTree()->root().add (this);
	} catch (Exception& exception) {
		throw exception;
	}
	template<class A>
	Hyp<A> :: ~ Hyp() {
	}

	// prover :: Proof implementation
	template<class A>
	index :: Arity
	Hyp<A> :: getUpArity() const {
		return 1;
	}
	template<class A>
	typename Hyp<A> :: Proof_*
	Hyp<A> :: getUp (const index :: Arity i) {
		return (i == 0) ? up_ : NULL;
	}
	template<class A>
	const typename Hyp<A> :: Proof_*
	Hyp<A> :: getUp (const index :: Arity i) const {
		return (i == 0) ? up_ : NULL;
	}
	template<class A>
	void
	Hyp<A> :: checkValidity() {
		up_->checkValidity();
	}
	template<class A>
	typename Hyp<A> :: Proof_*
	Hyp<A> :: makeCopy() const {
		return new Hyp (*this);
	}
	template<class A>
	typename Hyp<A> :: Proof_ :: Kind
	Hyp<A> :: getKind() const {
		return Proof_ :: HYP;
	}
	template<class A>
	bool
	Hyp<A> :: isIdentical (const Proof_* proof) const
	{
		if (proof->getKind() != Proof_ :: HYP) {
			return false;
		}
		const Hyp* hyp = dynamic_cast<const Hyp*>(proof);
		return up_->isIdentical (hyp->up_);
	}
	template<class A>
	bool
	Hyp<A> :: isValid() const {
		return up_->isValid();
	}
	template<class A>
	void
	Hyp<A> :: resetCompilation()
	{
		reference_ = NULL;
		up_->resetCompilation();
	}
	template<class A>
	void
	Hyp<A> :: verifyIntegrity() {
		evidence_->verifyIntegrity();
	}
	template<class A>
	const typename Hyp<A> :: Evidence_*
	Hyp<A> :: getEvidence() const {
		return evidence_;
	}
	template<class A>
	index :: Step
	Hyp<A> :: getDepth() const {
		return up_->getDepth();
	}
	template<class A>
	value :: Integer
	Hyp<A> :: getCardinality() const {
		return up_->getCardinality();
	}
	template<class A>
	mdl :: proof :: Step*
	Hyp<A> :: compileStep (mdl :: proof :: Question* question)
	{
		up_->compileStep (question);
		if (!evidence_->getNode()->isRoot()) {
			reference_ = up_->getReference();
			reference_->build (question->getScope());
		}
		return up_->getStep();
	}
	template<class A>
	void
	Hyp<A> :: compileClaim (mdl :: proof :: Claim* claim)
	{
		up_->compileClaim (claim);
		if (reference_ != NULL) {
			return;
		}
		if (!evidence_->getNode()->isRoot()) {
			const Evidence_* upEvidence = up_->getEvidence();
			typedef
				typename evidence :: Prop<Allocator_>
				Prop_;
			const Prop_* prop = dynamic_cast<const Prop_*>(upEvidence);
			if (prop != NULL) {
				reference_ = new form :: proof :: Reference
				(
					claim->getLocation(),
					Token :: STEP,
					up_->getStep()->getIndex()
				);
				reference_->build (claim->getProof()->getScope());
			} else {
				reference_ = up_->getReference();
			}
		} else {
			mdl :: proof :: Qed*
				qed = new form :: proof :: Qed (claim, up_->getStep());
			claim->getProof()->addQed (qed);
		}
	}
	template<class A>
	mdl :: proof :: Reference*
	Hyp<A> :: getReference() {
		return reference_;
	}
	template<class A>
	mdl :: proof :: Step*
	Hyp<A> :: getStep() {
		return up_->getStep();
	}
	template<class A>
	const mdl :: proof :: Reference*
	Hyp<A> :: getReference() const {
		return reference_;
	}
	template<class A>
	const mdl :: proof :: Step*
	Hyp<A> :: getStep() const {
		return up_->getStep();
	}
	template<class A>
	void
	Hyp<A> :: showAsTerm(String& string) const {
		up_->showAsTerm (string);
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;

	// object :: Object interface
	template<class A>
	void
	Hyp<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Hyp<A> :: getVolume() const {
		return 0;
	}
	template<class A>
	Size_t
	Hyp<A> :: getSizeOf() const {
		return sizeof (Hyp);
	}
	template<class A>
	void
	Hyp<A> :: show (String& string) const
	{
		string << "PROOF_HYP: ";
		if (reference_ != NULL) {
			string << *reference_;
		}
	}
}
}
}

#endif /*MDL_PROVER_PROOF_HYP_CPP_*/
