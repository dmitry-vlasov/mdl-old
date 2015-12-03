/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_statement_Provable.hpp                   */
/* Description:     provable statement class                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_HEADER_STATEMENT_PROVABLE_HPP_
#define MDL_FORM_HEADER_STATEMENT_PROVABLE_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/form/header/statement/mdl_form_header_statement_Statement.hpp"

namespace mdl {
namespace form {
namespace header {
namespace statement {

class Provable :
	virtual public mdl :: statement :: Provable,
	public Proposition,
	public Scalar<Provable> {
public :
	Provable
	(
		const Location&,
		index :: Arity,
		mdl :: Identificator*,
		array :: Expression*,
		mdl :: Theory*
	);
	virtual ~ Provable();

	// statement :: Provable interface
	virtual mdl :: proof :: Provable* getProof();
	virtual const mdl :: proof :: Provable* getProof() const;

	// object :: Buildable interface
	virtual void build();

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

#endif /*MDL_FORM_HEADER_STATEMENT_PROVABLE_HPP_*/
