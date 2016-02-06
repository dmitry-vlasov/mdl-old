/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_Variable.hpp                             */
/* Description:     variable declaration                                     */
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

class Variable :
	public mdl :: header :: Variable,
	public Scalar<Variable> {
public :
	Variable
	(
		const Location&,
		value :: Literal,
		mdl :: Identificator*,
		mdl :: Theory*
	);
	Variable
	(
		const Location&,
		const Symbol&,
		mdl :: Theory*
	);
	Variable (const Symbol&);
	virtual ~ Variable();

	// header :: Variable interface
	virtual value :: Literal getLiteral() const;
	virtual void setIndex (const index :: Arity);
	virtual void setType (mdl :: Type*);
	virtual void translateReference (String&) const;

	virtual Symbol& getSymbol();
	virtual mdl :: Type* getType ();
	virtual const Symbol& getSymbol() const;
	virtual const mdl :: Type* getType () const;

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

protected :
	const Location location_;
	index :: Arity index_;
	Symbol symbol_;
	mdl :: Identificator* identificator_;
};

}
}
}


