/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_statement_Definition.hpp                 */
/* Description:     definition statement class                               */
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

class Definition :
	virtual public mdl :: statement :: Definition,
	public Proposition,
	public Scalar<Definition> {
public :
	Definition
	(
		const Location&,
		index :: Arity,
		mdl :: Identificator*,
		array :: Expression*,
		mdl :: Theory*
	);
	virtual ~ Definition();

	// statement :: Definition interface
	virtual void setDefiendum (mdl :: term :: Definition*);
	virtual void setDefiniens (mdl :: term :: Definition*);

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
	virtual void setAssertion (mdl :: Assertion*);
	//virtual index :: Arity getIndex() const;
	//virtual const mdl :: proof :: Node* getProofNode() const;

	// object :: Expressive interface
	//virtual const array :: Expression* getExpression() const;
	//virtual const mdl :: Type* getType() const;

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
	void insert
	(
		value :: Literal* literals,
		index :: Literal& index,
		mdl :: term :: Definition*
	) const;
	index :: Literal calculateLength() const;
	void substituteTerms();
	void substituteSymbol
	(
		const index :: Literal i,
		value :: Literal* literals,
		index :: Literal& index,
		bool& defiendumMet,
		bool& definiensMet
	) const;
	void buildOriginal ();

	class MetaVariables_;
	friend class MetaVariables_;

	array :: Expression* expandedExpression_;
	array :: Expression* originalExpression_;
	mdl :: term :: Definition* defiendum_;
	mdl :: term :: Definition* definiens_;
	MetaVariables_* metaVariables_;

	// static attributes
	static value :: Literal defiendumKeyword_;
	static value :: Literal definiensKeyword_;
};

}
}
}
}


