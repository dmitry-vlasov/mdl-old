/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_notation_Notation.cpp                     */
/* Description:     notation class                                           */
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
namespace proof {
namespace notation {

	/****************************
	 *		Public members
	 ****************************/

	Notation :: Notation
	(
		mdl :: proof :: Line* prev,
		const Location& location,
		value :: Literal literal,
		mdl :: Variables* variables,
		mdl :: proof :: Term* abbreviation,
		mdl :: proof :: Term* meaning,
		mdl :: Theory* theory
	) :
	location_ (location),
	literal_ (literal),
	variables_ (variables),
	abbreviation_ (abbreviation),
	meaning_ (meaning),
	next_ (NULL),
	prev_ (prev),
	scope_ (NULL)
	{
		if (prev != NULL) {
			prev->setNext (this);
		}
	}
	Notation :: ~ Notation()
	{
		deleteAggregateObject (variables_);
		deleteAggregateObject (abbreviation_);
		deleteAggregateObject (meaning_);
		deleteAggregateObject (next_);
		deleteAggregateObject (scope_);
	}

	// mdl :: proof :: Notation implementation
	value :: Literal
	Notation :: getLiteral() const {
		return literal_;
	}
	mdl :: Variables*
	Notation :: getVariables() {
		return variables_;
	}
	mdl :: proof :: Term*
	Notation :: getAbbreviation() {
		return abbreviation_;
	}
	mdl :: proof :: Term*
	Notation :: getMeaning() {
		return meaning_;
	}
	const mdl :: Variables*
	Notation :: getVariables() const {
		return variables_;
	}
	const mdl :: proof :: Term*
	Notation :: getAbbreviation() const {
		return abbreviation_;
	}
	const mdl :: proof :: Term*
	Notation :: getMeaning() const {
		return meaning_;
	}

	// mdl :: proof :: Line implementation
	Notation :: Sort
	Notation :: getSort() const {
		return NOTATION;
	}
	const mdl :: proof :: Line*
	Notation :: getNext() const {
		return next_;
	}
	const mdl :: proof :: Line*
	Notation :: getPrev() const {
		return prev_;
	}
	void
	Notation :: incIndex (const index :: Step) {
	}
	void
	Notation :: decIndex (const index :: Step) {
	}
	void
	Notation :: setNext (mdl :: proof :: Line* line) {
		next_ = line;
	}
	void
	Notation :: setPrev (mdl :: proof :: Line* line) {
		prev_ = line;
	}
	mdl :: proof :: Line*
	Notation :: getNext() {
		return next_;
	}
	mdl :: proof :: Line*
	Notation :: getPrev() {
		return prev_;
	}
	const Location&
	Notation :: getLocation() const {
		return location_;
	}

	// object :: Scoping implementation
	mdl :: proof :: Scope*
	Notation :: buildScope (mdl :: proof :: Scope* scope)
	{
		scope_ = new proof :: scope :: Notation (scope, this);
		return scope_;
	}
	void
	Notation :: setScope (mdl :: proof :: Scope* scope) {
		scope_ = scope;
	}
	mdl :: proof :: Scope*
	Notation :: getScope() {
		return scope_;
	}
	const mdl :: proof :: Scope*
	Notation :: getScope() const {
		return scope_;
	}

	// object :: Buildable implementation
	void
	Notation :: build()
	{
		variables_->build();
		abbreviation_->build();
		meaning_->build();
	}

using manipulator :: space;
using manipulator :: underline;
using manipulator :: endLine;

	// object :: Writable implementation
	void
	Notation :: translate (String&) const {
	}
	void
	Notation :: replicate (String& string) const
	{
		string << location_.getIndent() << Token :: notation_ << space;
		string << Table :: literals()->get (literal_) << space;
		variables_->replicate (string);
		string << Token :: openBrace_ << endLine;
		abbreviation_->replicate (string);
		meaning_->replicate (string);
		string << Token :: closeBrace_ << endLine;
	}

	// object :: Object implementation
	void
	Notation :: commitSuicide() {
		delete this;
	}
	Size_t
	Notation :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (variables_);
		volume += getAggregateVolume (abbreviation_);
		volume += getAggregateVolume (meaning_);

		volume += getAggregateVolume (next_);
		volume += getAggregateVolume (scope_);
		return volume;
	}
	Size_t
	Notation :: getSizeOf() const {
		return sizeof (Notation);
	}
}
}
}
}


