/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_block_Axiom.cpp                                 */
/* Description:     axiom class                                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_BLOCK_AXIOM_CPP_
#define MDL_FORM_BLOCK_AXIOM_CPP_

namespace mdl {
namespace form {
namespace block {

	/****************************
	 *		Public members
	 ****************************/

	Axiom :: Axiom
	(
		const Location& location,
		const mdl :: Comments* comments,
		lexer :: Indent barIndent,
		value :: Name name,
		mdl :: Variables* variables,
		mdl :: Disjointeds* disjointeds,
		const vector :: parser :: Hypothesis& hypothesisVector,
		const vector :: parser :: Axiomatic& propositionVector,
		mdl :: Theory* theory
	) :
	Ancestor_
	(
		location,
		comments,
		barIndent,
		name,
		variables,
		disjointeds,
		hypothesisVector,
		propositionVector,
		theory
	) {
		Ancestor_ :: add (this);
	}
	Axiom :: ~ Axiom() {
	}

	// mdl :: Assertion implementation
	mdl :: Assertion :: Kind
	Axiom :: getKind() const {
		return mdl :: Assertion :: AXIOM;
	}

	// object :: Verifiable implementation
	/*void
	Axiom :: check() {
	}
	void
	Axiom :: compress() {
	}
	void
	Axiom :: reprove() {
	}
	void
	Axiom :: prove() {
	}
	bool
	Axiom :: isVerified() const {
		return true;
	}*/

	// object :: Buildable implementation
	/*void
	Axiom :: build() {
		Ancestor_ :: build();
	}*/

using manipulator :: space;
using manipulator :: endLine;

	// object :: Writable implementation
	void
	Axiom :: replicate (String& string) const
	{
		if (!Config :: removeComments() && (comments_ != NULL)) {
			string << location_.getIndent();
			comments_->replicate (string);
			string << endLine;
		}
		string << location_.getIndent() << Token :: axiom_ << space;
		Ancestor_ :: replicate (string);
		string << endLine;
	}

	// object :: Object implementation
	void
	Axiom :: commitSuicide() {
		delete this;
	}
}
}
}

#endif /*MDL_FORM_BLOCK_AXIOM_CPP_*/
