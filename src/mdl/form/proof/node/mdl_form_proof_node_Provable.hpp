/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_node_Provable.hpp                         */
/* Description:     provable proof node                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/form/proof/node/mdl_form_proof_node_Statement.hpp"

namespace mdl {
namespace form {
namespace proof {
namespace node {

class Provable :
	virtual public Statement,
	virtual public mdl :: proof :: Provable,
	public Scalar<Provable> {
public :
	Provable
	(
		mdl :: Assertion*,
		index :: Arity,
		const array :: Expression*
	);
	virtual ~ Provable();

	// proof :: Provable interface
	virtual void setProof (mdl :: proof :: Node*);

	// proof :: Node interface
	virtual Kind getKind() const;
	virtual index :: Step getIndex() const;
	virtual void replicateReference (String&) const;
	virtual void translateReference (String&) const;

	// object :: Scoping interface
	virtual mdl :: proof :: Scope* buildScope (mdl :: proof :: Scope*);
	virtual void setScope (mdl :: proof :: Scope*);
	virtual mdl :: proof :: Scope* getScope();
	virtual const mdl :: proof :: Scope* getScope() const;

	// object :: Expressive interface
	virtual const array :: Expression* getExpression() const;
	virtual const mdl :: Type* getType() const;

	// object :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	mdl :: proof :: Node* proof_;
};

}
}
}
}


