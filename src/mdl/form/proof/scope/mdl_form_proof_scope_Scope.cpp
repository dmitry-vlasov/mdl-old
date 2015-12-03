/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_scope_Scope.cpp                           */
/* Description:     base scope class                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_PROOF_SCOPE_SCOPE_CPP_
#define MDL_FORM_PROOF_SCOPE_SCOPE_CPP_

#include "mdl/form/mdl_form.hpp"

namespace mdl {
namespace form {
namespace proof {
namespace scope {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Scope :: Scope (mdl :: proof :: Scope* scope) :
	scope_ (scope) {
	}
	Scope :: ~ Scope() {
	}

	// object :: Object implementation
	Size_t
	Scope :: getVolume() const {
		return 0;
	}
	Size_t
	Scope :: getSizeOf() const {
		return sizeof (Scope);
	}
	void
	Scope :: show (String&) const {
	}
}
}
}
}

#endif /*MDL_FORM_PROOF_SCOPE_SCOPE_CPP_*/
