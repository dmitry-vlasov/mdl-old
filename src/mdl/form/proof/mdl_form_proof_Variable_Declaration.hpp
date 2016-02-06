/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_Variable_Declaration.hpp                  */
/* Description:     variable declaration in proof                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/form/header/mdl_form_header_Variable.hpp"

namespace mdl {
namespace form {
namespace proof {

class Variable :: Declaration : public header :: Variable {
public :
	Declaration
	(
		const Location&,
		value :: Literal,
		mdl :: Identificator*,
		mdl :: Theory*
	);
	virtual ~ Declaration();

	// header :: Variable interface
	virtual void translateReference (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
};

}
}
}


