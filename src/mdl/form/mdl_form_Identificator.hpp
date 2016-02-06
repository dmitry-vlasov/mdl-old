/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_Identificator.hpp                               */
/* Description:     identificator                                            */
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

class Identificator :
	public mdl :: Identificator,
	public Scalar<Identificator> {
public :
	Identificator ();
	Identificator (const mdl :: Identificator&);
	Identificator (const mdl :: Identificator*);
	Identificator (const value :: Name);
	Identificator (const value :: Name, const Location&);
	Identificator (const char*);
	Identificator (const String&);
	virtual ~ Identificator();

	// mdl :: Identificator interface
	virtual value :: Name getName() const;
	virtual void setNext (mdl :: Identificator*);
	virtual mdl :: Identificator* getNext();
	virtual const mdl :: Identificator* getNext() const;

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
	const Location location_;
	value :: Name name_;
	mdl :: Identificator* next_;
};

}
}


