/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_notation_Meaning.hpp                      */
/* Description:     meaning in notation                                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_PROOF_NOTATION_MEANING_HPP_
#define MDL_FORM_PROOF_NOTATION_MEANING_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/form/mdl_form.hpp"

namespace mdl {
namespace form {
namespace proof {
namespace notation {

class Meaning : public Term {
public :
	Meaning
	(
		const Location&,
		index :: Arity,
		mdl :: Identificator*,
		array :: Expression*,
		mdl :: Theory*
	);
	virtual ~ Meaning();

	// object :: Writable interface
	virtual void replicate (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
};

}
}
}
}

#endif /*MDL_FORM_PROOF_NOTATION_MEANING_HPP_*/
