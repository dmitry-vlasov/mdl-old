/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_block_Definition.cpp                            */
/* Description:     definition class                                         */
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
	Definition :: Definition
	(
		const Location& location,
		const mdl :: Comments* comments,
		lexer :: Indent barIndent,
		value :: Name name,
		mdl :: Variables* variables,
		mdl :: Disjointeds* disjointeds,
		mdl :: term :: Definition* defiendum,
		mdl :: term :: Definition* definiens,
		const vector :: parser :: Hypothesis& hypothesisVector,
		const vector :: parser :: Definition& propositionVector,
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
	),
	defiendum_ (defiendum),
	definiens_ (definiens)
	{
		Ancestor_ :: add (this);
		defiendum_->setDefinition (this);
		definiens_->setDefinition (this);
	}
	Definition :: ~ Definition()
	{
		deleteAggregateObject (defiendum_);
		deleteAggregateObject (definiens_);
	}

	// mdl :: Definition implementation
	mdl :: term :: Definition*
	Definition :: getDefiendum() {
		return defiendum_;
	}
	mdl :: term :: Definition*
	Definition :: getDefiniens() {
		return definiens_;
	}
	const mdl :: term :: Definition*
	Definition :: getDefiendum() const {
		return defiendum_;
	}
	const mdl :: term :: Definition*
	Definition :: getDefiniens() const {
		return definiens_;
	}

	// mdl :: Assertion implementation
	mdl :: Assertion :: Kind
	Definition :: getKind() const {
		return mdl :: Assertion :: DEFINITION;
	}

	// object :: Buildable implementation
	void
	Definition :: build()
	{
		Ancestor_ :: buildVariables();
		Ancestor_ :: buildHypothesis();

		defiendum_->build();
		definiens_->build();

		const array :: Expression*
			defiendum = defiendum_->getExpression();
		if (!defiendum->isPrimitive()) {
			if (Config :: warnings()) {
				std :: cout << "Warning: defiendum term " << *defiendum << " ";
				std :: cout << "is not primitive." << std :: endl;
			}
		}
		Ancestor_ :: buildPropositions();
	}

using nstd :: manipulator :: space;
using nstd :: manipulator :: endLine;

	// object :: Writable implementation
	void
	Definition :: replicate (String& string) const
	{
		if (!Config :: removeComments() && (comments_ != NULL)) {
			string << location_.getIndent();
			comments_->replicate (string);
			string << endLine;
		}
		string << location_.getIndent() << Token :: definition_ << space;
		replicateHeader (string);
		string << location_.getIndent() << Token :: openBrace_<< endLine;
		defiendum_->replicate (string);
		definiens_->replicate (string);
		replicateHypothesis (string);
		replicateBar (string);
		replicatePropositions (string);
		string << location_.getIndent() << Token :: closeBrace_<< endLine;
	}
	bool
	Definition :: lookup() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return true;
		}
		if (defiendum_->lookup()) {
			return true;
		}
		if (definiens_->lookup()) {
			return true;
		}
		return false;
	}
	object :: Writable*
	Definition :: find()
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		}
		object :: Writable* object = NULL;
		object = defiendum_->find();
		if (object != NULL) {
			return object;
		}
		object = definiens_->find();
		if (object != NULL) {
			return object;
		}
		return NULL;
	}
	const object :: Writable*
	Definition :: find() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		}
		const object :: Writable* object = NULL;
		object = defiendum_->find();
		if (object != NULL) {
			return object;
		}
		object = definiens_->find();
		if (object != NULL) {
			return object;
		}
		return NULL;
	}

	// object :: Object implementation
	void
	Definition :: commitSuicide() {
		delete this;
	}
	Size_t
	Definition :: getVolume() const
	{
		Size_t result = 0;
		result += Ancestor_ :: getVolume();
		result += getAggregateVolume (defiendum_);
		result += getAggregateVolume (definiens_);
		return result;
	}
	Size_t
	Definition :: getSizeOf() const {
		return sizeof (Definition);
	}

	/****************************
	 *		Private members
	 ****************************/
}
}
}


