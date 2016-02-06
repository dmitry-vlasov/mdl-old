/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_Step.cpp                                  */
/* Description:     proof step                                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/math/mdl_math.hpp"
#include "mdl/form/proof/mdl_form_proof_Step.hpp"

namespace mdl {
namespace form {
namespace proof {

	/****************************
	 *		Public members
	 ****************************/

	Step :: Step
	(
		mdl :: proof :: Line* prev,
		const Location& location,
		const mdl :: Comments* comments,
		index :: Step index,
		mdl :: Identificator* identificator,
		array :: Expression* expression,
		mdl :: Theory* theory,
		mdl :: proof :: Scope* scope
	) :
	location_ (location),
	theory_ (theory),
	comments_ (comments),
	index_ (index),
	identificator_ (identificator),
	type_ (NULL),
	expression_ (expression),
	next_ (NULL),
	prev_ (prev),
	scope_ (scope),
	isVerified_ (false)
	{
		if (Config :: localParsing()) {
			return;
		}
		const index :: Type
			typeIndex = theory_->getIndex (identificator_);
		if (typeIndex == index :: undefined :: TYPE) {
			Error* error = new Error (location_, Error :: SEMANTIC, "undefined type");
			throw error;
		}
		type_ = Math :: types()->get (typeIndex);
		if (prev != NULL) {
			prev->setNext (this);
		}
	}
	Step :: Step (mdl :: proof :: Step* step) :
	location_ (step->getLocation()),
	theory_ (NULL),
	comments_ (NULL),
	index_ (step->getIndex()),
	identificator_ (NULL),
	type_ (step->getType()),
	expression_ (new array :: Expression (step->getExpression())),
	next_ (step->getNext()),
	prev_ (step->getPrev()),
	scope_ (step->getScope()),
	isVerified_ (false) {
	}
	Step :: Step
	(
		mdl :: proof :: Step* step,
		index :: Step index,
		array :: Expression* expression
	) :
	location_ (step->getLocation()),
	theory_ (NULL),
	comments_ (NULL),
	index_ (index),
	identificator_ (NULL),
	type_ (const_cast<mdl :: Type*>(expression->getType())),
	expression_ (expression),
	next_ (NULL),
	prev_ (NULL),
	scope_ (step->getScope()),
	isVerified_ (false) {
	}
	inline
	Step :: Step
	(
		index :: Step index,
		array :: Expression* expression
	) :
	location_ (),
	theory_ (NULL),
	comments_ (NULL),
	index_ (index),
	identificator_ (NULL),
	type_ (const_cast<mdl :: Type*>(expression->getType())),
	expression_ (expression),
	next_ (NULL),
	prev_ (NULL),
	scope_ (NULL),
	isVerified_ (false) {
	}
	Step :: Step (mdl :: Proposition* proposition) :
	location_ (proposition->getLocation()),
	theory_ (NULL),
	comments_ (NULL),
	index_ (proposition->getIndex()),
	identificator_ (NULL),
	type_ (const_cast<mdl :: Type*>(proposition->getExpression()->getType())),
	expression_ (new array :: Expression (proposition->getExpression())),
	next_ (NULL),
	prev_ (NULL),
	scope_ (NULL),
	isVerified_ (false) {
		expression_->setReplaceable (false);
	}
	Step :: ~ Step()
	{
		deleteAggregateObject (comments_);
		deleteAggregateObject (identificator_);
		deleteAggregateObject (expression_);
	}

	// proof :: Step implementation
	mdl :: proof :: Question*
	Step :: questionSelf() {
		return new proof :: step :: Question (this);
	}

	// proof :: Node implementation
	Step :: Kind
	Step :: getKind() const {
		return mdl :: proof :: Node :: STEP;
	}
	index :: Step
	Step :: getIndex() const {
		return index_;
	}

	// proof :: Line implementation
	Step :: Sort
	Step :: getSort() const {
		return mdl :: proof :: Line :: STEP;
	}
	void
	Step :: incIndex (const index :: Step index)
	{
		if (index_ >= index) {
			++ index_;
		}
	}
	void
	Step :: decIndex (const index :: Step index)
	{
		if (index_ > index) {
			-- index_;
		}
	}
	void
	Step :: setNext (Line* line) {
		next_ = line;
	}
	void
	Step :: setPrev (Line* line) {
		prev_ = line;
	}
	mdl :: proof :: Line*
	Step :: getNext() {
		return next_;
	}
	mdl :: proof :: Line*
	Step :: getPrev() {
		return prev_;
	}
	const mdl :: proof :: Line*
	Step :: getNext() const {
		return next_;
	}
	const mdl :: proof :: Line*
	Step :: getPrev() const {
		return prev_;
	}
	const Location&
	Step :: getLocation() const {
		return location_;
	}

	// object :: Scoping implementation
	mdl :: proof :: Scope*
	Step :: buildScope (mdl :: proof :: Scope* scope)
	{
		try {
			scope_ = scope;
			if (expression_->getTerm() == NULL) {
				object :: Typing* variables = scope_->getVariables();
				expression_->build (variables, true);
				expression_->parse (type_);
			}
			return scope;
		} catch (Error* error) {
			error->add (location_);
			throw error;
		}
	}
	void
	Step :: setScope (mdl :: proof :: Scope* scope) {
		scope_ = scope;
	}
	mdl :: proof :: Scope*
	Step :: getScope() {
		return scope_;
	}
	const mdl :: proof :: Scope*
	Step :: getScope() const {
		return scope_;
	}

	// object :: Expressive implementation
	array :: Expression*
	Step :: getExpression() {
		return expression_;
	}
	mdl :: Type*
	Step :: getType() {
		return type_;
	}
	const array :: Expression*
	Step :: getExpression() const {
		return expression_;
	}
	const mdl :: Type*
	Step :: getType() const {
		return type_;
	}

	// object :: Verifiable implementation
	void
	Step :: reprove() {
	}

	// object :: Verifiable implementation
	bool
	Step :: isVerified() const {
		return isVerified_;
	}

	// object :: Writable implementation
	bool
	Step :: lookup() const
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
	Step :: find()
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
	Step :: find() const
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

using manipulator :: endLine;
using manipulator :: space;

	// object :: Object implementation
	Size_t
	Step :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (comments_);
		volume += getAggregateVolume (identificator_);
		volume += getAggregateVolume (expression_);
		return volume;
	}
	Size_t
	Step :: getSizeOf() const {
		return sizeof (Step);
	}
}
}
}


