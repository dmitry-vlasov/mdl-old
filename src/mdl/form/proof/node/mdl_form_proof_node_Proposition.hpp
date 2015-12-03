/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_proof_node_Proposition.hpp                      */
/* Description:     proposition as a proof node                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_PROOF_NODE_PROPOSITION_HPP_
#define MDL_FORM_PROOF_NODE_PROPOSITION_HPP_

#include "mdl/form/proof/node/mdl_form_proof_node_Statement.hpp"

namespace mdl {
namespace form {
namespace proof {
namespace node {

class Proposition :
	public Statement,
	public Scalar<Proposition>{
public :
	Proposition
	(
		mdl :: Assertion*,
		index :: Arity,
		const array :: Expression*
	);
	virtual ~ Proposition();

	// proof :: Node interface
	virtual Kind getKind() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
};

}
}
}
}

#endif /*MDL_FORM_PROOF_NODE_PROPOSITION_HPP_*/
