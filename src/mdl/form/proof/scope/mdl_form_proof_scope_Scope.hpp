/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_scope_Scope.hpp                           */
/* Description:     base scope class                                         */
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
namespace scope {

class Scope : public mdl :: proof :: Scope {
public :
	Scope (mdl :: proof :: Scope*);
	virtual ~ Scope();

	// object :: Object interface
	virtual void commitSuicide() = 0;
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

protected :
	mdl :: proof :: Scope* scope_;
};

}
}
}
}


