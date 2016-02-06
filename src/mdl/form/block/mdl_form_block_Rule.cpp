/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_block_Rule.cpp                                  */
/* Description:     syntax grammar rule class                                */
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
	Rule :: Rule
	(
		const Location& location,
		const mdl :: Comments* comments,
		value :: Name name,
		mdl :: Variables* variables,
		mdl :: term :: Rule* term,
		mdl :: Theory* theory
	) :
	form :: Identifiable (location, comments, name, theory),
	type_ (NULL),
	variables_ (variables),
	term_ (term)
	{
		Math :: rules()->add (this);
		if (Config :: localParsing()) {
			return;
		}
		term_->setRule (this);
		theory->addComponent (this);

		if (Config :: shallowParsing() && !location_.isTop()) {
			return;
		}
		form :: Identifiable :: build();
		variables_->build();
		if (Config :: shallowParsing()) {
			return;
		}
		try {
			term_->build();
		} catch (Error* error) {
			error->add (location_);
			error->message() << "rule ";
			replicateName (error->message());
			error->message() << endLine;
			throw error;
		}
	}
	Rule :: ~ Rule()
	{
		deleteAggregateObject (variables_);
		deleteAggregateObject (term_);
	}

	// mdl :: Rule implementation
	void
	Rule :: setType (mdl :: Type* type) {
		type_ = type;
	}
	mdl :: Type*
	Rule :: getType() {
		return type_;
	}
	mdl :: Variables*
	Rule :: getVariables() {
		return variables_;
	}
	mdl :: term :: Rule*
	Rule :: getTerm() {
		return term_;
	}
	const mdl :: Type*
	Rule :: getType() const {
		return type_;
	}
	const mdl :: Variables*
	Rule :: getVariables() const {
		return variables_;
	}
	const mdl :: term :: Rule*
	Rule :: getTerm() const {
		return term_;
	}

	// object :: Identifiable implementation
	/*const mdl :: Theory*
	Rule :: getTheory() const {
		return Identifiable :: getTheory();
	}
	value :: Name
	Rule :: getName() const {
		return Identifiable :: getName();
	}*/
	void
	Rule :: translateName (String& string, const index :: Arity) const
	{
		string << :: smm :: Token :: prefix_a_;
		if (Config :: noLabels()) {
			string << term_->getTargetIndex();
		} else {
			Identifiable :: translateName (string);
		}
	}
	void
	Rule :: replicateName (String& string) const {
		Identifiable :: replicateName (string);
	}

using manipulator :: tab;
using manipulator :: iterate;
using manipulator :: space;
using manipulator :: endLine;

	// object :: Verifiable implementation
	/*void
	Rule :: check() {
	}
	void
	Rule :: compress() {
	}
	void
	Rule :: reprove() {
	}
	void
	Rule :: prove() {
	}
	bool
	Rule :: isVerified() const {
		return true;
	}*/
	void
	Rule :: mine (String& string) const
	{
		if (!Config :: getMiningOptions().getValue (Config :: MINE_RULES)) {
			return;
		}
		const value :: Integer depth =
			Config :: getMiningOptions().getValue (Config :: MINE_THEORIES) ?
			Identifiable :: getDepth() :
			1;
		string << iterate << depth << tab << "<rule ";
		Identifiable :: mine (string);
		string << "/>" << endLine;
	}

	// object :: Buildable implementation
	void
	Rule :: build() {
	}

	// object :: Writable implementation
	void
	Rule :: translate (String& string) const
	{
		if (!Config :: removeComments() && (comments_ != NULL)) {
			string << location_.getIndent();
			comments_->translate (string);
			string << endLine;
		}
		string << :: smm :: Token :: blockBegin_ << endLine;
		variables_->translate (string);
		term_->translate (string);
		string << :: smm :: Token :: blockEnd_ << endLine;
		string << endLine;
	}
	void
	Rule :: replicate (String& string) const
	{
		if (!Config :: removeComments() && (comments_ != NULL)) {
			string << location_.getIndent();
			comments_->replicate (string);
			string << endLine;
		}
		string << location_.getIndent() << Token :: rule_ << space;
		replicateName (string);
		string << space;
		variables_->replicate (string); string << endLine;
		string << location_.getIndent() << Token :: openBrace_ << endLine;
		term_->replicate (string);
		string << location_.getIndent() << Token :: closeBrace_ << endLine;
		string << endLine;
	}
	bool
	Rule :: lookup() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return true;
		}
		if (variables_->lookup()) {
			return true;
		}
		return term_->lookup();
	}
	object :: Writable*
	Rule :: find()
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		}
		object :: Writable* object = variables_->find();
		if (object != NULL) {
			return object;
		}
		return term_->find();
	}
	const object :: Writable*
	Rule :: find() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		}
		const object :: Writable* object = variables_->find();
		if (object != NULL) {
			return object;
		}
		return term_->find();
	}

	// object :: Object implementation
	void
	Rule :: commitSuicide() {
		delete this;
	}
	Size_t
	Rule :: getVolume() const
	{
		Size_t result = 0;
		result += Identifiable :: getVolume();
		result += getAggregateVolume (variables_);
		result += getAggregateVolume (term_);
		return result;
	}
	Size_t
	Rule :: getSizeOf() const {
		return sizeof (Rule);
	}
}
}
}


