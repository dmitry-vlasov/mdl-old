/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_statement_Provable.cpp                   */
/* Description:     provable statement class                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace form {
namespace header {
namespace statement {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Provable :: Provable
	(
		const Location& location,
		index :: Arity index,
		mdl :: Identificator* identificator,
		array :: Expression* expression,
		mdl :: Theory* theory
	) :
	header :: statement :: Proposition
	(
		location,
		index,
		identificator,
		expression,
		theory
	) {
	}
	Provable :: ~ Provable() {
	}

	// statement :: Provable implementation
	mdl :: proof :: Provable*
	Provable :: getProof() {
		return dynamic_cast<mdl :: proof :: Provable*>(Proposition :: proofNode_);
	}
	const mdl :: proof :: Provable*
	Provable :: getProof() const {
		return dynamic_cast<const mdl :: proof :: Provable*>(Proposition :: proofNode_);
	}

	// object :: Buildable implementation
	void
	Provable :: build()
	{
		Statement :: build();
		Statement :: proofNode_ =
			new form :: proof :: node :: Provable
			(
				Statement :: assertion_,
				Statement :: index_,
				Statement :: expression_
			);
		Math :: propositions()->addToTree (this);
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Provable :: translate (String& string) const
	{
		string << tab;
		assertion_->translateName (string, Statement :: index_);
		string << space;
		string << :: smm :: Token :: provable_ << space;
		Proposition :: translate (string);
		string << :: smm :: Token :: equality_<< endLine;
		string << tab;
		proofNode_->translate (string);
		string << :: smm :: Token :: end_<< endLine;
	}
	void
	Provable :: replicate (String& string) const {
		Proposition :: replicate (string);
	}

	// object :: Object implementation
	void
	Provable :: commitSuicide() {
		delete this;
	}
	Size_t
	Provable :: getVolume() const {
		return Proposition :: getVolume();
	}
	Size_t
	Provable :: getSizeOf() const {
		return sizeof (Provable);
	}
}
}
}
}


