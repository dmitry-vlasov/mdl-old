/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_Line.cpp                                 */
/* Description:     header line                                              */
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

using manipulator :: endLine;

	inline
	Line :: Line
	(
		const Location& location,
		mdl :: Identificator* identificator,
		array :: Expression* expression,
		mdl :: Theory* theory
	) :
	location_ (location),
	identificator_ (identificator),
	type_ (NULL),
	expression_ (expression)
	{
		if (Config :: localParsing()) {
			return;
		}
		if (Config :: shallowParsing() && !location_.isTop()) {
			return;
		}
		const index :: Type
			index = theory->getIndex (identificator_);
		type_ = Math :: types()->get (index);
		if (type_ == NULL) {
			Error* error = new Error (Error :: SEMANTIC, "undefined type ");
			error->message() << *identificator_ << endLine;
			throw error;
		}
	}
	Line :: ~ Line()
	{
		deleteAggregateObject (expression_);
		deleteAggregateObject (identificator_);
	}

	// object :: Expressive implementation
	mdl :: Type*
	Line :: getType() {
		return type_;
	}
	array :: Expression*
	Line :: getExpression() {
		return expression_;
	}
	const mdl :: Type*
	Line :: getType() const {
		return type_;
	}
	const array :: Expression*
	Line :: getExpression() const {
		return expression_;
	}

	// object :: Buildable implementation
	void
	Line :: build() {
	}

	// object :: Writable implementation
	bool
	Line :: lookup() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return true;
		}
		if (identificator_->lookup()) {
			if (Config :: lookupDefinition()) {
				std :: cout << *type_;
			} else {
				std :: cout << type_->getLocation();
			}
			return true;
		} else {
			return false;
		}
	}
	object :: Writable*
	Line :: find()
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		}
		if (identificator_->lookup()) {
			return type_;
		} else {
			return NULL;
		}
	}
	const object :: Writable*
	Line :: find() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		}
		if (identificator_->lookup()) {
			return type_;
		} else {
			return NULL;
		}
	}

	// object :: Object implementation
	Size_t
	Line :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (expression_);
		volume += getAggregateVolume (identificator_);
		return volume;
	}
	Size_t
	Line :: getSizeOf() const {
		return sizeof (Line);
	}

	inline const Location&
	Line :: getLocation() const {
		return location_;
	}

	inline void
	Line :: Counter :: setIndex() const
	{
		if (index_ == index :: undefined :: ASSERTION) {
			const_cast<index :: Assertion&>(index_) = counter_ ++;
		}
	}
	inline index :: Assertion
	Line :: Counter :: getIndex() const
	{
		if (index_ == index :: undefined :: ASSERTION) {
			const_cast<index :: Assertion&>(index_) = counter_ ++;
		}
		return index_;
	}

	/****************************
	 *		Protected members
	 ****************************/

	inline Line :: Counter :: Counter () :
	index_ (index :: undefined :: ASSERTION) {
	}

	/************************************
	 *		Static private attributes
	 ************************************/

	index :: Assertion
		Line :: Counter :: counter_ = 0;
}
}
}


