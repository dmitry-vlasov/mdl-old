/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_header_term_Defiendum.hpp                       */
/* Description:     defiendum term class                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_HEADER_TERM_DEFIENDUM_HPP_
#define MDL_FORM_HEADER_TERM_DEFIENDUM_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/form/header/term/mdl_form_header_term_Definition.hpp"

namespace mdl {
namespace form {
namespace header {
namespace term {

class Defiendum :
	public Definition,
	public Scalar<Defiendum> {
public :
	Defiendum
	(
		const Location&,
		index :: Arity,
		mdl :: Identificator*,
		array :: Expression*,
		mdl :: Theory*
	);
	virtual ~ Defiendum();

	// object :: Buildable interface
	virtual void build();

	// object :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
};

}
}
}
}

#endif /*MDL_FORM_HEADER_TERM_DEFIENDUM_HPP_*/
