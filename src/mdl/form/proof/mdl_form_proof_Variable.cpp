/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_Variable.cpp                              */
/* Description:     variable declaration in proof                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_PROOF_VARIABLE_CPP_
#define MDL_FORM_PROOF_VARIABLE_CPP_

namespace mdl {
namespace form {
namespace proof {

	/****************************
	 *		Public members
	 ****************************/

	Variable :: Variable (const Location& location, mdl :: header :: Variable* variable) :
	location_ (location),
	comments_ (NULL),
	variable_ (variable),
	scope_ (NULL),
	previous_ (NULL),
	nextLine_ (NULL),
	prevLine_ (NULL),
	next_ (NULL) {
	}
	Variable :: Variable
	(
		mdl :: proof :: Line* prev,
		const Location& location,
		const mdl :: Comments* comments,
		mdl :: header :: Variable* variable,
		mdl :: Theory*
	) :
	location_ (location),
	comments_ (comments),
	variable_ (variable),
	scope_ (NULL),
	previous_ (NULL),
	nextLine_ (NULL),
	prevLine_ (prev),
	next_ (NULL)
	{
		if (prev != NULL) {
			prev->setNext (this);
		}
	}
	Variable :: ~ Variable()
	{
		deleteAggregateObject (comments_);
		deleteAggregateObject (variable_);
		deleteAggregateObject (scope_);
	}

	// object :: Typing implementation
	void
	Variable :: translateVariables (String& string) const
	{
		string << tab << :: smm :: Token :: variable_ << space;
		const value :: Literal literal = variable_->getLiteral();
		string << Table :: literals()->get (literal) << space;
		string << :: smm :: Token :: end_ << endLine;
		if (next_ != NULL) {
			next_->translateVariables (string);
		}
	}
	void
	Variable :: translateFloatings (String& string, const index :: Arity index) const
	{
		string << tab;
		variable_->setIndex (index);
		variable_->translate (string);
		if (next_ != NULL) {
			next_->translateFloatings (string, index + 1);
		}
	}
	void
	Variable :: setNext (object :: Typing*  next) {
		next_ = next;
	}
	void
	Variable :: setType (const value :: Literal name, mdl :: Type* type)
	{
		if (variable_->getLiteral() == name) {
			variable_->setType (type);
		} else if (next_ != NULL) {
			next_->setType (name, type);
		}
	}
	mdl :: Type*
	Variable :: getType (const value :: Literal literal)
	{
		if (variable_->getLiteral() == literal) {
			return variable_->getType();
		}
		if (previous_ != NULL) {
			return previous_->getType (literal);
		} else {
			return NULL;
		}
	}
	mdl :: header :: Variable*
	Variable :: getDeclaration (const value :: Literal literal)
	{
		if (variable_->getLiteral() == literal) {
			return variable_;
		}
		if (next_ != NULL) {
			return next_->getDeclaration (literal);
		} else {
			return NULL;
		}
	}
	object :: Typing*
	Variable :: getPrevious() {
		return previous_;
	}
	const mdl :: Type*
	Variable :: getType (const value :: Literal literal) const
	{
		if (variable_->getLiteral() == literal) {
			return variable_->getType();
		}
		if (previous_ != NULL) {
			return previous_->getType (literal);
		} else {
			return NULL;
		}
	}
	const mdl :: header :: Variable*
	Variable :: getDeclaration (const value :: Literal literal) const
	{
		if (variable_->getLiteral() == literal) {
			return variable_;
		}
		if (next_ != NULL) {
			return next_->getDeclaration (literal);
		} else {
			return NULL;
		}
	}
	const object :: Typing*
	Variable :: getPrevious() const {
		return previous_;
	}

	// mdl :: proof :: Line implementation
	Variable :: Sort
	Variable :: getSort() const {
		return VARIABLE;
	}
	void
	Variable :: incIndex (const index :: Step) {
	}
	void
	Variable :: decIndex (const index :: Step) {
	}
	void
	Variable :: setNext (mdl :: proof :: Line* line) {
		nextLine_ = line;
	}
	void
	Variable :: setPrev (mdl :: proof :: Line* line) {
		prevLine_ = line;
	}
	mdl :: proof :: Line*
	Variable :: getNext() {
		return nextLine_;
	}
	mdl :: proof :: Line*
	Variable :: getPrev() {
		return prevLine_;
	}
	const mdl :: proof :: Line*
	Variable :: getNext() const {
		return nextLine_;
	}
	const mdl :: proof :: Line*
	Variable :: getPrev() const {
		return prevLine_;
	}
	const Location&
	Variable :: getLocation() const {
		return location_;
	}

	// object :: Scoping implementation
	mdl :: proof :: Scope*
	Variable :: buildScope (mdl :: proof :: Scope* scope)
	{
		previous_ = scope->getVariables();
		previous_->setNext (this);
		scope_ = new scope :: Variable (scope, this);
		return scope_;
	}
	void
	Variable :: setScope (mdl :: proof :: Scope* scope) {
		scope_ = scope;
	}
	mdl :: proof :: Scope*
	Variable :: getScope() {
		return scope_;
	}
	const mdl :: proof :: Scope*
	Variable :: getScope() const {
		return scope_;
	}

	// object :: Buildable implementation
	void
	Variable :: build() {
		variable_->build();
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: tab;

	// object :: Writable implementation
	void
	Variable :: translate (String& string) const
	{
		string << location_.getIndent();
		variable_->translate (string);
	}
	void
	Variable :: replicate (String& string) const
	{
		if (!Config :: removeComments() && (comments_ != NULL)) {
			string << location_.getIndent();
			comments_->replicate (string);
			string << endLine;
		}
		string << location_.getIndent();
		variable_->replicate (string);
		string << Token :: semicolon_  << endLine;
	}
	bool
	Variable :: lookup() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return true;
		} else {
			return variable_->lookup();
		}
	}
	object :: Writable*
	Variable :: find()
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		} else {
			return variable_->find();
		}
	}
	const object :: Writable*
	Variable :: find() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
		} else {
			return variable_->find();
		}
	}

	// object :: Object implementation
	void
	Variable :: commitSuicide() {
		delete this;
	}
	Size_t
	Variable :: getVolume() const {
		Size_t volume = 0;
		volume += getAggregateVolume (comments_);
		volume += getAggregateVolume (variable_);
		volume += getAggregateVolume (scope_);
		return volume;
	}
	Size_t
	Variable :: getSizeOf() const {
		return sizeof (Variable);
	}
}
}
}

#endif /*MDL_FORM_PROOF_VARIABLE_CPP_*/
