/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_block_Type.hpp                                  */
/* Description:     type class                                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/form/mdl_form_Identifiable.hpp"

namespace mdl {
namespace form {
namespace block {

class Type :
	public Identifiable,
	public mdl :: Type,
	public Scalar<Type> {
public :
	Type
	(
		const Location&,
		const mdl :: Comments*,
		value :: Name,
		const vector :: parser :: Identificator&,
		mdl :: Theory*
	);
	virtual ~ Type();

	// mdl :: Type interface
	virtual void mine (String&, const index :: Type) const;
	virtual index :: Type getSuperCount() const;
	virtual index :: Type getInferCount() const;
	virtual bool isSuper (const mdl :: Type*) const;
	virtual bool isInfer (const mdl :: Type*) const;

	virtual void addRule (mdl :: Rule*);
	virtual void addSubtype (mdl :: Type*);

	virtual tree :: Rule* getRuleTree();
	virtual mdl :: Super* getSuper (const index :: Type);
	virtual mdl :: Super* getSuper (const mdl :: Type*);
	virtual mdl :: Type*  getInfer (const index :: Type);

	virtual const tree :: Rule* getRuleTree() const;
	virtual const mdl :: Super* getSuper (const index :: Type) const;
	virtual const mdl :: Super* getSuper (const mdl :: Type* const) const;
	virtual const mdl :: Type*  getInfer (const index :: Type) const;

	// object :: Identifiable interface
	virtual const Location& getLocation() const;
	virtual value :: Name getName() const;

	virtual void translateName (String&, const index :: Arity = 0) const;
	virtual void replicateName (String&) const;

	virtual mdl :: Theory* getTheory();
	virtual mdl :: Identificator* getIdentificator();
	virtual const mdl :: Theory* getTheory() const;
	virtual const mdl :: Identificator* getIdentificator() const;

	// object :: Verifiable interface
	virtual void mine (String&) const;

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
	const index :: Type index_;
	const vector :: Identificator superNames_;
	vector :: Super supers_;
	vector :: Type subTypes_;
	tree :: Rule* ruleTree_;
};

}
}
}


