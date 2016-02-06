/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_notation_Term.hpp                         */
/* Description:     notation term class                                      */
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
namespace proof {
namespace notation {

class Term :
	public mdl :: proof :: Term,
	public Scalar<Term> {
public :
	Term
	(
		const Location&,
		mdl :: Identificator*,
		array :: Expression*,
		mdl :: Theory*
	);
	virtual ~ Term();

	// object :: Expressive interface
	virtual array :: Expression* getExpression();
	virtual mdl :: Type* getType();
	virtual const array :: Expression* getExpression() const;
	virtual const mdl :: Type* getType() const;

	// object :: Buildable interface
	virtual void build();

	// object :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const = 0;

	// object :: Object interface
	virtual void commitSuicide() = 0;
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

protected :
	const Location location_;
	mdl :: Theory* theory_;
	mdl :: Identificator* identificator_;
	mdl :: Type* type_;
	array :: Expression* expression_;
};

}
}
}
}


