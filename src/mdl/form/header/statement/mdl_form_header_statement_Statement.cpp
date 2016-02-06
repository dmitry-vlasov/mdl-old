/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_statement_Statement.cpp                  */
/* Description:     statement class                                          */
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
	Statement :: Statement
	(
		const Location& location,
		index :: Arity index,
		mdl :: Identificator* identificator,
		array :: Expression* expression,
		mdl :: Theory* theory
	) :
	header :: Line
	(
		location,
		identificator,
		expression,
		theory
	),
	assertion_ (NULL),
	index_ (index),
	proofNode_ (NULL) {
	}
	Statement :: ~ Statement() {
		deleteAggregateObject (proofNode_);
	}

	// mdl :: Statement implementation
	void
	Statement :: setAssertion (mdl :: Assertion* assertion) {
		assertion_ = assertion;
	}
	index :: Arity
	Statement :: getIndex() const {
		return index_;
	}
	mdl :: Assertion*
	Statement :: getAssertion() {
		return assertion_;
	}
	mdl :: proof :: Node*
	Statement :: getProofNode() {
		return proofNode_;
	}
	const mdl :: Assertion*
	Statement :: getAssertion() const {
		return assertion_;
	}
	const mdl :: proof :: Node*
	Statement :: getProofNode() const {
		return proofNode_;
	}

	// object :: Buildable implementation
	void
	Statement :: build()
	{
		try {
			header :: Line :: build();
			expression_->build (assertion_->getVariables());
			expression_->parse (type_);
		} catch (Error* error) {
			error->add (location_);
			throw error;
		}
	}

	// object :: Object implementation
	void
	Statement :: commitSuicide() {
		delete this;
	}
	Size_t
	Statement :: getVolume() const
	{
		Size_t volume = 0;
		volume += header :: Line :: getVolume();
		volume += getAggregateVolume (proofNode_);
		return volume;
	}
	Size_t
	Statement :: getSizeOf() const {
		return sizeof (Statement);
	}
}
}
}
}


