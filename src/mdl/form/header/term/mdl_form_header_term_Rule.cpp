/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_term_Rule.cpp                            */
/* Description:     syntax rule term class                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_HEADER_TERM_RULE_CPP_
#define MDL_FORM_HEADER_TERM_RULE_CPP_

#include "mdl/math/mdl_math.hpp"
#include "mdl/form/header/term/mdl_form_header_term_Rule.hpp"

#include "smm/lexer/smm_lexer_Token.hpp"

namespace mdl {
namespace form {
namespace header {
namespace term {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Rule :: Rule
	(
		const Location& location,
		index :: Arity,
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
	header :: Line :: Counter(),
	rule_ (NULL) {
	}
	Rule :: ~ Rule() {
	}

	// mdl :: term :: Rule implementation
	void
	Rule :: setRule (mdl :: Rule* rule) {
		rule_ = rule;
	}
	index :: Assertion
	Rule :: getTargetIndex() const {
		return header :: Line :: Counter :: getIndex();
	}

	// object :: Expressive implementation
	/*mdl :: Type*
	Rule :: getType() {
		return header :: Line :: type_;
	}
	const array :: Expression*
	Rule :: getExpression() const {
		return header :: Line :: expression_;
	}
	const mdl :: Type*
	Rule :: getType() const {
		return header :: Line :: type_;
	}
	const array :: Expression*
	Rule :: getExpression() const {
		return header :: Line :: expression_;
	}*/

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Buildable implementation
	void
	Rule :: build()
	{
		try {
			Line :: build();
			rule_->setType (type_);
			expression_->build (rule_->getVariables());
			expression_->create (rule_);
			type_->addRule (rule_);
		} catch (Error* error) {
			error->add (location_);
			throw error;
		}
		checkSemantics();
	}

	// object :: Writable implementation
	void
	Rule :: translate (String& string) const
	{
		string << tab;
		rule_->translateName (string);
		string << space;
		string << :: smm :: Token :: axiomatic_ << space;
		type_->translateName (string);
		string << space;
		expression_->write (string);
		string << :: smm :: Token :: end_ << endLine;
	}
	void
	Rule :: replicate (String& string) const
	{
		string << location_.getIndent() << Token :: term_ << space;
		string << Token :: colon_ << space;
		identificator_->replicate (string);
		string << space;
		string << Token :: equality_ << space;
		string << Token :: sharp_ << space;
		expression_->write (string);
		string << Token :: semicolon_ << endLine;
	}

	// object :: Object implementation
	void
	Rule :: commitSuicide() {
		delete this;
	}
	Size_t
	Rule :: getVolume() const {
		return header :: Line :: getVolume();
	}
	Size_t
	Rule :: getSizeOf() const {
		return sizeof (Rule);
	}

	/****************************
	 *		Public members
	 ****************************/

	void
	Rule :: checkSemantics() const
	{
		if (expression_->getBegin()->isVariable()) {
			Error* error = new Error (location_, Error :: SEMANTIC);
			error->message() << "syntax rule term must not start with a variable." << endLine;
			error->message() << tab << "term: " << *expression_ << endLine;
			throw error;
		}
		for (index :: Literal i = 1; i < expression_->getSize(); ++ i) {
			if (expression_->getSymbol (i).isVariable()) {
				checkVariable (i);
			}
		}
	}
	void
	Rule :: checkVariable (const index :: Literal index) const
	{
		const Symbol& current= expression_->getSymbol (index);
		for (index :: Literal i = 1; i < index - 1; ++ i) {
			const Symbol& previous = expression_->getSymbol (i);
			if (current == previous) {
				Error* error = new Error (location_, Error :: SEMANTIC);
				error->message() << "syntax rule term must not contain two different ";
				error->message() << "occurrences of a single variable." << endLine;
				error->message() << tab << "term: " << *expression_ << endLine;
				throw error;
			}
		}
	}
}
}
}
}

#endif /*MDL_FORM_HEADER_TERM_RULE_CPP_*/
