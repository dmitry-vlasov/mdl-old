/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_Variables.cpp                            */
/* Description:     variables declarations                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_HEADER_VARIABLES_CPP_
#define MDL_FORM_HEADER_VARIABLES_CPP_

namespace mdl {
namespace form {
namespace header {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Variables :: Variables
	(
		const Location& location,
		const vector :: parser :: Variable& variableVector,
		mdl :: Theory* theory
	) :
	location_ (location),
	variableVector_ (variableVector),
	next_ (NULL) {
	}
	Variables :: ~ Variables() {
	}

	const mdl :: Variables*
	Variables :: getCurrent() {
		return current_;
	}

	// mdl :: Variables implementation
	index :: Arity
	Variables :: getSize() const {
		return variableVector_.getSize();
	}
	bool
	Variables :: contain (const Symbol& symbol) const
	{
		for (index :: Arity i = 0; i < variableVector_.getSize(); ++ i) {
			const mdl :: header :: Variable* const
				variable = variableVector_.getValue (i);
			if (variable->getLiteral() == symbol.getLiteral()) {
				return true;
			}
		}
		return false;
	}
	mdl :: header :: Variable*
	Variables :: getVariable (const index :: Arity index) {
		return variableVector_.getValue (index);
	}
	const mdl :: header :: Variable*
	Variables :: getVariable (const index :: Arity index) const {
		return variableVector_.getValue (index);
	}

	// object :: Typing implementation
	void
	Variables :: translateVariables (String& string) const
	{
		current_ = this;
		if (!variableVector_.isEmpty()) {
			string << tab << :: smm :: Token :: variable_ << space;
			for (index :: Arity i = 0; i < variableVector_.getSize(); ++ i) {
				const value :: Literal
					literal = variableVector_.getValue (i)->getLiteral();
				string << Table :: literals()->get (literal) << space;
			}
			string << :: smm :: Token :: end_ << endLine;
		}
		if (next_ != NULL) {
			next_->translateVariables (string);
		}
	}
	void
	Variables :: translateFloatings (String& string, const index :: Arity index) const
	{
		for (index :: Arity i = 0; i < variableVector_.getSize(); ++ i) {
			string << tab;
			variableVector_.getValue (i)->setIndex (index + i);
			variableVector_.getValue (i)->translate (string);
		}
		if (next_ != NULL) {
			next_->translateFloatings (string, index);
		}
	}
	void
	Variables :: setNext (object :: Typing*  next) {
		next_ = next;
	}
	void
	Variables :: setType (const value :: Literal name, mdl :: Type* type)
	{
		for (index :: Arity i = 0; i < variableVector_.getSize(); ++ i) {
			mdl :: header :: Variable*
				variable = variableVector_.getValue (i);
			if (variable->getLiteral() == name) {
				variable->setType (type);
				return;
			}
		}
		if (next_ != NULL) {
			next_->setType (name, type);
		}
	}
	mdl :: Type*
	Variables :: getType (const value :: Literal literal)
	{
		for (index :: Arity i = 0; i < variableVector_.getSize(); ++ i) {
			mdl :: header :: Variable*
				variable = variableVector_.getValue (i);
			if (variable->getLiteral() == literal) {
				return variable->getType();
			}
		}
		return NULL;
	}
	mdl :: header :: Variable*
	Variables :: getDeclaration (const value :: Literal literal)
	{
		for (index :: Arity i = 0; i < variableVector_.getSize(); ++ i) {
			mdl :: header :: Variable*
				variable = variableVector_.getValue (i);
			if (variable->getLiteral() == literal) {
				return variable;
			}
		}
		if (next_ != NULL) {
			return next_->getDeclaration (literal);
		}
		return NULL;
	}
	object :: Typing*
	Variables :: getPrevious() {
		return NULL;
	}
	const mdl :: Type*
	Variables :: getType (const value :: Literal literal) const
	{
		for (index :: Arity i = 0; i < variableVector_.getSize(); ++ i) {
			const mdl :: header :: Variable* const
				variable = variableVector_.getValue (i);
			if (variable->getLiteral() == literal) {
				return variable->getType();
			}
		}
		return NULL;
	}
	const mdl :: header :: Variable*
	Variables :: getDeclaration (const value :: Literal literal) const
	{
		for (index :: Arity i = 0; i < variableVector_.getSize(); ++ i) {
			const mdl :: header :: Variable* const
				variable = variableVector_.getValue (i);
			if (variable->getLiteral() == literal) {
				return variable;
			}
		}
		if (next_ != NULL) {
			return next_->getDeclaration (literal);
		}
		return NULL;
	}
	const object :: Typing*
	Variables :: getPrevious() const {
		return NULL;
	}



	// object :: Buildable implementation
	//void
	//Variables :: build() {
	//}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Variables :: translate (String& string) const
	{
		translateVariables (string);
		translateFloatings (string);
	}
	void
	Variables :: replicate (String& string) const
	{
		string << Token :: openBracket_;
		for (index :: Arity i = 0; i < variableVector_.getSize(); ++ i) {
			variableVector_.getValue (i)->replicate (string);
			if (i < variableVector_.getSize() - 1) {
				string << Token :: comma_ << space;
			}
		}
		string << Token :: closeBracket_ << space;
	}
	bool
	Variables :: lookup() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return true;
		}
		for (index :: Arity i = 0; i < variableVector_.getSize(); ++ i) {
			if (variableVector_.getValue (i)->lookup()) {
				return true;
			}
		}
		return false;
	}
	object :: Writable*
	Variables :: find()
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		}
		object :: Writable* object = NULL;
		for (index :: Arity i = 0; i < variableVector_.getSize(); ++ i) {
			object = variableVector_.getValue (i)->find();
			if (object != NULL) {
				return object;
			}
		}
		return NULL;
	}
	const object :: Writable*
	Variables :: find() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		}
		const object :: Writable* object = NULL;
		for (index :: Arity i = 0; i < variableVector_.getSize(); ++ i) {
			object = variableVector_.getValue (i)->find();
			if (object != NULL) {
				return object;
			}
		}
		return NULL;
	}

	// object :: Object implementation
	void
	Variables :: commitSuicide() {
		delete this;
	}
	Size_t
	Variables :: getVolume() const {
		return variableVector_.getVolume();
	}
	Size_t
	Variables :: getSizeOf() const {
		return sizeof (Variables);
	}

	/***********************************
	 *		Static private attributes
	 ***********************************/

	const mdl :: Variables* Variables :: current_ = NULL;
}
}
}

#endif /*MDL_FORM_HEADER_VARIABLES_CPP_*/
