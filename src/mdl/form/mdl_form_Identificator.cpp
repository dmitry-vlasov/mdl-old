/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_Identificator.cpp                               */
/* Description:     identificator                                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/lexer/mdl_lexer.hpp"
#include "mdl/form/mdl_form_Identificator.hpp"

namespace mdl {
namespace form {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Identificator :: Identificator () :
	location_(),
	name_ (value :: undefined :: NAME),
	next_ (NULL) {
	}
	inline
	Identificator :: Identificator (const mdl :: Identificator& identificator) :
	location_ (),
	name_ (identificator.getName()),
	next_
	(
		(identificator.getNext() == NULL) ?
			NULL :
			new Identificator (identificator.getNext())
	) {
	}
	inline
	Identificator :: Identificator (const mdl :: Identificator* identificator) :
	location_ (),
	name_ (identificator->getName()),
	next_
	(
		(identificator->getNext() == NULL) ?
			NULL :
			new Identificator (identificator->getNext())
	) {
	}
	inline
	Identificator :: Identificator (const value :: Name name) :
	location_(),
	name_ (name),
	next_ (NULL) {
	}
	inline
	Identificator :: Identificator
	(
		const value :: Name name,
		const Location& location
	) :
	location_ (location),
	name_ (name),
	next_ (NULL) {
	}
	Identificator :: Identificator (const char* identificator) :
	location_(),
	name_ (value :: undefined :: NAME),
	next_ (NULL)
	{
		const char* nameBegin = identificator;
		const char* nameEnd = identificator;
		while (*nameEnd != '.' && *nameEnd != '\0') {
			++ nameEnd;
		}
		String nameString (nameBegin, nameEnd);
		name_ = Table :: names()->find (nameString);
		if (*nameEnd != '\0') {
			next_ = new Identificator (++ nameEnd);
		}
	}
	Identificator :: Identificator (const String& identificator) :
	location_(),
	name_ (value :: undefined :: NAME),
	next_ (NULL)
	{
		const char* nameBegin = identificator.c_str();
		const char* nameEnd = identificator.c_str();
		while (*nameEnd != '.' && *nameEnd != '\0') {
			++ nameEnd;
		}
		String nameString (nameBegin, nameEnd);
		name_ = Table :: names()->find (nameString);
		if (*nameEnd != '\0') {
			next_ = new Identificator (++ nameEnd);
		}
	}
	Identificator :: ~ Identificator() {
		deleteAggregateObject (next_);
	}

	// mdl :: Identificator implementation
	value :: Name
	Identificator :: getName() const {
		return name_;
	}
	void
	Identificator :: setNext (mdl :: Identificator* next) {
		next_ = next;
	}
	mdl :: Identificator*
	Identificator :: getNext() {
		return next_;
	}
	const mdl :: Identificator*
	Identificator :: getNext() const {
		return next_;
	}


using manipulator :: underline;

	// object :: Writable implementation
	void
	Identificator :: translate (String& string) const
	{
		if (name_ != value :: undefined :: NAME) {
			string << Table :: names()->get (name_);
		}
		if (next_ != NULL) {
			if (name_ != value :: undefined :: NAME) {
				string << underline;
			}
			next_->replicate (string);
		}
	}
	void
	Identificator :: replicate (String& string) const
	{
		if (name_ != value :: undefined :: NAME) {
			string << Table :: names()->get (name_);
		}
		if (next_ != NULL) {
			if (name_ != value :: undefined :: NAME) {
				string << Token :: dot_;
			}
			next_->replicate (string);
		}
	}
	bool
	Identificator :: lookup() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return true;
		} else {
			return false;
		}
	}
	object :: Writable*
	Identificator :: find()
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		} else {
			return NULL;
		}
	}
	const object :: Writable*
	Identificator :: find() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		} else {
			return NULL;
		}
	}

	// object :: Object implementation
	void
	Identificator :: commitSuicide() {
		delete this;
	}
	Size_t
	Identificator :: getVolume() const {
		return getAggregateVolume (next_);
	}
	Size_t
	Identificator :: getSizeOf() const {
		return sizeof (Identificator);
	}
}
}


