/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_statement_Axiomatic.hpp                  */
/* Description:     axiomatic statement class                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/form/header/statement/mdl_form_header_statement_Proposition.hpp"

namespace mdl {
namespace form {
namespace header {
namespace statement {

class Axiomatic :
	virtual public mdl :: statement :: Axiomatic,
	public Proposition,
	public Scalar<Axiomatic> {
public :
	Axiomatic
	(
		const Location&,
		index :: Arity,
		mdl :: Identificator*,
		array :: Expression*,
		mdl :: Theory*
	);
	virtual ~ Axiomatic();

	// mdl :: Proposition interface
	/*virtual const Location& getLocation() const;
	virtual index :: Assertion getSourceIndex() const;
	virtual index :: Assertion getTargetIndex() const;
	virtual mdl :: statement :: Experience* getExperience() const;
	virtual mdl :: evaluation :: Function* getEvaluation (const value :: Name);
	virtual const mdl :: evaluation :: Function* getEvaluation (const value :: Name) const;

	virtual void incRate (const bool sign = true) const;
	virtual value :: Integer getRate (const bool sign = true) const;*/

	// mdl :: Statement interface
	/*virtual index :: Arity getIndex() const;
	virtual void setAssertion (mdl :: Assertion*);
	virtual const mdl :: proof :: Node* getProofNode() const;*/

	// object :: Expressive interface
	//virtual const array :: Expression* getExpression() const;
	//virtual const mdl :: Type* getType() const;

	// object :: Buildable interface
	//virtual void build();

	// object :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
};

}
}
}
}


