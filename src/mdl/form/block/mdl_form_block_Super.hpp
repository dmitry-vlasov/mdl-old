/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_block_Super.hpp                                 */
/* Description:     type-supertype relation class                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/form/header/mdl_form_header_Line.hpp"

namespace mdl {
namespace form {
namespace block {

class Super :
	public mdl :: Super,
	public header :: Line :: Counter,
	public Scalar<Super> {
public :
	Super
	(
		mdl :: Type*,
		mdl :: Identificator*,
		mdl :: Theory*
	);
	Super
	(
		mdl :: Type*,
		mdl :: Type*,
		mdl :: Theory*
	);
	virtual ~ Super();

	// mdl :: Super interface
	virtual void translateReference (String&) const;
	virtual void addSuperSuper (vector :: Super&);
	virtual mdl :: Type* getType();
	virtual const mdl :: Type* getType() const;

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

private :
	mdl :: Theory* theory_;
	mdl :: Identificator* const identificator_;
	mdl :: Type* inferType_;
	mdl :: Type* superType_;

	static const char variable_[];
	static const char header_[];
	static const char delimiter_[];
};

}
}
}


