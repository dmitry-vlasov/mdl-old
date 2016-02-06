/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_statement_Statement.hpp                  */
/* Description:     statement class                                          */
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
namespace header {
namespace statement {

class Statement :
	virtual public mdl :: Statement,
	public Line {
public :
	Statement
	(
		const Location&,
		index :: Arity,
		mdl :: Identificator*,
		array :: Expression*,
		mdl :: Theory*
	);
	virtual ~ Statement();

	// mdl :: Statement interface

	virtual void setAssertion (mdl :: Assertion*);
	virtual index :: Arity getIndex() const;

	virtual mdl :: Assertion* getAssertion();
	virtual mdl :: proof :: Node* getProofNode();
	virtual const mdl :: Assertion* getAssertion() const;
	virtual const mdl :: proof :: Node* getProofNode() const;

	// object :: Buildable interface
	virtual void build();

	// object :: Writable interface
	virtual void translate (String&) const = 0;
	virtual void replicate (String&) const = 0;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

protected :
	friend class refactor :: redundant :: Hypotheses;

	mdl :: Assertion* assertion_;
	index :: Arity index_;
	mdl :: proof :: Node* proofNode_;
};

}
}
}
}


