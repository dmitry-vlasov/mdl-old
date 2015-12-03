/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_tree_Root.cpp                                 */
/* Description:     root of the tree                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_ROOT_ROOT_CPP_
#define MDL_PROVER_ROOT_ROOT_CPP_

namespace mdl {
namespace prover {
namespace tree {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	inline
	Root<A> :: Root (Tree_* tree) :
	tree_ (tree),
	buffer_ (INITIAL_BUFFER_CAPACITY),
	rootVector_ (INITIAL_PROOF_VECTOR_CAPACITY),
	proofVector_ (INITIAL_PROOF_VECTOR_CAPACITY),
	stepVector_ (INITIAL_PROOF_VECTOR_CAPACITY),
	invalidVector_ (INITIAL_PROOF_VECTOR_CAPACITY),
	unusedVector_ (INITIAL_PROOF_VECTOR_CAPACITY),
	isBlocked_ (false) {
	}
	template<class A>
	Root<A> :: ~ Root() {
	}

	// prover :: Root implementation
	template<class A>
	inline value :: Integer
	Root<A> :: getSize() const {
		return stepVector_.getSize();
	}
	template<class A>
	inline const mdl :: proof :: Step*
	Root<A> :: getProof (const value :: Integer i) const {
		return stepVector_.getValue (i);
	}
	template<class A>
	void
	Root<A> :: update()
	{
		constructProofs();
		if (rootVector_.getSize() > 0) {
			#ifdef VERIFY_PROOF_STEPS
			verifyCompilation (false);
			#endif
			#ifdef DEBUG_PROVER_ROOT
			verifyCompilation (false);
			#endif
			tree_->getTimers()->recount();
		}
	}
	template<class A>
	inline bool
	Root<A> :: isProved()
	{
		constructProofs();
		return (rootVector_.getSize() > 0);
	}
	template<class A>
	inline void
	Root<A> :: add (Evidence_* evidence) {
		buffer_.add (evidence);
	}
	template<class A>
	void
	Root<A> :: add (Proof_* proof)
	{
		if (isBlocked_) {
			unusedVector_.add (proof);
		} else {
			proofVector_.add (proof);
		}
		#ifdef DEBUG_PROVER_PROOF
		proof->verifyIntegrity();
		#endif
	}
	template<class A>
	void
	Root<A> :: verifyCompilation (const bool forceOutput)
	{
		verifyDuplicateProofs();
		value :: Integer failed = 0;
		value :: Integer succeded = 0;
		if (forceOutput || (Config :: verbosity() > Config :: VERBOSE_MED)) {
			//std :: cout << "problem:" << std :: endl;
			//std :: cout << *Prover :: getProblem()  << std :: endl;
			std :: cout << "proofs found: " << stepVector_.getSize() << std :: endl;
			std :: cout << "===============================" << std :: endl;
		}
		for (value :: Integer i = 0; i < stepVector_.getSize(); ++ i) {
			//Proof_* proof = proofVector_.getValue (i);
			mdl :: proof :: Step* claim = stepVector_.getValue (i);
			if (forceOutput || (Config :: verbosity() > Config :: VERBOSE_MED)) {
				std :: cout << "proof " << i << " is verifying... ";
			}
			//std :: cout << "claim " << i << " is verifying... " << std :: endl;
			//std :: cout << *claim << std :: endl;
 			if (verifyProof (claim, true)) {
				++ succeded;
				if (forceOutput || (Config :: verbosity() > Config :: VERBOSE_MED)) {
					std :: cout << "ok:" << std :: endl;
					std :: cout << *claim << std :: endl;
				}
			} else {
				++ failed;
				if (Config :: verbosity() >= Config :: VERBOSE_MED) {
					//std :: cout << "problem:" << std :: endl;
					//std :: cout << *Prover :: getProblem()  << std :: endl;
					std :: cout << "proof " << i << " is verifying... ";
				}
				std :: cout << "failed:" << std :: endl;
				std :: cout << *claim << std :: endl;
				Counter :: switchOn();
				Counter :: set();
				//proof->verifyIntegrity();
				Counter :: switchOff();
				//verifyProof (claim, true);
			}
		}
		if (forceOutput || (Config :: verbosity() > Config :: VERBOSE_MED)) {
			//std :: cout << "===============================" << std :: endl;
			std :: cout << "failed = " << failed << std :: endl;
			std :: cout << "succeded = " << succeded << std :: endl;
			std :: cout << std :: endl << std :: endl << std :: endl << std :: endl;
		}
	}
	template<class A>
	bool
	Root<A> :: hasValidProofs() const
	{
		for (value :: Integer i = 0; i < rootVector_.getSize(); ++ i) {
			if (rootVector_.getValue (i)->isValid()) {
				return true;
			}
		}
		return false;
	}
	template<class A>
	mdl :: proof :: Step*
	Root<A> :: takeProof (const value :: Integer index)
	{
		if (index >= stepVector_.getSize()) {
			return NULL;
		} else {
			mdl :: proof :: Step* proof = stepVector_.getValue (index);
			stepVector_.remove (index);
			return proof;
		}
	}
	template<class A>
	mdl :: proof :: Step*
	Root<A> :: takeBestProof()
	{
		const value :: Integer index = getLeastProofIndex();
		return takeProof (index);
	}
	template<class A>
	bool
	Root<A> :: contains (const Proof_* proof_1) const
	{
		for (value :: Integer i = 0; i < rootVector_.getSize(); ++ i) {
			const Proof_* proof_2 = rootVector_.getValue (i);
			if (proof_2->isIdentical (proof_1)) {
				return true;
			}
		}
		return false;
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;
using manipulator :: iterate;

	template<class A>
	void
	Root<A> :: showInfo (String& string, const int indent) const
	{
		string << iterate << indent << tab;
		string << "<root>" << endLine;

		for (value :: Integer i = 0; i < stepVector_.getSize(); ++ i) {
			const mdl :: proof :: Step* step = stepVector_.getValue(i);
			string << iterate << (indent + 1) << tab;
			string << "<proof>";
			string << "<![CDATA[" << endLine;
			step->replicate (string);
			string << iterate << (indent + 1) << tab;
			string << "]]>";
			string << "</proof>" << endLine;
		}
 		string << iterate << indent << tab;
 		string << "</root>" << endLine;
	}
	template<class A>
	void
	Root<A> :: showVolume (String& string, const int indent) const
	{
		const Size_t totalVolume = getVolume();
		string << iterate << indent << tab;
		string << "Tree root volume" << endLine;
		string << iterate << indent << tab;
		string << "------------------" << endLine;
		string << iterate << indent << tab;
		string << memory :: UsageMessage (totalVolume, totalVolume, "total volume") << endLine;
		string << iterate << indent << tab;
		string << memory :: UsageMessage (totalVolume, buffer_.getVolume(), "buffer") << endLine;

		//string << iterate << indent << tab;
		//string << "root vector size = " << rootVector_.getSize() << endLine;
		string << iterate << indent << tab;
		string << memory :: UsageMessage (totalVolume, rootVector_.getVolume(), "root vector") << endLine;

		//string << iterate << indent << tab;
		//string << "step vector size = " << stepVector_.getSize() << endLine;
		string << iterate << indent << tab;
		string << memory :: UsageMessage (totalVolume, stepVector_.getVolume(), "step vector") << endLine;


		//string << iterate << indent << tab;
		//string << "proof vector size = " << proofVector_.getSize() << endLine;
		string << iterate << indent << tab;
		string << memory :: UsageMessage (totalVolume, proofVector_.getVolume(), "proof vector") << endLine;

		string << iterate << indent << tab << endLine;

		showVolumeStatistics (string, indent + 1);
	}
	template<class A>
	void
	Root<A> :: dumpVolume () const
	{
		String string (1024);
		showVolume (string);
		std :: cout << std :: endl;
		std :: cout << string << std :: endl;
	}
	template<class A>
	void
	Root<A> :: dumpInvalidProofs() const
	{
		for (value :: Integer i = 0; i < invalidVector_.getSize(); ++ i) {
			Proof_* invalidProof = invalidVector_.getValue (i);
			Proof_* invalidNode = invalidProof->findInvalidProof();

			Counter :: set();
			invalidNode->dump();
			std :: cout << std :: endl <<  "invalidProof->checkValidity()" << std :: endl;
			invalidProof->checkValidity();
			invalidNode->checkValidity();
			if (invalidProof->isValid()) {
				std :: cout << "invalid is valid - something is wrong" << std :: endl;
			}


			mdl :: proof :: Step* invalidStep = createProof (invalidProof);
			std :: cout << std :: endl << "INVALID PROOF " << i << ":" << std :: endl;
			invalidStep->dump();
			std :: cout << std :: endl;
			invalidStep->commitSuicide();
		}
	}

	template<class A>
	inline void
	Root<A> :: block() {
		isBlocked_ = true;
	}
	template<class A>
	inline void
	Root<A> :: unblock() {
		isBlocked_ = false;
	}

	// object :: Object implementation
	template<class A>
	void
	Root<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Root<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += buffer_.getVolume();
		volume += rootVector_.getVolume();
		volume += proofVector_.getVolume();
		volume += stepVector_.getVolume();

		volume += invalidVector_.getVolume();
		volume += unusedVector_.getVolume();
		return volume;
	}
	template<class A>
	Size_t
	Root<A> :: getSizeOf() const {
		return sizeof (Root);
	}
	template<class A>
	void
	Root<A> :: show (String& string) const
	{
		if (rootVector_.getSize() == 0) {
			//string << "evidences: none." << endLine;
			return;
		}
		string << "proofs:" << endLine;
		for (value :: Integer i = 0; i < rootVector_.getSize(); ++ i) {
			Proof_* proof = rootVector_.getValue (i);
			string << (Proof_*)proof << endLine;
			proof->show (string);
			mdl :: proof :: Question*
				question = const_cast<mdl :: proof :: Question*>(tree_->getQuestion());
			const mdl :: proof :: Step*
				claim = const_cast<const mdl :: proof :: Step*>(createClaim (proof, question));
			string << *claim << endLine;
			deleteObject (claim);
		}
		/*const Mode mode (string);
		if (mode.getValue (Mode :: SHOW_GRAPH_IN_GML)) {
			clearMappedToGraph();
			string << "graph [" << endLine;
			string << tab << "directed 1" << endLine;
			string << tab << "id " << 1 << endLine;
			//string << tab << "label \"size = " << evidences_.getSize();
			//string << "\"" << endLine;
			string << tab << "label \"evidences\"" << endLine;
			const Mode mOld (string);
			Mode mNew (mOld);
			mNew.setValue (Mode :: SHOW_GRAPH_IN_GML, false);
			mNew.setValue (Mode :: SHOW_NODE_IN_GML, true);
			string << mode << mNew;
			show (string);
			string << mode << mOld;
			string << "]" << endLine;
			string << endLine;
		} else if (mode.getValue (Mode :: SHOW_NODE_IN_GML)) {
			for (value :: Integer i = 0; i < root_->getSize(); ++ i) {
				const Evidence*
					evidence = root_->getValue (i);
				evidence->show (string);
			}
			crown_->show (string);
		} else {
			if (mode.getValue (Mode :: SHOW_ROOT_CARD)) {
				if (mode.getValue (Mode :: END_LINE)) {
					string << tab;
				}
				string << "down tree card: " << size_ << " nodes";
				if (mode.getValue (Mode :: END_LINE)) {
					string << endLine;
				} else {
					string << ", ";
				}
			}
			if (mode.getValue (Mode :: SHOW_ROOT_CARD)) {
				if (mode.getValue (Mode :: END_LINE)) {
					string << tab;
				}
				string << "down root card: " << getRootSize() << " nodes";
				if (mode.getValue (Mode :: END_LINE)) {
					string << endLine;
				} else {
					string << ", ";
				}
			}
			if (mode.getValue (Mode :: SHOW_ROOT_VOLUME)) {
				if (mode.getValue (Mode :: END_LINE)) {
					string << tab;
				}
				const Size_t volume = getVolume();
				string << "down tree volume: ";
				memory :: Unit :: show (string, volume);
				if (mode.getValue (Mode :: END_LINE)) {
					string << endLine;
				} else {
					string << ", ";
				}
			}
			crown_->show (string);
		}*/
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	void
	Root<A> :: constructProofs()
	{
		for (value :: Integer i = 0; i < buffer_.getSize(); ++ i) {
			Evidence_* evidence = buffer_.getValue (i);
			Proof_* proof = evidence->constructProof();
			if (rootVector_.contains (proof)) {
				deleteObject (proof);
			} else if (proof->isValid()) {
				rootVector_.add (proof);
				mdl :: proof :: Step* step = createProof (proof);
				stepVector_.add (step);
			} else {
				invalidVector_.add (proof);
			}
		}
		buffer_.clear();
	}

	template<class A>
	inline void
	Root<A> :: showDiffSubset (String& string, const Root* vector) const
	{
		for (value :: Integer i = 0; i < rootVector_.getSize(); ++ i) {
			const Proof_*
				proof = rootVector_.getValue (i);
			if (!vector->contains (proof)) {
				if (proof == NULL) {
					string << "NULL"<< space;
				} else {
					string << *proof << space;
				}
				string << "is absent" << endLine;
			}
		}
	}
	template<class A>
	value :: Integer
	Root<A> :: getLeastProofIndex() const
	{
		value :: Integer leastIndex = 0;
		value :: Integer leastCardinality = value :: undefined :: INTEGER;

		for (value :: Integer i = 0; i < rootVector_.getSize(); ++ i) {
			const Proof_*
				proof = rootVector_.getValue (i);
			if (!proof->isValid()) {
				continue;
			}
			const value :: Integer
				cardinality = proof->getCardinality();

			if (cardinality < leastCardinality) {
				leastCardinality = cardinality;
				leastIndex = i;
			}
		}
		return leastIndex;
	}

	template<class A>
	mdl :: proof :: Step*
	Root<A> :: createStep (Proof_* proof, mdl :: proof :: Question* question) const
	{
		proof->resetCompilation();
		return proof->compileStep (question);
	}
	template<class A>
	mdl :: proof :: Step*
	Root<A> :: createClaim (Proof_* proof, mdl :: proof :: Question* step) const
	{
		proof->resetCompilation();
		form :: proof :: step :: Question*
			question = dynamic_cast<form :: proof :: step :: Question*>(step);
		mdl :: proof :: Claim*
			claim = new form :: proof :: step :: Claim
			(
				question,
				proof->getCardinality()
			);
		proof->compileClaim (claim);
		return claim;
	}

	template<class A>
	mdl :: proof :: Step*
	Root<A> :: createProof (Proof_* proof) const
	{
		switch (proof->getCardinality()) {
		case 0  : return NULL;
		case 1  : return createStep (proof);
		default : return createClaim (proof);
		}
	}
	template<class A>
	mdl :: proof :: Step*
	Root<A> :: createClaim (Proof_* proof) const
	{
		mdl :: proof :: Question*
			questionStep = tree_->getQuestion();
		form :: proof :: step :: Question*
			question = dynamic_cast<form :: proof :: step :: Question*>(questionStep);
		mdl :: proof :: Step* const
			claim = createClaim (proof, question);

		//std :: cout << *claim << std :: endl;

		//proof->verifyIntegrity();
		//claim->check();
		return claim;
	}
	template<class A>
	mdl :: proof :: Step*
	Root<A> :: createStep (Proof_* proof) const
	{
		mdl :: proof :: Question*
			questionStep = tree_->getQuestion();
		form :: proof :: step :: Question*
			question = dynamic_cast<form :: proof :: step :: Question*>(questionStep);
		return createStep (proof, question);
		//proof->verifyIntegrity();
		//step->check();
	}
	template<class A>
	bool
	Root<A> :: verifyProof (mdl :: proof :: Step* step, const bool showError) const
	{
		bool success = true;
		try {
			step->check();
		} catch (Error* error) {
			success = false;
			if (showError) {
				std :: cout << *error << std :: endl;
			}
			delete error;
		}
		return success;
	}
	template<class A>
	bool
	Root<A> :: verifyDuplicateProofs()
	{
		if (rootVector_.isEmpty()) {
			return true;
		}
		bool result = true;
		for (value :: Integer i = 0; i < rootVector_.getSize() - 1; ++ i) {
			Proof_* proof_1 = rootVector_.getValue (i);
			for (value :: Integer j = i + 1; j < rootVector_.getSize(); ++ j) {
				Proof_* proof_2 = rootVector_.getValue (j);
				if (proof_1->isIdentical (proof_2)) {
					mdl :: proof :: Step*
						claim_1 = createProof (proof_1);
					mdl :: proof :: Step*
						claim_2 = createProof (proof_2);
					std :: cout << std :: endl;
					std :: cout << "Duplcate proofs:" << std :: endl;
					std :: cout << *claim_1 << std :: endl;
					std :: cout << *claim_2 << std :: endl;
					std :: cout << std :: endl;
					const_cast<mdl :: proof :: Step*>(claim_1)->commitSuicide();
					const_cast<mdl :: proof :: Step*>(claim_2)->commitSuicide();
					result = false;
				}
			}
		}
		return result;
	}
	template<class A>
	bool
	Root<A> :: verifyDuplicateEvidences() const
	{
		if (buffer_.isEmpty()) {
			return true;
		}
		bool result = true;
		for (value :: Integer i = 0; i < buffer_.getSize() - 1; ++ i) {
			const Evidence_*
				evidence_1 = buffer_.getValue (i);
			for (value :: Integer j = i + 1; j < buffer_.getSize(); ++ j) {
				const Evidence_*
					evidence_2 = rootVector_.getValue (j);
				if (evidence_1->givesTheSameProof (evidence_2)) {
					/*const mdl :: proof :: Step*
						claim_1 = createProof (proof_1);
					const mdl :: proof :: Step*
						claim_2 = createProof (proof_2);*/
					std :: cout << std :: endl;
					std :: cout << "Duplcate proofs:" << std :: endl;
					/*std :: cout << *claim_1 << std :: endl;
					std :: cout << *claim_2 << std :: endl;
					std :: cout << std :: endl;
					const_cast<mdl :: proof :: Step*>(claim_1)->commitSuicide();
					const_cast<mdl :: proof :: Step*>(claim_2)->commitSuicide();*/
					result = false;
				}
			}
		}
		return result;
	}
	template<class A>
	Size_t
	Root<A> :: getProofsVolume() const
	{
		Size_t volume = 0;
		for (value :: Integer i = 0; i < rootVector_.getSize(); ++ i) {
			const Proof_*
				proof = rootVector_.getValue (i);
			volume += getAggregateVolume (proof);
		}
		return volume;
	}

	template<class A>
	void
	Root<A> :: showVolumeStatistics (String& string, const int indent) const
	{
		string << iterate << indent << tab;
		string << "Tree root statistics" << endLine;
		string << iterate << indent << tab;
		string << "--------------------" << endLine;

		int hypCount  = 0;
		int propCount = 0;
		int refCount  = 0;
		int topCount  = 0;
		Size_t hypVolume  = 0;
		Size_t propVolume = 0;
		Size_t refVolume  = 0;
		Size_t topVolume  = 0;

		for (int i = 0; i < proofVector_.getSize(); ++ i) {
			const Proof_* proof = proofVector_.getValue (i);
			if (dynamic_cast<const Hyp_*>(proof) != NULL)  {
				++ hypCount;
				hypVolume += getAggregateVolume (proof);
			}
			if (dynamic_cast<const Prop_*>(proof) != NULL) {
				++ propCount;
				propVolume += getAggregateVolume (proof);
			}
			if (dynamic_cast<const Ref_*>(proof) != NULL)  {
				++ refCount;
				refVolume += getAggregateVolume (proof);
			}
			if (dynamic_cast<const Top_*>(proof) != NULL)  {
				++ topCount;
				topVolume += getAggregateVolume (proof);
			}
		}

		string << iterate << indent << tab;
		string << "hyp count = " << hypCount << ", " << tab;
		string << "total volume = " << hypVolume << ", " << tab;
		string << "average volume = " << ((hypCount > 0) ? (hypVolume / hypCount) : 0);
		string << endLine;

		string << iterate << indent << tab;
		string << "prop count = " << propCount << ", " << tab;
		string << "total volume = " << propVolume << ", " << tab;
		string << "average volume = " << ((propCount > 0) ? (propVolume / propCount) : 0);
		string << endLine;

		string << iterate << indent << tab;
		string << "ref count = " << refCount << ", " << tab;
		string << "total volume = " << refVolume << ", " << tab;
		string << "average volume = " << ((refVolume > 0) ? (refVolume / refCount) : 0);
		string << endLine;

		string << iterate << indent << tab;
		string << "top count = " << topCount << ", " << tab;
		string << "total volume = " << topVolume << ", " << tab;
		string << "average volume = " << ((topVolume > 0) ? (topVolume / topCount) : 0);
		string << endLine;

		string << iterate << indent << tab << endLine;

		/*for (int i = 0; i < proofVector_.getSize(); ++ i) {
			const Proof_* proof = proofVector_.getValue (i);
			if (dynamic_cast<const Prop_*>(proof) != NULL) {
				const Prop_* prop = dynamic_cast<const Prop_*>(proof);
				std :: cout << *prop << std :: endl;
			}
		}
		string << iterate << indent << tab << endLine;*/
	}
}
}
}

#endif /*MDL_PROVER_ROOT_ROOT_CPP_*/
