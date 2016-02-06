/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_statement_Definition_MetaVariables.hpp   */
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

class Definition :: MetaVariables_ :
	public object :: Typing,
	public Scalar<Definition :: MetaVariables_> {
public :
	MetaVariables_
	(
		object :: Typing*,
		mdl :: term :: Definition*,
		mdl :: term :: Definition*
	);
	virtual ~ MetaVariables_();

	// object :: Typing interface
	//virtual void setNext (const object :: Typing*) const;

	virtual mdl :: Type* getType (const value :: Literal);
	virtual mdl :: header :: Variable* getDeclaration (const value :: Literal);
	virtual object :: Typing* getPrevious();

	virtual const mdl :: Type* getType (const value :: Literal) const;
	virtual const mdl :: header :: Variable* getDeclaration (const value :: Literal) const;
	virtual const object :: Typing* getPrevious() const;

	//virtual void translateVariables (String&) const;
	//virtual void translateFloatings (String&, const index :: Arity = 0) const;

	// object :: Buildable interface
	//virtual void build();

	// object :: Writable interface
	//virtual void translate (String&) const;
	//virtual void replicate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	object :: Typing* variables_;
	mdl :: term :: Definition* defiendum_;
	mdl :: term :: Definition* definiens_;
};

}
}
}
}


