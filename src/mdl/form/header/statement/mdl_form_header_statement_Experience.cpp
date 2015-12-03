/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_statement_Experience.hpp                 */
/* Description:     proposition usage experience                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_HEADER_STATEMENT_EXPERIENCE_CPP_
#define MDL_FORM_HEADER_STATEMENT_EXPERIENCE_CPP_

namespace mdl {
namespace form {
namespace header {
namespace statement {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Experience :: Experience (const mdl :: Proposition* proposition) :
	proposition_ (proposition),
	positiveSteps_ (INITIAL_STEP_VECTOR_CAPACITY),
	negativeSteps_ (INITIAL_STEP_VECTOR_CAPACITY) {
	}
	Experience :: ~ Experience() {
	}

	// prover :: Experience implementation
	index :: Step
	Experience :: getSize() const {
		return positiveSteps_.getSize() + negativeSteps_.getSize();
	}
	void
	Experience :: addPositive (mdl :: proof :: Step* step) {
		positiveSteps_.add (step);
	}
	void
	Experience :: addNegative (mdl :: proof :: Step* step)
	{
		if (positiveSteps_.getSize() <= negativeSteps_.getSize()) {
			return;
		}
		negativeSteps_.add (step);
	}
	mdl :: vector :: proof :: Step&
	Experience :: positiveSteps() {
		return positiveSteps_;
	}
	mdl :: vector :: proof :: Step&
	Experience :: negativeSteps() {
		return negativeSteps_;
	}
	const mdl :: vector :: proof :: Step&
	Experience :: positiveSteps() const {
		return positiveSteps_;
	}
	const mdl :: vector :: proof :: Step&
	Experience :: negativeSteps() const {
		return negativeSteps_;
	}

using manipulator :: endLine;

	// object :: Object implementation
	void
	Experience :: commitSuicide() {
		delete this;
	}
	Size_t
	Experience :: getVolume() const
	{
		Size_t volume = 0;
		volume += positiveSteps_.getVolume();
		volume += negativeSteps_.getVolume();
		return volume;
	}
	Size_t
	Experience :: getSizeOf() const {
		return sizeof (Experience);
	}
	void
	Experience :: show (String& string) const
	{
		string << "experience of ";
		proposition_->getAssertion()->replicateName (string);
		string << "assertion";
		const index :: Arity
			index = proposition_->getIndex();
		if (index == 0) {
			string << ": ";
		} else {
			string << "proposition " << index << ": ";
		}
		string << "+ " << positiveSteps_.getSize() << " / ";
		string << "- " << negativeSteps_.getSize();
	}

	/****************************
	 *		Private members
	 ****************************/
}
}
}
}

#endif /*MDL_FORM_HEADER_STATEMENT_EXPERIENCE_CPP_*/
