/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_Link.hpp                                  */
/* Description:     proof link class                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/lexer/mdl_lexer.hpp"
#include "mdl/form/mdl_form_Identificator.hpp"

namespace mdl {
namespace form {
namespace proof {

class Link :
	public mdl :: proof :: Link,
	public Scalar<Link> {
public :
	Link
	(
		const Location&,
		value :: Kind,
		mdl :: Identificator*,
		index :: Arity,
		mdl :: proof :: References*,
		mdl :: Theory*
	);
	Link
	(
		const Location&,
		value :: Kind,
		mdl :: Theory*
	);
	Link
	(
		const Location&,
		mdl :: Proposition*,
		mdl :: proof :: References*,
		mdl :: Theory* = NULL
	);
	virtual ~ Link();

	// mdl :: proof :: Link interface
	virtual void buildScope (mdl :: proof :: Scope*);
	virtual index :: Arity getPropositionIndex() const;
	virtual mdl :: Assertion* getAssertion();
	virtual mdl :: Proposition* getProposition();
	virtual mdl :: proof :: References* getReferences();
	virtual const mdl :: Assertion* getAssertion() const;
	virtual const mdl :: Proposition* getProposition() const;
	virtual const mdl :: proof :: References* getReferences() const;

	virtual void translateReferences (String&) const;
	virtual void translateAssertion (String&) const;

	// object :: Buildable interface
	virtual void build();

	// object :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;
	virtual bool lookup() const;
	virtual const object :: Writable* find() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	const Location location_;
	mdl :: Theory* theory_;
	value :: Kind kind_;
	mdl :: Identificator* identificator_;
	index :: Arity proposition_;
	mdl :: proof :: References* references_;
	mdl :: Assertion* assertion_;
};

}
}
}


