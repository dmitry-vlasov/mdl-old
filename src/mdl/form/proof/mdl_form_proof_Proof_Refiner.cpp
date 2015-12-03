/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_Proof_Refiner.cpp                         */
/* Description:     proof refining utility                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_PROOF_PROOF_REFINER_CPP_
#define MDL_FORM_PROOF_PROOF_REFINER_CPP_

namespace mdl {
namespace form {
namespace proof {

	/****************************
	 *		Public members
	 ****************************/

	inline index :: Assertion
	Proof :: Refiner :: getCompressedCount() {
		return compressedCount_;
	}
	inline index :: Step
	Proof :: Refiner :: getOriginalProofLength() {
		return originalProofLength_;
	}
	inline index :: Step
	Proof :: Refiner :: getCompressedProofLength() {
		return compressedProofLength_;
	}
	inline double
	Proof :: Refiner :: getCompressionFactor() {
		return compressionFactor_;
	}

	bool
	Proof :: Refiner :: isCompressable (const mdl :: Assertion* provable)
	{
		init();
		if (Config :: getCompressionFactor() == 1) {
			return true;
		}
		const index :: Assertion index = provable->getIndex();
		if (index < Config :: getCompressionFactor()) {
			return false;
		}
		const index :: Assertion k = (index / Config :: getCompressionFactor()) - 1;
		return (provable == theoremVector_->getValue (k));
	}
	void
	Proof :: Refiner :: beforeCompression (const mdl :: Proof* proof)
	{
		init();
		originalProofLength_ = proof->getLength();
	}
	void
	Proof :: Refiner :: afterCompression (const mdl :: Proof* proof)
	{
		const index :: Step
			length = proof->getLength();
		compressedProofLength_ = length;
		++ compressedCount_;
		compressionFactor_ =
			static_cast<double>(originalProofLength_) /
			static_cast<double>(compressedProofLength_);
	}

	inline void
	Proof :: Refiner :: init()
	{
		if (averageProofLength_ != NULL) {
			return;
		}
		calculateAverageLengthVector();
		calculateTheoremVector();
	}
	inline void
	Proof :: Refiner :: release()
	{
		if (averageProofLength_ == NULL) {
			return;
		}
		delete averageProofLength_;
		delete theoremVector_;
		averageProofLength_ = NULL;
		theoremVector_ = NULL;
	}
	inline Size_t
	Proof :: Refiner :: getVolume()
	{
		Size_t volume = 0;
		if (averageProofLength_ != NULL) {
			volume += averageProofLength_->getVolume();
			volume += averageProofLength_->getSizeOf();
		}
		if (theoremVector_ != NULL) {
			volume += theoremVector_->getVolume();
			volume += theoremVector_->getSizeOf();
		}
		return volume;
	}
	inline Size_t
	Proof :: Refiner :: getSizeOf() {
		return sizeof (Refiner);
	}
	inline void
	Proof :: Refiner :: show (String&) {
	}

	/****************************
	 *		Private members
	 ****************************/

	inline void
	Proof :: Refiner :: calculateAverageLengthVector()
	{
		if (Config :: getCompressionFactor() == 1) {
			return;
		}
		const index :: Assertion
			assertionsTotalCount = Math :: assertions()->getSize();
		const index :: Assertion
			assertionsCompressCount = assertionsTotalCount / Config :: getCompressionFactor();
		averageProofLength_ = new vector :: value :: Integer (assertionsCompressCount);

		index :: Step stepCount = 0;
		index :: Step proofCount = 0;
		for (index :: Assertion i = 0; i < assertionsTotalCount; ++ i) {
			if ((i > 0) && (i % Config :: getCompressionFactor() == 0)) {
				const index :: Step
					averageProofLength = stepCount / proofCount;
				averageProofLength_->add (averageProofLength);
				stepCount = 0;
				proofCount = 0;
			}
			const mdl :: Assertion* const
				assertion = Math :: assertions()->get (i);
			if (assertion->getKind() == mdl :: Assertion :: THEOREM) {
				const form :: block :: Theorem* const
					theorem = dynamic_cast<const form :: block :: Theorem*>(assertion);
				const vector :: Proof&
					proofVector = theorem->getProofVector();
				for (value :: Integer i = 0; i < proofVector.getSize(); ++ i) {
					const mdl :: Proof* const
						proof = proofVector.getValue (i);
					const index :: Step
						length = proof->getLength();
					stepCount += length;
				}
				proofCount += proofVector.getSize();
			}
		}
	}
	inline void
	Proof :: Refiner :: calculateTheoremVector()
	{
		if (Config :: getCompressionFactor() == 1) {
			return;
		}
		const index :: Assertion
			assertionsTotalCount = Math :: assertions()->getSize();
		const index :: Assertion
			assertionsCompressCount = assertionsTotalCount / Config :: getCompressionFactor();
		theoremVector_ = new Vector_ (assertionsCompressCount);

		bool entityChosen = true;
		for (index :: Assertion i = 0; i < assertionsTotalCount; ++ i) {
			const index :: Assertion
				k = i / Config :: getCompressionFactor();
			const index :: Step
				averageLength = averageProofLength_->getValue (k - 1);
			const index :: Assertion
				rest = i % Config :: getCompressionFactor();
			if (rest == 0) {
				entityChosen = false;
			}
			if ((k == 0) || entityChosen) {
				continue;
			}
			const mdl :: Assertion* const
				assertion = Math :: assertions()->get (i);
			if (assertion->getKind() == mdl :: Assertion :: THEOREM) {
				const form :: block :: Theorem* const
					theorem = dynamic_cast<const form :: block :: Theorem*>(assertion);
				const vector :: Proof&
					proofVector = theorem->getProofVector();
				for (value :: Integer i = 0; i < proofVector.getSize(); ++ i) {
					const mdl :: Proof* const
						proof = proofVector.getValue (i);
					const index :: Step
						currentLength = proof->getLength();
					if (goodLength (averageLength, currentLength)) {
						theoremVector_->add (assertion);
						entityChosen = true;
						break;
					}
				}
			}
		}
	}
	inline bool
	Proof :: Refiner :: goodLength
	(
		const index :: Step averageLength,
		const index :: Step testedLength
	)
	{
		if (averageLength == 0) {
			return true;
		}
		index :: Step deltaLength =
			(testedLength > averageLength) ?
			testedLength - averageLength :
			averageLength - testedLength;
		if (deltaLength < COMPRESSION_LOWER_BOUNDARY_THRESHOLD) {
			return true;
		}
		const bool
			good = (deltaLength * 100 / averageLength) < COMPRESSION_PERCENT_THRESHOLD;
		return good;
	}

	/************************************
	 *		Private static attributes
	 ************************************/

	index :: Assertion
		Proof :: Refiner :: compressedCount_ = 0;
	index :: Step
		Proof :: Refiner :: originalProofLength_ = 0;
	index :: Step
		Proof :: Refiner :: compressedProofLength_ = 0;
	double
		Proof :: Refiner :: compressionFactor_ = 0;

	Proof :: Refiner :: Vector_*
		Proof :: Refiner :: theoremVector_ = NULL;
	vector :: value :: Integer*
		Proof :: Refiner :: averageProofLength_ = NULL;
}
}
}

#endif /*MDL_FORM_PROOF_PROOF_REFINER_CPP_*/
