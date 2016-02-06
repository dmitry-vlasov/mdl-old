/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_evidence_Vector.cpp                           */
/* Description:     evidences: vector of evidences                           */
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
namespace evidence {

	/****************************
	 *		Public members
	 ****************************/

	template<class A, bool D>
	Vector<A, D> :: Vector (Node_* node) :
	Evidences<Allocator_> (),
	node_ (node),
	evidenceVector_ (INITIAL_EVIDENCE_VECTOR_CAPACITY) {
	}
	template<class A, bool D>
	Vector<A, D> :: ~ Vector() {
	}

using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: space;

	template<class A, bool D>
	bool
	Vector<A, D> :: isEqual (const Vector* vector) const
	{
		const bool a = this->isSubset (vector);
		const bool b = vector->isSubset (this);
		const bool c = vector->getSize() == getSize();
		return a && b && c;
	}
	template<class A, bool D>
	void
	Vector<A, D> :: showDifference (String& string, const Vector* vector) const
	{
		string << "direction A, size = " << getSize() << ":" << endLine;
		showDiffSubset (string, vector);
		string << endLine;
		string << "direction B, size = " << vector->getSize() << ":" << endLine;
		vector->showDiffSubset (string, this);
		string << endLine;
	}

	template<class A, bool D>
	void
	Vector<A, D> :: showSubstitutions (String& string, const bool showUp) const
	{
		string << "evidences: " << endLine;
		if (evidenceVector_.getSize() == 0) {
			string << tab << "none." << endLine;
			return;
		}
		for (value :: Integer i = 0; i < evidenceVector_.getSize(); ++ i) {
			const Evidence_* const
				evidence = evidenceVector_.getValue (i);
			string << tab << evidence << tab;
			string << "depth = " << evidence->getDepth() << ";" << tab;
			const Prop_* const
				prop = dynamic_cast<const Prop_*>(evidence);
			if (showUp && (prop != NULL)) {
				string << "up: ";
				for (index :: Arity i = 0; i < prop->getArity(); ++ i) {
					const Evidence_* const
						upEvidence = prop->getUp (i);
					string << upEvidence << space;
				}
			}
			const Sub_* const
				sub = dynamic_cast<const Sub_*>(evidence);
			if (showUp && (sub != NULL)) {
				string << "up: ";
				for (value :: Integer i = 0; i < sub->getSize(); ++ i) {
					const Evidence_* const
						upEvidence = sub->getUp (i);
					const Prop_* const
						prop = dynamic_cast<const Prop_*>(upEvidence);
					if (i != 0) {
						string << ";" << space;
					}
					for (index :: Arity j = 0; j < prop->getArity(); ++ j) {
						const Evidence_* const
							up = prop->getUp (j);
						string << up << space;
					}
				}
			}
			const Substitution_* const
				substitution = evidence->getSubstitution();
			if (substitution == NULL) {
				string << "NULL";
			} else {
				string << *substitution;
			}
			string << endLine;
			if (i == evidenceVector_.getSize() - 1) {
				string << endLine;
			}
		}
	}

	// prover :: Evidences implementation
	template<class A, bool D>
	void
	Vector<A, D> :: checkForDuplicateProofs()
	{
		return;
		if (evidenceVector_.isEmpty()) {
			return;
		}
		for (value :: Integer i = 0; i < evidenceVector_.getSize() - 1; ++ i) {
			const Evidence_* const
				evidence_1 = evidenceVector_.getValue (i);
			for (value :: Integer j = i + 1; j < evidenceVector_.getSize(); ++ j) {
				const Evidence_* const
					evidence_2 = evidenceVector_.getValue (j);
				if (evidence_1->givesSameProof (evidence_2)) {
					//std :: cout << "duplicate evidence" << std :: endl;
					//node_->getTree()->show();
				}
			}
		}
	}
	template<class A, bool D>
	void
	Vector<A, D> :: add (const stack :: Substitution* sub, Evidence_* up)
	{
		if (duplicate_) {
			addWithDuplicate (sub, up);
		} else {
			addWithoutDuplicate (sub, up);
		}
	}
	template<class A, bool D>
	void
	Vector<A, D> :: verifyIntegrity() const
	{
		for (value :: Integer i = 0; i < evidenceVector_.getSize(); ++ i) {
			evidenceVector_.getValue (i)->verifyIntegrity();
		}
	}
	template<class A, bool D>
	value :: Integer
	Vector<A, D> :: getSize() const {
		return evidenceVector_.getSize();
	}
	template<class A, bool D>
	void
	Vector<A, D> :: add (Evidence_* evidence) {
		evidenceVector_.add (evidence);
	}
	template<class A, bool D>
	typename Vector<A, D> :: Evidence_*
	Vector<A, D> :: getValue (const value :: Integer index) {
		return evidenceVector_.getValue (index);
	}
	template<class A, bool D>
	typename Vector<A, D> :: Node_*
	Vector<A, D> :: getNode() {
		return node_;
	}
	template<class A, bool D>
	const typename Vector<A, D> :: Evidence_*
	Vector<A, D> :: getValue (const value :: Integer index) const {
		return evidenceVector_.getValue (index);
	}

	template<class A, bool D>
	void
	Vector<A, D> :: show (String& string, const int indent) const
	{
		string << iterate << indent << tab;
		string << "evidences ";
		if (evidenceVector_.getSize() == 0) {
			string << " { }";
		} else {
			string << "size = " << evidenceVector_.getSize() << " {" << endLine;
			for (value :: Integer i = 0; i < evidenceVector_.getSize(); ++ i) {
				const Evidence_*
					evidence = evidenceVector_.getValue (i);
				string << iterate << (indent + 1) << tab;
				evidence->show (string);
				if (i + 1 < evidenceVector_.getSize()) {
					", ";
				}
				string << endLine;
			}
			string << iterate << indent << tab;
			string << "}";
		}
	}

	// object :: Object interface
	template<class A, bool D>
	void
	Vector<A, D> :: commitSuicide() {
		delete this;
	}
	template<class A, bool D>
	Size_t
	Vector<A, D> :: getVolume() const
	{
		Size_t volume = 0;
		volume += evidenceVector_.getVolume();
		return volume;
	}
	template<class A, bool D>
	Size_t
	Vector<A, D> :: getSizeOf() const {
		return sizeof (Vector);
	}
	template<class A, bool D>
	void
	Vector<A, D> :: show (String& string) const
	{
		if (evidenceVector_.getSize() == 0) {
			//string << "evidences: none." << endLine;
			return;
		}
		string << "evidences ";
		string << "(size = " << evidenceVector_.getSize() << ", ";
		string << endLine;
		for (value :: Integer i = 0; i < evidenceVector_.getSize(); ++ i) {
			const Evidence_*
				evidence = evidenceVector_.getValue (i);
			string << tab << "evidence " << i << ":" << endLine;
			evidence->show (string);
		}
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A, bool D>
	bool
	Vector<A, D> :: containsSameProof (const Evidence_* evidence_1) const
	{
		for (value :: Integer i = 0; i < evidenceVector_.getSize(); ++ i) {
			const Evidence_* const
				evidence_2 = evidenceVector_.getValue (i);
			if (evidence_2->givesSameProof (evidence_1)) {
				return true;
			}
		}
		return false;
	}
	template<class A, bool D>
	bool
	Vector<A, D> :: containsSubstitution (const Evidence_* evidence_1) const
	{
		for (value :: Integer i = 0; i < evidenceVector_.getSize(); ++ i) {
			const Evidence_* const
				evidence_2 = evidenceVector_.getValue (i);
			if (evidence_1->hasSameSubstitution (evidence_2)) {
				return true;
			}
		}
		return false;
	}
	template<class A, bool D>
	inline void
	Vector<A, D> :: showDiffSubset (String& string, const Vector* vector) const
	{
		for (value :: Integer i = 0; i < evidenceVector_.getSize(); ++ i) {
			const Evidence_* const
				evidence = evidenceVector_.getValue (i);
			if (!vector->containsSubstitution (evidence)) {
				const Substitution_* const
					substitution = evidence->getSubstitution();
				string << tab << evidence << tab;
				if (substitution == NULL) {
					string << "NULL"<< space;
				} else {
					string << *substitution << space;
				}
				string << "is absent" << endLine;
			}
		}
	}
	template<class A, bool D>
	bool
	Vector<A, D> :: isSubset (const Vector* vector) const
	{
		for (value :: Integer i = 0; i < evidenceVector_.getSize(); ++ i) {
			const Evidence_* const
				evidence = evidenceVector_.getValue (i);
			if (!vector->containsSubstitution (evidence)) {
				return false;
			}
		}
		return true;
	}

	template<class A, bool D>
	void
	Vector<A, D> :: addWithoutDuplicate (const stack :: Substitution* sub, Evidence_* up)
	{
		Evidence_* result = NULL;
		Substitution_* substitution = Substitution_ :: create (sub);
		Sub_* newOne = new Sub_ (node_, up, substitution, false);

		if (Config :: growUpMode() == Config :: GROW_UP_DETERMINED &&
			Config :: growUpLimit() == 1) {
			if (evidenceVector_.getSize() > 0) {
				std :: cout << "fuck off and die: " << evidenceVector_.getSize() << std :: endl;
				//String str;
				//this->showInfo (str);
				//std :: cout << str << std :: endl;
			}
		}

		for (value :: Integer i = 0; i < evidenceVector_.getSize(); ++ i) {
			Evidence_* evidence = evidenceVector_.getValue (i);
			if (evidence->givesSameProof (newOne)) {
				node_->getTree()->down().remove (newOne);
				newOne->commitSuicide();
				return;
			}
		}
		newOne->confirm();
		evidenceVector_.add (newOne);
	}
	template<class A, bool D>
	void
	Vector<A, D> :: addWithDuplicate (const stack :: Substitution* sub, Evidence_* up)
	{
		Evidence_* result = NULL;
		Substitution_* substitution = Substitution_ :: create (sub);
		result = new Sub_ (node_, up, substitution);

		if (Config :: growUpMode() == Config :: GROW_UP_DETERMINED &&
			Config :: growUpLimit() == 1) {
			if (evidenceVector_.getSize() > 0) {
				std :: cout << "fuck off and die: " << evidenceVector_.getSize() << std :: endl;
				//String str;
				//this->showInfo (str);
				//std :: cout << str << std :: endl;
			}
		}

#if 0
		for (value :: Integer i = 0; i < evidenceVector_.getSize(); ++ i) {
			Evidence_* evidence = evidenceVector_.getValue (i);
			if (evidence->givesSameProof (result)) {

				//if (Counter :: stop()) {
					String str;
					node_->getTree()->root().block();
					Proof_* proof_1 = const_cast<Evidence_*>(evidence)->constructProof();
					proof_1->showAsTerm (str);
					std :: cout << std :: endl << "proof_1 = ";
					std :: cout << str << std :: endl;

					str.clear();
					Proof_* proof_2 = result->constructProof();
					proof_2->showAsTerm (str);
					std :: cout << std :: endl << "proof_2 = ";
					std :: cout << str << std :: endl;
					node_->getTree()->root().unblock();
				//}
			}
		}
#endif

		evidenceVector_.add (result);
	}
}
}
}



