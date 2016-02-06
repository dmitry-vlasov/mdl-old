/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_block_Rule.hpp                                  */
/* Description:     syntax grammar rule class                                */
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

class Rule :
	public mdl :: Rule,
	public form :: Identifiable,
	public Scalar<Rule> {
public :
	Rule
	(
		const Location&,
		const mdl :: Comments*,
		value :: Name,
		mdl :: Variables*,
		mdl :: term :: Rule*,
		mdl :: Theory*
	);
	virtual ~ Rule();

	// mdl :: Rule interface
	virtual void setType (mdl :: Type*);

	virtual mdl :: Type* getType();
	virtual mdl :: Variables* getVariables();
	virtual mdl :: term :: Rule* getTerm();

	virtual const mdl :: Type* getType() const;
	virtual const mdl :: Variables* getVariables() const;
	virtual const mdl :: term :: Rule* getTerm() const;

	// object :: Identifiable interface
	//virtual const mdl :: Theory* getTheory() const;
	//virtual value :: Name getName() const;
	virtual void translateName (String&, const index :: Arity = 0) const;
	virtual void replicateName (String&) const;

	// object :: Verifiable interface
	/*virtual void check() const;
	virtual void compress();
	virtual void reprove();
	virtual void prove();
	virtual bool isVerified() const;*/
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
	mdl :: Type* type_;
	mdl :: Variables* variables_;
	mdl :: term :: Rule* term_;
};

}
}
}


