/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_notation_Notation.hpp                     */
/* Description:     notation class                                           */
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
namespace proof {
namespace notation {

class Notation :
	public mdl :: proof :: Notation,
	public Scalar<Notation> {
public :
	Notation
	(
		mdl :: proof :: Line*,
		const Location&,
		value :: Literal,
		mdl :: Variables*,
		mdl :: proof :: Term*,
		mdl :: proof :: Term*,
		mdl :: Theory*
	);
	virtual ~ Notation();

	// mdl :: proof :: Notation interface
	virtual value :: Literal getLiteral() const;
	virtual mdl :: Variables* getVariables();
	virtual mdl :: proof :: Term* getAbbreviation();
	virtual mdl :: proof :: Term* getMeaning();
	virtual const mdl :: Variables* getVariables() const;
	virtual const mdl :: proof :: Term* getAbbreviation() const;
	virtual const mdl :: proof :: Term* getMeaning() const;

	// mdl :: proof :: Line interface
	virtual Sort getSort() const;
	virtual const mdl :: proof :: Line* getNext() const;
	virtual const mdl :: proof :: Line* getPrev() const;
	virtual void incIndex (const index :: Step);
	virtual void decIndex (const index :: Step);
	virtual mdl :: proof :: Line* getNext();
	virtual mdl :: proof :: Line* getPrev();
	virtual void setNext (mdl :: proof :: Line*);
	virtual void setPrev (mdl :: proof :: Line*);
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

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	const Location location_;
	value :: Literal literal_;
	mdl :: Variables* variables_;
	mdl :: proof :: Term* abbreviation_;
	mdl :: proof :: Term* meaning_;

	mdl :: proof :: Line* next_;
	mdl :: proof :: Line* prev_;
	mdl :: proof :: Scope* scope_;
};

}
}
}
}


