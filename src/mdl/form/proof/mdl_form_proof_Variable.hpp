/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_Variable.hpp                              */
/* Description:     variable declaration in proof                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_PROOF_VARIABLE_HPP_
#define MDL_FORM_PROOF_VARIABLE_HPP_

#include "mdl/interface/mdl_interface.hpp"

namespace mdl {
namespace form {
namespace proof {

class Variable :
	public mdl :: proof :: Variable,
	public Scalar<Variable> {
public :
	Variable (const Location& location, mdl :: header :: Variable*);
	Variable
	(
		mdl :: proof :: Line*,
		const Location&,
		const mdl :: Comments*,
		mdl :: header :: Variable*,
		mdl :: Theory*
	);
	virtual ~ Variable();

	// object :: Typing interface
	virtual void translateVariables (String&) const;
	virtual void translateFloatings (String&, const index :: Arity = 0) const;

	virtual void setNext (object :: Typing*);
	virtual void setType (const value :: Literal, mdl :: Type*);

	virtual mdl :: Type* getType (const value  :: Literal);
	virtual mdl :: header :: Variable* getDeclaration (const value :: Literal);
	virtual object :: Typing* getPrevious();

	virtual const mdl :: Type* getType (const value  :: Literal) const;
	virtual const mdl :: header :: Variable* getDeclaration (const value :: Literal) const;
	virtual const object :: Typing* getPrevious() const;

	// proof :: Line interface
	virtual Sort getSort() const;
	virtual void incIndex (const index :: Step);
	virtual void decIndex (const index :: Step);
	virtual void setNext (mdl :: proof :: Line*);
	virtual void setPrev (mdl :: proof :: Line*);
	virtual mdl :: proof :: Line* getNext();
	virtual mdl :: proof :: Line* getPrev();
	virtual const mdl :: proof :: Line* getNext() const;
	virtual const mdl :: proof :: Line* getPrev() const;
	virtual const Location& getLocation() const;

	// object :: Scoping interface
	virtual mdl :: proof :: Scope* buildScope (mdl :: proof :: Scope*);
	virtual void setScope (mdl :: proof :: Scope*);
	virtual mdl :: proof :: Scope* getScope();
	virtual const mdl :: proof :: Scope* getScope() const;

	// object :: Buildable interface
	virtual void build();

	// object :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;
	virtual bool lookup() const;
	virtual object :: Writable* find();
	virtual const object :: Writable* find() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

	class Declaration;

private :
	const Location location_;
	const mdl :: Comments* const comments_;
	mdl :: header :: Variable* variable_;
	mdl :: proof :: Scope* scope_;
	object :: Typing* previous_;
	Line* nextLine_;
	Line* prevLine_;
	object :: Typing* next_;
};

}
}
}

#endif /*MDL_FORM_PROOF_VARIABLE_HPP_*/
