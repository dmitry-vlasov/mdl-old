/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_notation_Term.cpp                         */
/* Description:     notation term class                                      */
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

	inline
	Term :: Term
	(
		const Location& location,
		mdl :: Identificator* identificator,
		array :: Expression* expression,
		mdl :: Theory* theory
	) :
	location_ (location),
	theory_ (theory),
	identificator_ (identificator),
	type_ (NULL),
	expression_ (expression) {
	}
	Term :: ~ Term()
	{
		deleteAggregateObject (expression_);
		deleteAggregateObject (identificator_);
	}

	// object :: Expressive implementation
	array :: Expression*
	Term :: getExpression() {
		return expression_;
	}
	mdl :: Type*
	Term :: getType() {
		return type_;
	}
	const array :: Expression*
	Term :: getExpression() const {
		return expression_;
	}
	const mdl :: Type*
	Term :: getType() const {
		return type_;
	}

	// object :: Buildable implementation
	void
	Term :: build()
	{
		try {
			const index :: Type
				index = theory_->getIndex (identificator_);
			type_ = Math :: types()->get (index);
			expression_->parse (type_);
		} catch (Error* error) {
			error->add (location_);
			throw error;
		}
	}

	// object :: Writable interface
	void
	Term :: translate (String&) const {
	}

	// object :: Object implementation
	Size_t
	Term :: getVolume() const {
		Size_t volume = 0;
		volume += getAggregateVolume (expression_);
		volume += getAggregateVolume (identificator_);
		return volume;
	}
	Size_t
	Term :: getSizeOf() const {
		return sizeof (Term);
	}
}
}
}
}


