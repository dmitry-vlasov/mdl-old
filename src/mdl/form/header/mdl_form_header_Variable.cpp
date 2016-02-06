/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_Variable.cpp                             */
/* Description:     variable declaration                                     */
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

	/****************************
	 *		Public members
	 ****************************/

	Variable :: Variable
	(
		const Location& location,
		value :: Literal literal,
		mdl :: Identificator* identificator,
		mdl :: Theory* theory
	) :
	location_ (location),
	index_ (index :: undefined :: ARITY),
	symbol_ (literal),
	identificator_ (identificator)
	{
		if (Config :: localParsing()) {
			return;
		}
		if (Config :: shallowParsing() && !location_.isTop()) {
			return;
		}
		symbol_.setReplaceable();
		const index :: Type
			typeIndex = theory->getIndex (identificator_);
		symbol_.setType (Math :: types()->get (typeIndex));
		if (getType() == NULL) {
			Error* error = new Error (location_, Error :: SEMANTIC);
			error->message() << "type " << *identificator_ << " is not declared." << endLine;
			throw error;
		}
	}
	Variable :: Variable
	(
		const Location& location,
		const Symbol& symbol,
		mdl :: Theory* theory
	) :
	location_ (location),
	index_ (index :: undefined :: ARITY),
	symbol_ (symbol),
	identificator_ (new Identificator (symbol.getType()->getIdentificator()))
	{
		if (Config :: localParsing()) {
			return;
		}
		if (Config :: shallowParsing() && !location_.isTop()) {
			return;
		}
		symbol_.setReplaceable();
		const index :: Type
			typeIndex = theory->getIndex (identificator_);
		symbol_.setType (Math :: types()->get (typeIndex));
		if (getType() == NULL) {
			Error* error = new Error (location_, Error :: SEMANTIC);
			error->message() << "type " << *identificator_ << " is not declared." << endLine;
			throw error;
		}
	}
	Variable :: Variable (const Symbol& symbol) :
	location_ (),
	index_ (index :: undefined :: ARITY),
	symbol_ (symbol),
	identificator_ (new Identificator (symbol.getType()->getIdentificator())) {
	}
	Variable :: ~ Variable() {
		deleteAggregateObject (identificator_);
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;
using manipulator :: underline;

	// mdl :: header :: Variable implementation

	value :: Literal
	Variable :: getLiteral() const {
		return symbol_.getLiteral();
	}
	void
	Variable :: setIndex (const index :: Arity index) {
		index_ = index;
	}
	void
	Variable :: setType (mdl :: Type* type) {
		symbol_.setType (type);
	}
	void
	Variable :: translateReference (String& string) const {
		string << smm :: Token :: prefix_f_ << index_;
	}
	Symbol&
	Variable :: getSymbol() {
		return symbol_;
	}
	mdl :: Type*
	Variable :: getType () {
		return const_cast<mdl :: Type*>(symbol_.getType());
	}
	const Symbol&
	Variable :: getSymbol() const {
		return symbol_;
	}
	const mdl :: Type*
	Variable :: getType () const {
		return symbol_.getType();
	}

using manipulator :: underline;

	// object :: Writable implementation
	void
	Variable :: translate (String& string) const
	{
		translateReference (string);
		string << space;
		string << :: smm :: Token :: floating_ << space;
		getType()->translateName (string);
		string << space;
		string << Table :: literals()->get (getLiteral()) << space;
		string << :: smm :: Token :: end_ << endLine;
	}
	void
	Variable :: replicate (String& string) const
	{
		string << Token :: variable_ << space;
		string << Table :: literals()->get (getLiteral()) << space;
		string << Token :: colon_ << space;
		if (identificator_ != NULL) {
			identificator_->replicate (string);
		} else {
			string << "<undefined>";
		}
	}
	bool
	Variable :: lookup() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return true;
		}
		if (identificator_->lookup()) {
			if (Config :: lookupDefinition()) {
				std :: cout << *symbol_.getType();
			} else {
				std :: cout << symbol_.getType()->getLocation();
			}
			return true;
		} else {
			return false;
		}
	}
	object :: Writable*
	Variable :: find()
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		}
		if (identificator_->lookup()) {
			return const_cast<mdl :: Type*>(symbol_.getType());
		} else {
			return NULL;
		}
	}
	const object :: Writable*
	Variable :: find() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		}
		if (identificator_->lookup()) {
			return symbol_.getType();
		} else {
			return NULL;
		}
	}

	// object :: Object implementation
	void
	Variable :: commitSuicide() {
		delete this;
	}
	Size_t
	Variable :: getVolume() const {
		return getAggregateVolume (identificator_);
	}
	Size_t
	Variable :: getSizeOf() const {
		return sizeof (Variable);
	}
}
}
}


