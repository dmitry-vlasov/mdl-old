/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_term_Definition.cpp                      */
/* Description:     definition term class                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_HEADER_TERM_DEFINITION_CPP_
#define MDL_FORM_HEADER_TERM_DEFINITION_CPP_

namespace mdl {
namespace form {
namespace header {
namespace term {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Definition :: Definition
	(
		const Location& location,
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
	definition_ (NULL) {
	}
	Definition :: ~ Definition() {
	}

	// term :: Definition implementation
	void
	Definition :: setDefinition (mdl :: Definition* definition) {
		definition_ = definition;
	}

	// object :: Expressive implementation
	mdl :: Type*
	Definition :: getType() {
		return header :: Line :: type_;
	}
	array :: Expression*
	Definition :: getExpression() {
		return header :: Line :: expression_;
	}
	const mdl :: Type*
	Definition :: getType() const {
		return header :: Line :: type_;
	}
	const array :: Expression*
	Definition :: getExpression() const {
		return header :: Line :: expression_;
	}

using manipulator :: endLine;
using manipulator :: space;

	// object :: Buildable implementation
	void
	Definition :: build()
	{
		try {
			header :: Line :: build();
			expression_->build (definition_->getVariables(), true);
			expression_->parse (type_);
		} catch (Error* error) {
			error->add (location_);
			throw error;
		}
	}

	// object :: Object implementation
	void
	Definition :: commitSuicide() {
		delete this;
	}
	Size_t
	Definition :: getVolume() const {
		return header :: Line :: getVolume();
	}
	Size_t
	Definition :: getSizeOf() const {
		return sizeof (Definition);
	}
}
}
}
}

#endif /*MDL_FORM_HEADER_TERM_DEFINITION_CPP_*/
