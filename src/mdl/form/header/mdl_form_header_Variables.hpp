/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_Variables.hpp                            */
/* Description:     variables declarations                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"

namespace mdl {
namespace form {
namespace header {

class Variables :
	public mdl :: Variables,
	public Scalar<Variables> {
public :
	Variables
	(
		const Location&,
		const vector :: parser :: Variable&,
		mdl :: Theory*
	);
	virtual ~ Variables();

	static const mdl :: Variables* getCurrent();

	// mdl :: Variables interface
	virtual index :: Arity getSize() const;
	virtual bool contain (const Symbol&) const;
	virtual mdl :: header :: Variable* getVariable (const index :: Arity);
	virtual const mdl :: header :: Variable* getVariable (const index :: Arity) const;

	// object :: Typing interface
	virtual void translateVariables (String&) const;
	virtual void translateFloatings (String&, const index :: Arity = 0) const;

	virtual void setNext (object :: Typing*);
	virtual void setType (const value :: Literal, mdl :: Type*);

	virtual mdl :: Type* getType (const value :: Literal);
	virtual mdl :: header :: Variable* getDeclaration (const value :: Literal);
	virtual object :: Typing* getPrevious();

	virtual const mdl :: Type* getType (const value :: Literal) const;
	virtual const mdl :: header :: Variable* getDeclaration (const value :: Literal) const;
	virtual const object :: Typing* getPrevious() const;

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

private :
	friend class refactor :: redundant :: Variables;

	const Location location_;
	vector :: header :: Variable variableVector_;
	object :: Typing* next_;

	static const mdl :: Variables* current_;
};

}
}
}


