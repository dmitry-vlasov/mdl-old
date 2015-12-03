/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_Proof_Timing.cpp                          */
/* Description:     timer for proof compression                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_PROOF_PROOF_TIMING_CPP_
#define MDL_FORM_PROOF_PROOF_TIMING_CPP_

namespace mdl {
namespace form {
namespace proof {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Proof :: Timing :: Timing (const mdl :: Proof* proof) :
	proof_ (proof),
	timer_ () {
	}
	inline
	Proof :: Timing :: ~ Timing() {
	}

	inline Time
	Proof :: Timing :: calculateTimeLimit (const bool exactAssertion)
	{
		value :: Long proveActsLeft = estimateProveActsLeft (exactAssertion);
		proveActsLeft = (proveActsLeft == 0) ? 1 : proveActsLeft;
		return estimateClocksPerProveAct (proveActsLeft);
	}
	inline void
	Proof :: Timing :: incrementProveActs() {
		proveActsDone_ += estimateProveActs();
	}
	inline Timer&
	Proof :: Timing :: timer() {
		return timer_;
	}
	inline const mdl :: Timer&
	Proof :: Timing :: getTimer() const {
		return timer_;
	}

	// object :: Object implementation
	void
	Proof :: Timing :: commitSuicide() {
		delete this;
	}
	Size_t
	Proof :: Timing :: getVolume() const {
		return timer_.getVolume();
	}
	Size_t
	Proof :: Timing :: getSizeOf() const {
		return sizeof (Timer);
	}
	void
	Proof :: Timing :: show (String& string) const {
		timer_.show (string);
	}

	/****************************
	 *		Private members
	 ****************************/

	value :: Long
	Proof :: Timing :: estimateProveActsLeft (const bool exactAssertion)
	{
		if (exactAssertion) {
			return estimateProveActs();
		} else {
			value :: Long stepsLeft = 0;
			const index :: Assertion
				index = proof_->getScope()->getAssertion()->getIndex();
			for (index :: Assertion i = index; i < Math :: assertions()->getSize(); ++ i) {
				const mdl :: Assertion* const
					assertion = Math :: assertions()->get (i);
				if (Config :: compress() && Refiner :: isCompressable (assertion)) {
					stepsLeft += estimateProveActs (assertion);
				}
				if (Config :: prove()) {
					stepsLeft += estimateProveActs (assertion);
				}
			}
			return stepsLeft;
		}
	}
	index :: Step
	Proof :: Timing :: estimateProveActs()
	{
		if (Config :: compress()) {
			const index :: Step
				length = proof_->getLength();
			return length * (length - 1) / 2;
		}
		if (Config :: prove()) {
			index :: Step questionCount = 0;
			for (index :: Step i = 0; i < proof_->getLength(); ++ i) {
				const mdl :: proof :: Step* const
					step = proof_->getStep (i);
				if (step->getClass() == mdl :: proof :: Step :: QUESTION) {
					++ questionCount;
				}
			}
			return questionCount;
		}
		return 0;
	}
	index :: Step
	Proof :: Timing :: estimateProveActs (const mdl :: Assertion* const assertion)
	{
		if (Config :: compress() && (assertion->getKind() == mdl :: Assertion :: THEOREM)) {
			const form :: block :: Theorem* const
				theorem = dynamic_cast<const form :: block :: Theorem*>(assertion);
			const vector :: Proof&
				proofVector = theorem->getProofVector();
			index :: Step stepsToProve = 0;
			for (value :: Integer i = 0; i < proofVector.getSize(); ++ i) {
				const mdl :: Proof* const
					proof = proofVector.getValue (i);
				const index :: Step
					length = proof->getLength();
				stepsToProve += length * (length - 1) / 2;
			}
			return stepsToProve;
		}
		/*if (Config :: prove() && (assertion->getKind() == mdl :: Assertion :: PROBLEM)) {
			const form :: block :: Problem* const
				problem = dynamic_cast<const form :: block :: Problem*>(assertion);
			const vector :: Proof&
				proofVector = problem->getProofVector();
			index :: Step questionCount = 0;
			for (value :: Integer i = 0; i < proofVector.getSize(); ++ i) {
				const mdl :: Proof* const
					proof = proofVector.getValue (i);
				for (index :: Step i = 0; i < proof->getLength(); ++ i) {
					const mdl :: proof :: Step* const
						step = proof->getStep (i);
					if (step->getClass() == mdl :: proof :: Step :: QUESTION) {
						++ questionCount;
					}
				}
			}
			return questionCount;
		}*/
		return 0;
	}
	Time
	Proof :: Timing :: estimateClocksPerProveAct (value :: Long proveActsLeft)
	{
		if (proveActsTotal_ == Undefined<value :: Long> :: getValue()) {
			proveActsTotal_ = proveActsLeft;
		}
		const Time timeTotal = Config :: getTimeLimit();
		const Time timePassed =
			Config :: prove() ?
			Engine :: getEngine()->getTimers().prove().getSeconds() :
			Engine :: getEngine()->getTimers().compress().getSeconds();
		const Time timeLeft =
			(timeTotal > timePassed) ?
			timeTotal - timePassed :
			0;
		Time result = timeLeft/ proveActsLeft;

		if (averageClocksForProve_ == Undefined<Time> :: getValue()) {
			averageClocksForProve_ = result;
		}

		const value :: Long estimatedClocksLeft =
			(proveActsTotal_ - proveActsDone_) * averageClocksForProve_;
		Time exactClocksLeft = timeLeft;

		value :: Long clockDelta =
			(exactClocksLeft > estimatedClocksLeft) ?
			exactClocksLeft - estimatedClocksLeft :
			0;
		result += clockDelta;
		return result;
	}


	/************************************
	 *		Private static attributes
	 ************************************/

	value :: Long
		Proof :: Timing :: proveActsTotal_ = Undefined<value :: Long> :: getValue();
	value :: Long
		Proof :: Timing :: proveActsDone_ = 0;
	Time
		Proof :: Timing :: averageClocksForProve_ = Undefined<Time> :: getValue();
}
}
}

#endif /*MDL_FORM_PROOF_PROOF_TIMING_CPP_*/
