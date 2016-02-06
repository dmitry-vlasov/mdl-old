/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_block_Super.hpp                                 */
/* Description:     type-supertype relation class                            */
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
namespace block {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Super :: Super
	(
		mdl :: Type* inferType,
		mdl :: Identificator* identificator,
		mdl :: Theory* theory
	) :
	header :: Line :: Counter(),
	theory_ (theory),
	identificator_ (identificator),
	inferType_ (inferType),
	superType_ (NULL) {
	}
	inline
	Super :: Super
	(
		mdl :: Type* inferType,
		mdl :: Type* superType,
		mdl :: Theory* theory
	) :
	header :: Line :: Counter(),
	theory_ (theory),
	identificator_ (NULL),
	inferType_ (inferType),
	superType_ (superType) {
	}
	Super :: ~ Super() {
	}


using nstd :: manipulator :: underline;

	// mdl :: Super implementation
	void
	Super :: translateReference (String& string) const
	{
		string << :: smm :: Token :: prefix_a_;
		if (Config :: noLabels()) {
			string << Counter :: getIndex();
		} else {
			// refernce template:
			// ([header]_)<super_type>_([delimiter]_)<infer_type>

			if (header_[0] != chars :: NULL_CHAR) {
				string << header_ << underline;
			}
			superType_->translateName (string);
			string << underline;
			if (delimiter_[0] != chars :: NULL_CHAR) {
				string << delimiter_ << underline;
			}
			inferType_->translateName (string);
		}
	}
	void
	Super :: addSuperSuper (vector :: Super& supers)
	{
		for (index :: Type i = 0; i < superType_->getSuperCount(); ++ i) {
			mdl :: Type*
				superSuperType = superType_->getSuper(i)->getType();
			mdl :: Super*
				superSuper = new Super (inferType_,superSuperType, NULL);
			supers.add (superSuper);
		}
	}
	mdl :: Type*
	Super :: getType() {
		return superType_;
	}
	const mdl :: Type*
	Super :: getType() const {
		return superType_;
	}

using nstd :: manipulator :: space;
using nstd :: manipulator :: tab;
using nstd :: manipulator :: endLine;

	// object :: Buildable implementation
	void
	Super :: build()
	{
		if (superType_ == NULL) {
			const index :: Type
				index = theory_->checkUsed (identificator_);
			superType_ = Math :: types()->get (index);
		}
		if (superType_ == NULL) {
			Error* error = new Error (Error :: SEMANTIC);
			error->message() << "super type ";
			identificator_->replicate (error->message());
			error->message() << "is not declared." << endLine;
			throw error;
		}
		superType_->addSubtype (inferType_);
	}

	// object :: Writable implementation
	void
	Super :: translate (String& string) const
	{
		// ${
		string << :: smm :: Token :: blockBegin_ << endLine;

		// $v x $.
		string << tab << :: smm :: Token :: variable_ << space;
		string << variable_ << space;
		string << :: smm :: Token :: end_ << endLine;

		// f0 $f type x $.
		string << tab << :: smm :: Token :: prefix_f_ << '0';
		string << space << :: smm :: Token :: floating_ << space;
		inferType_->translateName (string);
		string << space << variable_ << space;
		string << :: smm :: Token :: end_ << endLine;

		// <label> $a super_type x $.
		string << tab;
		translateReference (string);

		string << space << :: smm :: Token :: axiomatic_ << space;
		superType_->translateName (string);
		string << space << variable_ << space;
		string << :: smm :: Token :: end_ << endLine;

		// $}
		string << :: smm :: Token :: blockEnd_ << endLine;
	}
	void
	Super :: replicate (String&) const {
	}
	bool
	Super :: lookup() const {
		return false;
	}
	object :: Writable*
	Super :: find() {
		return NULL;
	}
	const object :: Writable*
	Super :: find() const {
		return NULL;
	}

	// object :: Object implementation
	void
	Super :: commitSuicide() {
		delete this;
	}
	Size_t
	Super :: getVolume() const {
		return 0;
	}
	Size_t
	Super :: getSizeOf() const {
		return sizeof (Super);
	}

	/*********************************
	 *		Private static attributes
	 *********************************/

	const char Super :: variable_[]  = "x"; //"RULE";
	const char Super :: header_[]    = "";  //"RULE";
	const char Super :: delimiter_[] = "";  //"IS_SUPER";
}
}
}


