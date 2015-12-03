/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_statement_Definition.cpp                 */
/* Description:     definition statement class                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_HEADER_STATEMENT_DEFINITION_CPP_
#define MDL_FORM_HEADER_STATEMENT_DEFINITION_CPP_

namespace mdl {
namespace form {
namespace header {
namespace statement {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Definition :: Definition
	(
		const Location& location,
		index :: Arity index,
		mdl :: Identificator* identificator,
		array :: Expression* expression,
		mdl :: Theory* theory
	) :
	header :: statement :: Proposition
	(
		location,
		index,
		identificator,
		expression,
		theory
	),
	expandedExpression_ (NULL),
	originalExpression_ (NULL),
	defiendum_ (NULL),
	definiens_ (NULL),
	metaVariables_ (NULL) {
	}
	Definition :: ~ Definition()
	{
		if (expression_ != originalExpression_) {
			deleteAggregateObject (originalExpression_);
		}
		if (expression_ != expandedExpression_) {
			deleteAggregateObject (expandedExpression_);
		}
		deleteAggregateObject (metaVariables_);
	}

	// statement :: Definition implementation
	void
	Definition :: setDefiendum (mdl :: term :: Definition* defiendum) {
		defiendum_ = defiendum;
	}
	void
	Definition :: setDefiniens (mdl :: term :: Definition* definiens) {
		definiens_ = definiens;
	}

	// mdl :: Proposition interface
	/*const Location&
	Definition :: getLocation() const {
		return Proposition :: getLocation();
	}
	index :: Assertion
	Definition :: getSourceIndex() const {
		return Proposition :: getSourceIndex();
	}
	index :: Assertion
	Definition :: getTargetIndex() const {
		return Proposition :: getTargetIndex();
	}
	mdl :: statement :: Experience*
	Definition :: getExperience() const {
		return Proposition :: getExperience();
	}
	mdl :: evaluation :: Function*
	Definition :: getEvaluation (const value :: Name name) {
		return Proposition :: getEvaluation (name);
	}
	const mdl :: evaluation :: Function*
	Definition :: getEvaluation (const value :: Name name) const {
		return Proposition :: getEvaluation (name);
	}

	void
	Definition :: incRate (const bool sign) const {
		Proposition :: incRate (sign);
	}
	value :: Integer
	Definition :: getRate (const bool sign) const {
		return Proposition :: getRate (sign);
	}*/

	// mdl :: Statement implementation
	void
	Definition :: setAssertion (mdl :: Assertion* assertion)
	{
		Proposition :: setAssertion (assertion);
		defiendum_ = dynamic_cast<mdl :: Definition*> (assertion_)->getDefiendum();
		definiens_ = dynamic_cast<mdl :: Definition*> (assertion_)->getDefiniens();
	}
	/*index :: Arity
	Definition :: getIndex() const {
		return Proposition :: getIndex();
	}
	const mdl :: proof :: Node*
	Definition :: getProofNode() const {
		return Proposition :: proofNode_;
	}*/

	// object :: Expressive implementation
	/*const array :: Expression*
	Definition :: getExpression() const {
		return Proposition :: expression_;
	}
	const mdl :: Type*
	Definition :: getType() const {
		return header :: Line :: type_;
	}*/

	// object :: Buildable implementation
	void
	Definition :: build()
	{
		substituteTerms();
		originalExpression_ = expression_;
		expression_ = expandedExpression_;
		Proposition :: build();
		buildOriginal();
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Definition :: translate (String& string) const
	{
		string << tab;
		assertion_->translateName (string);
		string << space;
		string << :: smm :: Token :: axiomatic_ << space;
		Proposition :: translate (string);
		string << :: smm :: Token :: end_ << endLine;
	}
	void
	Definition :: replicate (String& string) const
	{
		if (originalExpression_ != NULL) {
			const_cast<const array :: Expression*&>(expression_) = originalExpression_;
		}
		Proposition :: replicate (string);
		if (originalExpression_ != NULL) {
			const_cast<const array :: Expression*&>(expression_) = expandedExpression_;
		}
	}

	// object :: Object implementation
	void
	Definition :: commitSuicide() {
		delete this;
	}
	Size_t
	Definition :: getVolume() const
	{
		Size_t volume = 0;
		volume += Proposition :: getVolume();
		if (expression_ != originalExpression_) {
			volume += getAggregateVolume (originalExpression_);
		}
		if (expression_ != expandedExpression_) {
			volume += getAggregateVolume (expandedExpression_);
		}
		volume += getAggregateVolume (metaVariables_);
		return volume;
	}
	Size_t
	Definition :: getSizeOf() const {
		return sizeof (Definition);
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Definition :: insert
	(
		value :: Literal* literals,
		index :: Literal& index,
		mdl :: term :: Definition* term
	) const
	{
		array :: Expression*
			expression = term->getExpression();
		for (index :: Literal i = 0 ; i < expression->getSize(); ++ i) {
			literals [index ++] = expression->getSymbol (i).getLiteral();
		}
	}
	index :: Literal
	Definition :: calculateLength() const
	{
		index :: Literal length = 0;
		length += expression_->getSize();
		length += defiendum_->getExpression()->getSize();
		length += definiens_->getExpression()->getSize();
		return length - 2;
	}
	void
	Definition :: substituteTerms ()
	{
		const index :: Literal
			length = calculateLength();

		value :: Literal literals [length];
		index :: Literal index = 0;

		if (defiendumKeyword_ == value :: undefined :: LITERAL) {
			defiendumKeyword_= Table :: literals()->find (Token :: defiendum_.getString());
			definiensKeyword_= Table :: literals()->find (Token :: definiens_.getString());
		}
		bool defiendumMet = false;
		bool definiensMet = false;
		for (index :: Literal i = 0; i < Proposition :: expression_->getSize(); ++ i) {
			substituteSymbol (i, literals, index, defiendumMet, definiensMet);
		}
		expandedExpression_ = new array :: Expression (literals, length);
	}
	void
	Definition :: substituteSymbol
	(
		const index :: Literal i,
		value :: Literal* literals,
		index :: Literal& index,
		bool& defiendumMet,
		bool& definiensMet
	) const
	{
		const Symbol& symbol = Proposition :: expression_->getSymbol (i);
		if (symbol.getLiteral() == defiendumKeyword_) {
			if (defiendumMet) {
				Error* error = new Error (location_,Error :: SEMANTIC);
				error->message() << "defiendum already met in definition.";
				throw error;
			}
			insert (literals, index, defiendum_);
			defiendumMet = true;
		} else if (symbol.getLiteral() == definiensKeyword_) {
			if (definiensMet) {
				Error* error = new Error (location_,Error :: SEMANTIC);
				error->message() << "definiens already met in definition.";
				throw error;
			}
			insert (literals, index, definiens_);
			definiensMet = true;
		} else {
			literals [index ++] = symbol.getLiteral();
		}
	}
	void
	Definition :: buildOriginal()
	{
		try {
			metaVariables_ = new MetaVariables_
			(
				assertion_->getVariables(),
				defiendum_,
				definiens_
			);
			array :: Expression*
				expression = originalExpression_;
			expression->build (metaVariables_);
			expression->parse (type_);
		} catch (Error* error) {
			error->add (location_);
			throw error;
		}
		if (!originalExpression_->isPrimitive()) {
			Error* error = new Error (location_, Error :: SEMANTIC);
			error->message() << "definition proposition: " << *originalExpression_ << space;
			error->message() << "is not primitive." << endLine;
			throw error;
		}
	}

	/*************************************
	 *		Static private attributes
	 *************************************/

	value :: Literal
		Definition :: defiendumKeyword_ = value :: undefined :: LITERAL;
	value :: Literal
		Definition :: definiensKeyword_ = value :: undefined :: LITERAL;
}
}
}
}

#endif /*MDL_FORM_HEADER_STATEMENT_DEFINITION_CPP_*/

