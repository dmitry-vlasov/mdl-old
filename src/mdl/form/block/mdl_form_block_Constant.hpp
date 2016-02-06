/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_block_Constant.hpp                              */
/* Description:     constant class                                           */
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

class Constant :
	public mdl :: Constant,
	public form :: Identifiable,
	public Scalar<Constant> {
public :
	Constant
	(
		const Location&,
		const mdl :: Comments*,
		String*,
		String*,
		String*,
		mdl :: Theory*
	);
	virtual ~ Constant();

	// mdl :: Constant interface
	virtual index :: Literal getSize() const;
	virtual value :: Literal getValue (const index :: Literal) const;

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
	/*virtual void check();
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
	void writeXMLSafe (String&) const;

	String* symbol_;
	String* ascii_;
	String* latex_;
	value :: Literal literal_;
};

}
}
}


