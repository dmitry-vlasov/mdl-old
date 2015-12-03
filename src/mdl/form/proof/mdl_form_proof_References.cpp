/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_References.cpp                            */
/* Description:     vector of references to the proof nodes                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_PROOF_REFERENCES_CPP_
#define MDL_FORM_PROOF_REFERENCES_CPP_

namespace mdl {
namespace form {
namespace proof {

	/****************************
	 *		Public members
	 ****************************/

	inline
	References :: References (const index :: Arity capacity) :
	referenceVector_ (capacity) {
	}
	inline
	References :: References
	(
		const vector :: parser :: Reference& referenceVector,
		mdl :: Theory*
	) :
	referenceVector_ (referenceVector) {
	}
	References :: ~ References() {
	}

	// proof :: References implementation
	void
	References :: build (mdl :: proof :: Scope* scope)
	{
		for (index :: Arity i = 0; i < getArity(); ++ i) {
			mdl :: proof :: Reference*
				reference = referenceVector_.getValue (i);
			reference->build (scope);
		}
	}
	void
	References :: add (mdl :: proof :: Reference* ref)
	{
		mdl :: proof :: Reference* newReference = ref;
		for (index :: Arity i = 0; i < getArity(); ++ i) {
			mdl :: proof :: Reference*
				oldReference = referenceVector_.getValue (i);
			if (oldReference == newReference) {
				form :: proof :: Reference*
					reference = dynamic_cast<form :: proof :: Reference*>(newReference);
				newReference = new form :: proof :: Reference (*reference);
				break;
			}
		}
		referenceVector_.add (newReference);
	}
	index :: Arity
	References :: find (const mdl :: proof :: Node* node) const
	{
		for (index :: Arity i = 0; i < getArity(); ++ i) {
			const mdl :: proof :: Reference* const
				reference = referenceVector_.getValue (i);
			if (reference->getNode() == node) {
				return i;
			}
		}
		return index :: undefined :: ARITY;
	}
	index :: Arity
	References :: getArity() const {
		return referenceVector_.getSize();
	}
	mdl :: proof :: Reference*
	References :: get (const index :: Arity index) {
		return referenceVector_.getValue (index);
	}
	const mdl :: proof :: Reference*
	References :: get (const index :: Arity index) const {
		return referenceVector_.getValue (index);
	}

using manipulator :: space;

	// object :: Writable implementation
	void
	References :: translate (String& string) const
	{
		for (index :: Arity i = 0; i < getArity(); ++ i) {
			const mdl :: proof :: Reference* const
				reference = referenceVector_.getValue (i);
			reference->translate (string);
		}
	}
	void
	References :: replicate (String& string) const
	{
		string << Token :: openBracket_;
		const index :: Arity
			arity = referenceVector_.getSize();
		for (index :: Arity i = 0; i < arity; ++ i) {
			const mdl :: proof :: Reference* const
				reference = referenceVector_.getValue (i);
			reference->replicate (string);
			if (i < arity - 1) {
				string << Token :: comma_ << space;
			}
		}
		string << Token :: closeBracket_;
	}
	bool
	References :: lookup() const
	{
		for (index :: Arity i = 0; i < getArity(); ++ i) {
			const mdl :: proof :: Reference* const
				reference = referenceVector_.getValue (i);
			if (reference->lookup()) {
				return true;
			}
		}
		return false;
	}

	// object :: Object implementation
	void
	References :: commitSuicide() {
		delete this;
	}
	Size_t
	References :: getVolume() const {
		return referenceVector_.getVolume();
	}
	Size_t
	References :: getSizeOf() const {
		return sizeof (References);
	}
}
}
}

#endif /*MDL_FORM_PROOF_REFERENCES_CPP_*/
