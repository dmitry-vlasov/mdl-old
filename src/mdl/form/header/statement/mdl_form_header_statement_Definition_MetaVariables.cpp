/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_statement_Definition_MetaVariables.cpp   */
/* Description:     meta variables in definition proposition                 */
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
	Definition :: MetaVariables_ :: MetaVariables_
	(
		object :: Typing* variables,
		mdl :: term :: Definition* defiendum,
		mdl :: term :: Definition* definiens
	) :
	variables_ (variables),
	defiendum_ (defiendum),
	definiens_ (definiens) {
	}
	Definition :: MetaVariables_ :: ~ MetaVariables_() {
	}

	// object :: Typing implementation
	mdl :: Type*
	Definition :: MetaVariables_ :: getType (const value :: Literal literal)
	{
		if (literal == Definition :: defiendumKeyword_) {
			return defiendum_->getType();
		}
		if (literal == Definition :: definiensKeyword_) {
			return definiens_->getType();
		}
		return variables_->getType (literal);
	}
	mdl :: header :: Variable*
	Definition :: MetaVariables_ :: getDeclaration (const value :: Literal literal) {
		return variables_->getDeclaration (literal);
	}
	object :: Typing*
	Definition :: MetaVariables_ :: getPrevious() {
		return variables_;
	}

	const mdl :: Type*
	Definition :: MetaVariables_ :: getType (const value :: Literal literal) const
	{
		if (literal == Definition :: defiendumKeyword_) {
			return defiendum_->getType();
		}
		if (literal == Definition :: definiensKeyword_) {
			return definiens_->getType();
		}
		return variables_->getType (literal);
	}
	const mdl :: header :: Variable*
	Definition :: MetaVariables_ :: getDeclaration (const value :: Literal literal) const {
		return variables_->getDeclaration (literal);
	}
	const object :: Typing*
	Definition :: MetaVariables_ :: getPrevious() const {
		return variables_;
	}
	/*void
	Definition :: MetaVariables_ :: setNext (const object :: Typing*) const {
	}
	void
	Definition :: MetaVariables_ :: translateVariables (String&) const {
	}
	void
	Definition :: MetaVariables_ :: translateFloatings (String&, const index :: Arity) const {
	}*/

	// object :: Buildable implementation
	//void
	//Definition :: MetaVariables_ :: build() {
	//}

	// object :: Writable implementation
	/*void
	Definition :: MetaVariables_ :: translate (String&) const {
	}
	void
	Definition :: MetaVariables_ :: replicate (String&) const {
	}*/

	// object :: Object implementation
	void
	Definition :: MetaVariables_ :: commitSuicide() {
		delete this;
	}
	Size_t
	Definition :: MetaVariables_ :: getVolume() const {
		return 0;
	}
	Size_t
	Definition :: MetaVariables_ :: getSizeOf() const {
		return sizeof (MetaVariables_);
	}
}
}
}
}


